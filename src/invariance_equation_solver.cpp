#include "3hdm/invariance_equation_solver.h"

#include "3hdm/utilities.h"
#include "Eigen/Eigenvalues"
#include "unsupported/Eigen/KroneckerProduct"

const bool & InvarianceEquationSolver::Solution::isGood() const
{
	return mIsGood;
}

const InvarianceEquationSolver::Solution::Form & InvarianceEquationSolver::Solution::form() const
{
	return mForm;
}

const InvarianceEquationSolver::Solution::Origin & InvarianceEquationSolver::Solution::origin() const
{
	return mOrigin;
}

const MyVectorXcd & InvarianceEquationSolver::Solution::phase(size_t ith) const
{
	return mPhases.at(ith);
}

int InvarianceEquationSolver::Solution::phases() const
{
	return mPhases.size();
}

static MatrixForm::Form formConverter(InvarianceEquationSolver::Solution::Form form)
{
    switch (form)
    {
	case InvarianceEquationSolver::Solution::Form::General:
	    return MatrixForm::Form::General;
	case InvarianceEquationSolver::Solution::Form::Particular:
	    return MatrixForm::Form::Particular;
	default:
	    return MatrixForm::Form::Original;
    }
}

void InvarianceEquationSolver::Solution::switchFormTo(Form form)
{
	if (mForm != form)
	{
		mForm = form;
		takeForm();
	}
}

void InvarianceEquationSolver::Solution::takeForm()
{
	MatrixForm matrixForm(mInitialForm, formConverter(mForm));
	mPhases = matrixForm.phases();
	*this = matrixForm.matrix();
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles & particles, const Form & form)
{
	setParticles(particles);
	setForm(form);
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles & particles, const Form & form, const Group & group)
{
	setParticles(particles);
	setForm(form);
	compute(group);
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles & particles, const Form & form, const Group & group, const std::vector<size_t> & combination)
{
	setParticles(particles);
	setForm(form);
	compute(group, combination);
}

void InvarianceEquationSolver::compute(const Group & group, const std::vector<size_t> & combination)
{
	reset();
	generateInvarianceMatrices(group, combination);
	findEigenvectors1();
	if (EquationState::NoEigenvectors == mEquationState) { return; }
	findIntersectionBasis();
	if (EquationState::NoEigensubspace == mEquationState) { return; }
	prepareSolution(group, combination);
}

void InvarianceEquationSolver::compute(const Group & group)
{
	Combination combination(mShape, group.numberOfRepresentations());
	
	mSolutions.clear();
	do
	{
		compute(group, combination.get());
		if (EquationState::NoProblem == mEquationState)
		{
			mSolutions.push_back(mSolution);
		}
	} while (combination.next());
	reset();
}

const std::vector<MyMatrixXcd> & InvarianceEquationSolver::eigenvectors1() const
{
	return mEigenvectors1;
}

const std::vector<MyMatrixXcd> & InvarianceEquationSolver::invarianceMatrices() const
{
	return mInvarianceMatrices;
}

const MyMatrixXcd & InvarianceEquationSolver::intersectionBasis() const
{
	return mIntersectionBasis;
}

const InvarianceEquationSolver::Solution & InvarianceEquationSolver::solution() const
{
	return mSolution;
}

const std::vector<InvarianceEquationSolver::Solution> & InvarianceEquationSolver::solutions() const
{
	return mSolutions;
}

bool InvarianceEquationSolver::checkSolution() const
{
	for (const auto & solution : mSolution.mInitialForm.colwise())
	{
		for (const auto & invarianceMatrix : mInvarianceMatrices)
		{
			if ((invarianceMatrix * solution).isApprox(solution, 0.0001) == false)
			{
				return false;
			}
		}
	}

	return true;
}

MyMatrixXcd InvarianceEquationSolver::findEigenvectors1(const MyMatrixXcd & matrix)
{
	const double eigenvalue{1.0};
	MyMatrixXcd eigenvectors1{eigenvectors(matrix, eigenvalue)};
    
	return eigenvectors1;
}

void InvarianceEquationSolver::findEigenvectors1()
{
	MyMatrixXcd eigenvectors1;

	for (auto const invarianceMatrix : mInvarianceMatrices)
	{
		eigenvectors1 = findEigenvectors1(invarianceMatrix);
		if (0 == eigenvectors1.cols())
		{
			mEquationState = EquationState::NoEigenvectors;
			return;
		}
		mEigenvectors1.push_back(eigenvectors1);
	}
}

MyMatrixXcd InvarianceEquationSolver::findIntersectionBasis(const MyMatrixXcd & matrix1, const MyMatrixXcd & matrix2)
{
	MyMatrixXcd nullSpace{eigenspace(matrix1, matrix2)};
	MyMatrixXcd intersectionBasis(matrix1.rows(), nullSpace.cols());
	MyVectorXcd baseVector;

	for (auto i = 0; i < nullSpace.cols(); ++i)
	{
		baseVector.setZero(matrix1.rows());
		for (auto j = 0; j < matrix1.cols(); ++j)
		{
			baseVector += nullSpace.col(i)(j) * matrix1.col(j);
		}
		intersectionBasis.col(i) = baseVector;
	}

	return intersectionBasis;
}

void InvarianceEquationSolver::findIntersectionBasis()
{
	mIntersectionBasis = mEigenvectors1[0];
	for (auto i = 1; i < mEigenvectors1.size(); ++i)
	{
		mIntersectionBasis = findIntersectionBasis(mIntersectionBasis, mEigenvectors1.at(i));
		if (mIntersectionBasis.isZero())
		{
			mEquationState = EquationState::NoEigensubspace;
			return;
		}
	}
}

std::vector<MyMatrix3cd> InvarianceEquationSolver::prepareMatrices(const Group & group, size_t generator, const std::vector<size_t> & combination)
{
	std::vector<MyMatrix3cd> matrices{group.generator(generator, combination)};

	for (size_t i = 0; i < mOperation.size(); ++i)
	{
		if (mOperation[i] == 'A')
		{
			matrices[i].adjointInPlace();
		}
		if (mOperation[i] == 'T')
		{
			matrices[i].transposeInPlace();
		}
	}

	return matrices;
}

MyMatrixXcd InvarianceEquationSolver::generateInvarianceMatrix(const Group & group, size_t generator, const std::vector<size_t> & combination)
{
	std::vector<MyMatrix3cd> matrices{prepareMatrices(group, generator, combination)};
	return kroneckerProduct(matrices);
}

void InvarianceEquationSolver::generateInvarianceMatrices(const Group & group, const std::vector<size_t> & combination)
{
	MyMatrixXcd invarianceMatrix;

	for (auto i = 1; i <= group.numberOfGenerators(); ++i)
	{
		invarianceMatrix = generateInvarianceMatrix(group, i, combination);
		mInvarianceMatrices.push_back(invarianceMatrix);
	}
}

void InvarianceEquationSolver::prepareSolution(const Group & group, const std::vector<size_t> & combination)
{
	mSolution.mInitialForm = mIntersectionBasis;
	mSolution.mOrigin = { group.structure(), combination };
	mSolution.mIsGood = checkSolution();
	mSolution.takeForm();
}

void InvarianceEquationSolver::reset()
{
	mEquationState = EquationState::NoProblem;
	mInvarianceMatrices.clear();
	mEigenvectors1.clear();
	mIntersectionBasis.resize(0, 0);
	mSolution.resize(0, 0);
}

void InvarianceEquationSolver::setForm(const Form & form)
{
	mSolution.mForm = form;
}

void InvarianceEquationSolver::setParticles(const Particles & particles)
{
	const std::string shapes[3] = { "ABC", "ABC", "AABB" };
	const std::string operations[3] = { "AAT", "TAT", "TTAA" };

	mShape = shapes[static_cast<int>(particles)];
	mOperation = operations[static_cast<int>(particles)];
}

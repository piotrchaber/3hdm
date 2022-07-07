#include "../include/3hdm/invariance_equation_solver.h"

#include <Eigen/Eigenvalues>
#include <unsupported/Eigen/KroneckerProduct>

// helper function
static std::map<char, size_t> findUniqueChars(const std::string& s)
{
	std::map<char, size_t> result;
	for (auto const& c : s) { result[toupper(c)]; }
	return result;
}

// helper function
static std::vector<size_t> extendCombination(const std::string& shape, const std::vector<size_t>& combination, std::map<char, size_t>& uniqueChars)
{
	std::vector<size_t> result(shape.size());

	int i = 0;
	for (auto& uniqueChar : uniqueChars) {
		uniqueChar.second = combination[i++];
	}

	for (size_t i = 0; i < shape.size(); ++i) {
		result[i] = uniqueChars[shape[i]];
	}

	return result;
}

// helper function
static void extractColumnAndPhase(MyMatrixXcd::ColXpr& column, MyVectorXcd& phase)
{
	auto nonZeroElements = (column.array().abs() > 0.00001).count();
	phase.resize(nonZeroElements == 0 ? nonZeroElements : nonZeroElements - 1);

	int i = column.size() - 1;
	while (nonZeroElements > 1) {
		if (abs(column[i]) > 0.00001) {
			phase[nonZeroElements - 2] = column[i];
			column[i] = { 1.0,0.0 };
			--nonZeroElements;
		}
		--i;
	}
}

// helper function
static bool indexCompare(const MyVectorXcd& vector1, const MyVectorXcd& vector2)
{
	auto isNonZero = [](const auto& element) { return abs(element) > 0.000001; };
	auto firstNonZeroElement = [&](const auto& block) { return std::find_if(block.cbegin(), block.cend(), isNonZero); };
	auto indexOfFirstNonZeroElement = [&](const auto& block) { return std::distance(block.cbegin(), firstNonZeroElement(block)); };

	return indexOfFirstNonZeroElement(vector1) < indexOfFirstNonZeroElement(vector2);
}

// helper function
static void setFirstElementTo(MyMatrixXcd::ColXpr& column, const std::complex<double>& value)
{
	auto isNonZero = [](const auto& element) { return abs(element) > 0.000001; };
	auto isZero = [&](const auto& block) { return std::none_of(block.cbegin(), block.cend(), isNonZero); };
	auto firstNonZeroElement = [&](const auto& block) { return *std::find_if(block.cbegin(), block.cend(), isNonZero); };
	auto isFirstNonZeroElementEqual = [&](const auto& block) { return abs(firstNonZeroElement(block) - value) < 0.000001; };

	for (auto&& col : column.colwise()) {
		if (isZero(col) || isFirstNonZeroElementEqual(col)) { break; }
		col = (value / firstNonZeroElement(col)) * col;
	}
}

// helper function
static void sortByIndex(MyMatrixXcd::ColXpr& column)
{
	std::vector<MyVectorXcd> subvectors;
	for (int i = 0; i < column.size(); i += 9) {
		subvectors.push_back(column.segment(i, 9));
	}
	
	std::sort(subvectors.begin(), subvectors.end(), indexCompare);

	for (int i = 0; i < column.size(); i += 9) {
		column.segment(i, 9) = subvectors[i/9];
	}
}

const bool& InvarianceEquationSolver::Solution::isGood() const
{
	return mIsGood;
}

const InvarianceEquationSolver::Solution::Origin& InvarianceEquationSolver::Solution::origin() const
{
	return mOrigin;
}

const MyVectorXcd& InvarianceEquationSolver::Solution::phase(size_t ith) const
{
	return mPhases.at(ith);
}

int InvarianceEquationSolver::Solution::phases() const
{
	return mPhases.size();
}

void InvarianceEquationSolver::Solution::setActualZero()
{
	MyMatrixXcd::setActualZero();
	for (auto& phase : mPhases) {
		phase.setActualZero();
	}
}

void InvarianceEquationSolver::Solution::switchForm()
{
	*this = mOriginalForm;
	if (mForm == Form::Particular) {
		takeGeneralForm();
	}
	if (mForm == Form::General) {
		takeParticularForm();
	}
}

void InvarianceEquationSolver::Solution::extractColumnAndPhase()
{
	mPhases.resize(cols());
	int i = 0;
	for (auto&& col : colwise()) {
		::extractColumnAndPhase(col, mPhases[i++]);
	}
}

void InvarianceEquationSolver::Solution::setFirstElementTo(const std::complex<double>& value)
{
	for (auto&& col : colwise()) {
		::setFirstElementTo(col, value);
	}
}

void InvarianceEquationSolver::Solution::sortByIndex()
{
	for (auto&& col : colwise()) {
		::sortByIndex(col);
	}
}

void InvarianceEquationSolver::Solution::takeParticularForm()
{
	setFirstElementTo(1.0);
}

void InvarianceEquationSolver::Solution::takeGeneralForm()
{
	sortByIndex();
	setFirstElementTo(1.0);
	extractColumnAndPhase();
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles& particles, const Form& form)
{
	mIntersectionBasis.mForm = form;
	setParticles(particles);
}

InvarianceEquationSolver::InvarianceEquationSolver(const Group& group, const Particles& particles, const Form& form)
{
	mIntersectionBasis.mForm = form;
	setParticles(particles);
	compute(group);
}

InvarianceEquationSolver::InvarianceEquationSolver(const Group& group, const std::vector<size_t>& combination, const Particles& particles, const Form& form)
{
	mIntersectionBasis.mForm = form;
	setParticles(particles);
	compute(group, combination);
}

void InvarianceEquationSolver::compute(const Group& group)
{
	std::map<char, size_t> uniqueCoeffs = findUniqueChars(mShape);
	std::vector<size_t> partialCombination(uniqueCoeffs.size(), 1);
	std::vector<size_t> extendedCombination;
	int index = uniqueCoeffs.size() - 1;

	mIntersectionBases.clear();
	while (true) {
		extendedCombination = extendCombination(mShape, partialCombination, uniqueCoeffs);
		compute(group, extendedCombination);
		if (mEquationState == EquationState::NoProblem) {
			mIntersectionBases.push_back(mIntersectionBasis);
		}

		partialCombination[index]++;
		while (partialCombination[index] == group.numberOfRepresentations() + 1) {
			if (index == 0) {
				reset();
				return;
			}
			partialCombination[index] = 1;
			partialCombination[--index]++;
		}
		index = uniqueCoeffs.size() - 1;
	}
}

void InvarianceEquationSolver::compute(const Group& group, const std::vector<size_t>& combination)
{
	reset();
	generateInvarianceMatrices(group, combination);
	findEigenvectors1();
	findIntersectionBasis();

	if (mEquationState == EquationState::NoProblem) {
		mIntersectionBasis.mOriginalForm = mIntersectionBasis;
		mIntersectionBasis.mOrigin = { group.structure(), combination };
		mIntersectionBasis.mIsGood = checkSolution();
		if (mIntersectionBasis.mForm == Form::Particular) {
			mIntersectionBasis.takeParticularForm();
		}
		if (mIntersectionBasis.mForm == Form::General) {
			mIntersectionBasis.takeGeneralForm();
		}
	}
}

const std::vector<MyMatrixXcd>& InvarianceEquationSolver::eigenvectors1() const
{
	return mEigenvectors1;
}

const std::vector<MyMatrixXcd>& InvarianceEquationSolver::invarianceMatrices() const
{
	return mInvarianceMatrices;
}

const InvarianceEquationSolver::Solution& InvarianceEquationSolver::solution() const
{
	return mIntersectionBasis;
}

const std::vector<InvarianceEquationSolver::Solution>& InvarianceEquationSolver::solutions() const
{
	return mIntersectionBases;
}

bool InvarianceEquationSolver::checkSolution() const
{
	for (const auto& solution : mIntersectionBasis.colwise()) {
		for (const auto& invarianceMatrix : mInvarianceMatrices) {
			if ((invarianceMatrix * solution).isApprox(solution, 0.0001) == false) {
				return false;
			}
		}
	}

	return true;
}

void InvarianceEquationSolver::findEigenvector1(const MyMatrixXcd& matrix)
{
	Eigen::ComplexEigenSolver<Eigen::MatrixXcd> ces;
	ces.compute(matrix);

	MyMatrixXcd eigenvector1(matrix.rows(), (ces.eigenvectors()).size());
	size_t numberOfEigenvector1 = 0;
	bool isEigenvalue1 = false;

	for (int i = 0; i < (ces.eigenvalues()).size(); ++i) {
		isEigenvalue1 = (abs(real(ces.eigenvalues()[i]) - 1.0) < 0.0001) && (abs(imag(ces.eigenvalues()[i])) < 0.0001);
		if (isEigenvalue1) {
			eigenvector1.col(numberOfEigenvector1) = (ces.eigenvectors()).col(i);
			++numberOfEigenvector1;
		}
	}

	if (numberOfEigenvector1 == 0) {
		mEquationState = EquationState::NoEigenvectors;
		mEigenvectors1.clear();
		return;
	}

	eigenvector1.conservativeResize(matrix.rows(), numberOfEigenvector1);
	mEigenvectors1.push_back(eigenvector1);
}

void InvarianceEquationSolver::findEigenvectors1()
{
	size_t invarianceMatrixNumber = 0;
	do {
		findEigenvector1(mInvarianceMatrices[invarianceMatrixNumber]);
		++invarianceMatrixNumber;
	} while ((mEquationState != EquationState::NoEigenvectors) && invarianceMatrixNumber < mInvarianceMatrices.size());
}

void InvarianceEquationSolver::findIntersectionBasis()
{
	if (mEquationState == EquationState::NoEigenvectors) { return; }

	size_t eigenspaceNumber = 1;
	mIntersectionBasis = mEigenvectors1[0];
	do {
		findIntersectionBasis(mIntersectionBasis, mEigenvectors1[eigenspaceNumber]);
		++eigenspaceNumber;
	} while ((mEquationState != EquationState::NoEigensubspace) && (eigenspaceNumber < mEigenvectors1.size()));
}

void InvarianceEquationSolver::findIntersectionBasis(const MyMatrixXcd& matrix1, const MyMatrixXcd& matrix2)
{
	MyMatrixXcd matrixOf2Eigenspaces(matrix1.rows(), matrix1.cols() + matrix2.cols());
	matrixOf2Eigenspaces << matrix1, -1.0 * matrix2;

	Eigen::FullPivLU<Eigen::MatrixXcd> lu(matrixOf2Eigenspaces);
	if (!lu.dimensionOfKernel()) {
		mEquationState = EquationState::NoEigensubspace;
		mIntersectionBasis.resize(0, 0);
		return;
	}

	MyMatrixXcd nullSpace = lu.kernel();
	MyMatrixXcd intersectionBasis(matrix1.rows(), nullSpace.cols());
	MyVectorXcd baseVector;

	for (int i = 0; i < nullSpace.cols(); ++i) {
		baseVector.setZero(matrix1.rows());
		for (int j = 0; j < matrix1.cols(); ++j) {
			baseVector += nullSpace.col(i)(j) * (matrix1).col(j);
		}
		intersectionBasis.col(i) = baseVector;
	}

	mIntersectionBasis = intersectionBasis;
}

void InvarianceEquationSolver::generateInvarianceMatrices(const Group& group, const std::vector<size_t>& combination)
{
	std::vector<MyMatrix3cd> matrices;

	for (size_t i = 1; i <= group.numberOfGenerators(); ++i) {
		for (size_t c : combination) {
			matrices.push_back(group.generator(i)[c - 1]);
		}
		generateInvarianceMatrix(matrices);
		matrices.clear();
	}
}

void InvarianceEquationSolver::generateInvarianceMatrix(std::vector<MyMatrix3cd>& matrices)
{
	if (matrices.size() != mOperation.size()) { return; }

	for (size_t i = 0; i < mOperation.size(); ++i) {
		if (mOperation[i] == 'A') {
			matrices[i].adjointInPlace();
		}
		if (mOperation[i] == 'T') {
			matrices[i].transposeInPlace();
		}
	}

	std::vector<MyMatrixXcd> results(matrices.size() - 1);

	results[0] = kroneckerProduct(matrices[0], matrices[1]);
	for (size_t i = 1; i < results.size(); ++i) {
		results[i] = kroneckerProduct(results[i - 1], matrices[i + 1]);
	}

	mInvarianceMatrices.push_back(results.back());
}

void InvarianceEquationSolver::reset()
{
	mEquationState = EquationState::NoProblem;
	mInvarianceMatrices.clear();
	mEigenvectors1.clear();
	mIntersectionBasis.resize(0, 0);
}

void InvarianceEquationSolver::setParticles(const Particles& particles)
{
	const std::string shapes[3] = { "ABC", "ABC", "AABB" };
	const std::string operations[3] = { "AAT", "TAT", "TTAA" };

	mShape = shapes[static_cast<int>(particles)];
	mOperation = operations[static_cast<int>(particles)];
}
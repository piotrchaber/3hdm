#include "3hdm/invariance_equation_solver.h"

#include "3hdm/utilities.h"
#include "Eigen/Eigenvalues"
#include "unsupported/Eigen/KroneckerProduct"

namespace
{

MatrixForm::Form formConverter(const InvarianceEquationSolver::Solution::Form form)
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

}

bool InvarianceEquationSolver::Solution::isGood() const
{
    return is_good_;
}

InvarianceEquationSolver::Solution::Form InvarianceEquationSolver::Solution::form() const
{
    return form_;
}

const InvarianceEquationSolver::Solution::Origin & InvarianceEquationSolver::Solution::origin() const
{
    return origin_;
}

const MyVectorXcd & InvarianceEquationSolver::Solution::phase(const size_t ith) const
{
    return phases_.at(ith);
}

size_t InvarianceEquationSolver::Solution::phases() const
{
    return phases_.size();
}

void InvarianceEquationSolver::Solution::switchFormTo(const Form form)
{
    if (form != form_)
    {
        form_ = form;
        takeForm();
    }
}

void InvarianceEquationSolver::Solution::takeForm()
{
    const MatrixForm matrix_form(initial_form_, formConverter(form_));
    phases_ = matrix_form.phases();
    *this = matrix_form.matrix();
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles particles, const InvarianceEquationSolver::Solution::Form form)
{
    setParticles(particles);
    setForm(form);
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles particles, const InvarianceEquationSolver::Solution::Form form, const Group & group)
{
    setParticles(particles);
    setForm(form);
    compute(group);
}

InvarianceEquationSolver::InvarianceEquationSolver(const Particles particles, const InvarianceEquationSolver::Solution::Form form, const Group & group, const std::vector<size_t> & combination)
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
    if (EquationState::NoEigenvectors == equation_state_) { return; }
    findIntersectionBasis();
    if (EquationState::NoEigensubspace == equation_state_) { return; }
    prepareSolution(group, combination);
}

void InvarianceEquationSolver::compute(const Group & group)
{
    Combination combination(shape_, group.numberOfRepresentations());

    solutions_.clear();
    do
    {
        compute(group, combination.get());
        if (EquationState::NoProblem == equation_state_)
        {
            solutions_.push_back(solution_);
        }
    } while (combination.next());
    reset();
}

const std::vector<MyMatrixXcd> & InvarianceEquationSolver::eigenvectors1() const
{
    return eigenvectors1_;
}

const std::vector<MyMatrixXcd> & InvarianceEquationSolver::invarianceMatrices() const
{
    return invariance_matrices_;
}

const MyMatrixXcd & InvarianceEquationSolver::intersectionBasis() const
{
    return intersection_basis_;
}

const InvarianceEquationSolver::Solution & InvarianceEquationSolver::solution() const
{
    return solution_;
}

const std::vector<InvarianceEquationSolver::Solution> & InvarianceEquationSolver::solutions() const
{
    return solutions_;
}

bool InvarianceEquationSolver::checkSolution() const
{
    for (const auto & solution : solution_.initial_form_.colwise())
    {
        for (const auto & invariance_matrix : invariance_matrices_)
        {
            if (false == (invariance_matrix * solution).isApprox(solution, 0.0001))
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
    MyMatrixXcd eigenvectors1{};

    for (auto const invariance_matrix : invariance_matrices_)
    {
        eigenvectors1 = findEigenvectors1(invariance_matrix);
        if (0 == eigenvectors1.cols())
        {
            equation_state_ = EquationState::NoEigenvectors;
            return;
        }
        eigenvectors1_.push_back(eigenvectors1);
    }
}

MyMatrixXcd InvarianceEquationSolver::findIntersectionBasis(const MyMatrixXcd & lhs_matrix, const MyMatrixXcd & rhs_matrix)
{
    const MyMatrixXcd null_space{eigenspace(lhs_matrix, rhs_matrix)};
    MyMatrixXcd intersection_basis(lhs_matrix.rows(), null_space.cols());
    MyVectorXcd base_vector{};

    for (auto i = 0; i < null_space.cols(); ++i)
    {
        base_vector.setZero(lhs_matrix.rows());
        for (auto j = 0; j < lhs_matrix.cols(); ++j)
        {
            base_vector += null_space.col(i)(j) * lhs_matrix.col(j);
        }
        intersection_basis.col(i) = base_vector;
    }

    return intersection_basis;
}

void InvarianceEquationSolver::findIntersectionBasis()
{
    intersection_basis_ = eigenvectors1_.at(0);
    for (auto i = 1; i < eigenvectors1_.size(); ++i)
    {
        intersection_basis_ = findIntersectionBasis(intersection_basis_, eigenvectors1_.at(i));
        if (intersection_basis_.isZero())
        {
            equation_state_ = EquationState::NoEigensubspace;
            return;
        }
    }
}

std::vector<MyMatrix3cd> InvarianceEquationSolver::prepareMatrices(const Group & group, const size_t ith_generator, const std::vector<size_t> & combination)
{
    std::vector<MyMatrix3cd> matrices{group.generator(ith_generator, combination)};

    for (auto i = 0; i < operation_.size(); ++i)
    {
        if (operation_[i] == 'A')
        {
            matrices[i].adjointInPlace();
        }
        if (operation_[i] == 'T')
        {
            matrices[i].transposeInPlace();
        }
    }

    return matrices;
}

MyMatrixXcd InvarianceEquationSolver::generateInvarianceMatrix(const Group & group, const size_t ith_generator, const std::vector<size_t> & combination)
{
    const std::vector<MyMatrix3cd> matrices{prepareMatrices(group, ith_generator, combination)};
    return kroneckerProduct(matrices);
}

void InvarianceEquationSolver::generateInvarianceMatrices(const Group & group, const std::vector<size_t> & combination)
{
    MyMatrixXcd invariance_matrix{};

    for (auto i = 1; i <= group.numberOfGenerators(); ++i)
    {
        invariance_matrix = generateInvarianceMatrix(group, i, combination);
        invariance_matrices_.push_back(invariance_matrix);
    }
}

void InvarianceEquationSolver::prepareSolution(const Group & group, const std::vector<size_t> & combination)
{
    solution_.initial_form_ = intersection_basis_;
    solution_.origin_ = { group.structure(), combination };
    solution_.is_good_ = checkSolution();
    solution_.takeForm();
}

void InvarianceEquationSolver::reset()
{
    equation_state_ = EquationState::NoProblem;
    invariance_matrices_.clear();
    eigenvectors1_.clear();
    intersection_basis_.resize(0, 0);
    solution_.resize(0, 0);
}

void InvarianceEquationSolver::setForm(const InvarianceEquationSolver::Solution::Form form)
{
    solution_.form_ = form;
}

void InvarianceEquationSolver::setParticles(const Particles particles)
{
    const std::string shapes[3] = { "ABC", "ABC", "AABB" };
    const std::string operations[3] = { "AAT", "TAT", "TTAA" };

    shape_ = shapes[static_cast<int>(particles)];
    operation_ = operations[static_cast<int>(particles)];
}

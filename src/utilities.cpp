#include "3hdm/utilities.h"

#include <complex>

#include "unsupported/Eigen/KroneckerProduct"

MyMatrixXcd kroneckerProduct(const std::vector<MyMatrix3cd> & matrices)
{
    MyMatrixXcd result{kroneckerProduct(matrices[0], matrices[1])};

    for (auto i = 2; i < matrices.size(); ++i)
    {
        result = kroneckerProduct(result, matrices[i]);
    }

    return result;
}

bool isEigenvalue(const std::complex<double> & eigenvalue, double value)
{
    return (abs(std::real(eigenvalue) - value) < 0.0001) && (abs(std::imag(eigenvalue)) < 0.0001);
}

MyMatrixXcd eigenvectors(const MyMatrixXcd & matrix, double value)
{
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> ces{};
    ces.compute(matrix);

    const auto eigenvalues = ces.eigenvalues();
    const auto eigenvectors = ces.eigenvectors();
    const auto number_of_eigenvectors_value = std::count_if(eigenvalues.cbegin(), eigenvalues.cend(), [&](auto element) { return isEigenvalue(element, value); });

    MyMatrixXcd eigenvectors_value(matrix.rows(), number_of_eigenvectors_value);
    int col{0};

    for (auto i = 0; i < eigenvalues.size(); ++i)
    {
        if (isEigenvalue(eigenvalues[i], value))
        {
            eigenvectors_value.col(col++) = eigenvectors.col(i);
        }
    }

    return eigenvectors_value;
}

MyMatrixXcd eigenspace(const MyMatrixXcd & lhs_matrix, const MyMatrixXcd & rhs_matrix)
{
    MyMatrixXcd matrix_of_two_eigenspaces(lhs_matrix.rows(), lhs_matrix.cols() + rhs_matrix.cols());
    matrix_of_two_eigenspaces << lhs_matrix, -1.0 * rhs_matrix;

    Eigen::FullPivLU<Eigen::MatrixXcd> lu{};
    lu.compute(matrix_of_two_eigenspaces);

    return lu.kernel();
}

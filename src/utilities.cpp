#include "3hdm/utilities.h"

#include <complex>
#include "unsupported/Eigen/KroneckerProduct"

MyMatrixXcd kroneckerProduct(const std::vector<MyMatrix3cd> & matrices)
{
    MyMatrixXcd result{kroneckerProduct(matrices[0], matrices[1])};

    for (size_t i = 2; i < matrices.size(); ++i)
    {
        result = kroneckerProduct(result, matrices[i]);
    }

    return result;
}

bool isEigenvalue(std::complex<double> eigenvalue, double value)
{
    return (abs(std::real(eigenvalue) - value) < 0.0001) && (abs(std::imag(eigenvalue)) < 0.0001);
}

MyMatrixXcd eigenvectors(const MyMatrixXcd & matrix, double value)
{
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> ces;
    ces.compute(matrix);

    auto eigenvalues = ces.eigenvalues();
    auto eigenvectors = ces.eigenvectors();
    auto neigenvectorsValue = std::count_if(eigenvalues.cbegin(), eigenvalues.cend(), [&](auto element) { return isEigenvalue(element, value); });

    MyMatrixXcd eigenvectorsValue(matrix.rows(), neigenvectorsValue);
    int col{0};

    for (auto i = 0; i < eigenvalues.size(); ++i)
    {
        if (isEigenvalue(eigenvalues[i], value))
        {
            eigenvectorsValue.col(col++) = eigenvectors.col(i);
        }
    }

    return eigenvectorsValue;
}

MyMatrixXcd eigenspace(const MyMatrixXcd & matrix1, const MyMatrixXcd & matrix2)
{
    MyMatrixXcd matrixOf2Eigenspaces(matrix1.rows(), matrix1.cols() + matrix2.cols());
    matrixOf2Eigenspaces << matrix1, -1.0 * matrix2;

    Eigen::FullPivLU<Eigen::MatrixXcd> lu;
    lu.compute(matrixOf2Eigenspaces);

    return lu.kernel();
}

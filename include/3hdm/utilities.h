#ifndef UTILITIES_H
#define UTILITIES_H

#include "3hdm/mymatrix.h"

MyMatrixXcd kroneckerProduct(const std::vector<MyMatrix3cd> & matrices);
bool isEigenvalue(std::complex<double> eigenvalue, double value);
MyMatrixXcd eigenvectors(const MyMatrixXcd & matrix, double eigenvalue);
MyMatrixXcd eigenspace(const MyMatrixXcd & matrix1, const MyMatrixXcd & matrix2);

#endif // UTILITIES_H

#ifndef INCLUDE_3HDM_UTILITIES_H
#define INCLUDE_3HDM_UTILITIES_H

#include "3hdm/mymatrix.h"

MyMatrixXcd kroneckerProduct(const std::vector<MyMatrix3cd> & matrices);
bool isEigenvalue(const std::complex<double> & eigenvalue, double value);
MyMatrixXcd eigenvectors(const MyMatrixXcd & matrix, double eigenvalue);
MyMatrixXcd eigenspace(const MyMatrixXcd & lhs_matrix, const MyMatrixXcd & rhs_matrix);

#endif  // INCLUDE_3HDM_UTILITIES_H

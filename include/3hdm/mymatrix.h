#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "Eigen/Dense"
#include "mymatrix_simpl.h"

template<typename _Scalar, int _Rows, int _Cols>
class MyMatrix : public Eigen::Matrix<_Scalar, _Rows, _Cols>
{
public:
	using Eigen::Matrix<_Scalar, _Rows, _Cols>::Matrix;
	virtual ~MyMatrix() = default;
	
	virtual void setActualZero();
	void load(std::stringstream & ss);
	void load(const std::string & fileName, const std::string & fileDir);
};

typedef MyMatrix<std::complex<double>, 2, 2> MyMatrix2cd;
typedef MyMatrix<std::complex<float>, 2, 2> MyMatrix2cf;
typedef MyMatrix<double, 2, 2> MyMatrix2d;
typedef MyMatrix<float, 2, 2> MyMatrix2f;

typedef MyMatrix<std::complex<double>, 3, 3> MyMatrix3cd;
typedef MyMatrix<std::complex<float>, 3, 3> MyMatrix3cf;
typedef MyMatrix<double, 3, 3> MyMatrix3d;
typedef MyMatrix<float, 3, 3> MyMatrix3f;

typedef MyMatrix<std::complex<double>, 4, 4> MyMatrix4cd;
typedef MyMatrix<std::complex<float>, 4, 4> MyMatrix4cf;
typedef MyMatrix<double, 4, 4> MyMatrix4d;
typedef MyMatrix<float, 4, 4> MyMatrix4f;

typedef MyMatrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> MyMatrixXcd;
typedef MyMatrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic> MyMatrixXcf;
typedef MyMatrix<double, Eigen::Dynamic, Eigen::Dynamic> MyMatrixXd;
typedef MyMatrix<float, Eigen::Dynamic, Eigen::Dynamic> MyMatrixXf;

typedef MyMatrix<std::complex<double>, 1, 2> MyRowVector2cd;
typedef MyMatrix<std::complex<float>, 1, 2> MyRowVector2cf;
typedef MyMatrix<double, 1, 2> MyRowVector2d;
typedef MyMatrix<float, 1, 2> MyRowVector2f;

typedef MyMatrix<std::complex<double>, 1, 3> MyRowVector3cd;
typedef MyMatrix<std::complex<float>, 1, 3> MyRowVector3cf;
typedef MyMatrix<double, 1, 3> MyRowVector3d;
typedef MyMatrix<float, 1, 3> MyRowVector3f;

typedef MyMatrix<std::complex<double>, 1, 4> MyRowVector4cd;
typedef MyMatrix<std::complex<float>, 1, 4> MyRowVector4cf;
typedef MyMatrix<double, 1, 4> MyRowVector4d;
typedef MyMatrix<float, 1, 4> MyRowVector4f;

typedef MyMatrix<std::complex<double>, 1, Eigen::Dynamic> MyRowVectorXcd;
typedef MyMatrix<std::complex<float>, 1, Eigen::Dynamic> MyRowVectorXcf;
typedef MyMatrix<double, 1, Eigen::Dynamic> MyRowVectorXd;
typedef MyMatrix<float, 1, Eigen::Dynamic> MyRowVectorXf;

typedef MyMatrix<std::complex<double>, 2, 1> MyVector2cd;
typedef MyMatrix<std::complex<float>, 2, 1> MyVector2cf;
typedef MyMatrix<double, 2, 1> MyVector2d;
typedef MyMatrix<float, 2, 1> MyVector2f;

typedef MyMatrix<std::complex<double>, 3, 1> MyVector3cd;
typedef MyMatrix<std::complex<float>, 3, 1> MyVector3cf;
typedef MyMatrix<double, 3, 1> MyVector3d;
typedef MyMatrix<float, 3, 1> MyVector3f;

typedef MyMatrix<std::complex<double>, 4, 1> MyVector4cd;
typedef MyMatrix<std::complex<float>, 4, 1> MyVector4cf;
typedef MyMatrix<double, 4, 1> MyVector4d;
typedef MyMatrix<float, 4, 1> MyVector4f;

typedef MyMatrix<std::complex<double>, Eigen::Dynamic, 1> MyVectorXcd;
typedef MyMatrix<std::complex<float>, Eigen::Dynamic, 1> MyVectorXcf;
typedef MyMatrix<double, Eigen::Dynamic, 1> MyVectorXd;
typedef MyMatrix<float, Eigen::Dynamic, 1> MyVectorXf;

typedef MyMatrix<std::complex<double>, 2, Eigen::Dynamic> MyMatrix2Xcd;
typedef MyMatrix<std::complex<float>, 2, Eigen::Dynamic> MyMatrix2Xcf;
typedef MyMatrix<double, 2, Eigen::Dynamic> MyMatrix2Xd;
typedef MyMatrix<float, 2, Eigen::Dynamic> MyMatrix2Xf;

typedef MyMatrix<std::complex<double>, Eigen::Dynamic, 2> MyMatrixX2cd;
typedef MyMatrix<std::complex<float>, Eigen::Dynamic, 2> MyMatrixX2cf;
typedef MyMatrix<double, Eigen::Dynamic, 2> MyMatrixX2d;
typedef MyMatrix<float, Eigen::Dynamic, 2> MyMatrixX2f;

template <typename _Scalar, int _Rows, int _Cols>
void MyMatrix<_Scalar, _Rows, _Cols>::setActualZero()
{
	return setActualZeroImpl<MyMatrix, Eigen::NumTraits<_Scalar>::IsComplex>()(*this);
}

template <typename _Scalar, int _Rows, int _Cols>
void MyMatrix<_Scalar, _Rows, _Cols>::load(std::stringstream & ss)
{
	if (ss.str() == "")
	{
		std::cerr << "Stringstream is empty!" << '\n';
		*this = MyMatrix<_Scalar, Eigen::Dynamic, Eigen::Dynamic>(0, 0);
		return;
	}

	_Scalar scalar;
	std::vector<_Scalar> scalars;
	while (ss >> scalar) scalars.push_back(scalar);

	if (scalars.size() % _Rows != 0)
	{
		std::cerr << "Wrong number of elements!" << '\n';
		*this = MyMatrix<_Scalar, Eigen::Dynamic, Eigen::Dynamic>(0, 0);
		return;
	}

	*this = MyMatrix<_Scalar, Eigen::Dynamic, Eigen::Dynamic>(_Rows, _Cols);
	for (size_t row = 0; row < _Rows; ++row)
	{
		for (size_t col = 0; col < _Cols; ++col)
		{
			this->operator()(row, col) = scalars[(row * _Rows) + col];
		}
	}
}

template <typename _Scalar, int _Rows, int _Cols>
void MyMatrix<_Scalar, _Rows, _Cols>::load(const std::string & fileName, const std::string & fileDir)
{
	auto filePath = std::filesystem::path(fileDir + '/' + fileName);
	std::fstream ifile;
	ifile.open(filePath, std::ios::in);
	if(ifile.is_open() == false)
	{
		std::cerr << filePath << " file not opening properly!" << '\n';
		exit(EXIT_FAILURE);
	}
	
	std::stringstream ss;
	std::string matrixRow;
	while(std::getline(ifile, matrixRow))
	{
		ss << matrixRow + "\n";
	}
	
	load(ss);
}

#endif // MYMATRIX_H

// TODO: loadFromFile method of MyMatrixX class needs to provide any information about matrix dimension
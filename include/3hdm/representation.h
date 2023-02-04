#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "mymatrix.h"

template <typename _Scalar, int _Dimension>
class Representation
{
public:
	Representation() = default;
	explicit Representation(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>>& matrices);
	virtual ~Representation() = default;

	static const int& dimension();
	void load(const std::string& fileName, const std::string& fileDir);
	const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>>& matrices() const;
	const MyMatrix<_Scalar, _Dimension, _Dimension>& matrix(size_t ith) const;
	size_t numberOfMatrices() const;
	void setMatrices(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>>& matrices);

protected:
	void checkDimension();

private:
	std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> mMatrices;
	static int mDimension;
};

typedef Representation<std::complex<double>, 2> Representation2cd;
typedef Representation<std::complex<float>, 2> Representation2cf;
typedef Representation<double, 2> Representation2d;
typedef Representation<float, 2> Representation2f;

typedef Representation<std::complex<double>, 3> Representation3cd;
typedef Representation<std::complex<float>, 3> Representation3cf;
typedef Representation<double, 3> Representation3d;
typedef Representation<float, 3> Representation3f;

typedef Representation<std::complex<double>, 4> Representation4cd;
typedef Representation<std::complex<float>, 4> Representation4cf;
typedef Representation<double, 4> Representation4d;
typedef Representation<float, 4> Representation4f;

typedef Representation<std::complex<double>, Eigen::Dynamic> RepresentationXcd;
typedef Representation<std::complex<float>, Eigen::Dynamic> RepresentationXcf;
typedef Representation<double, Eigen::Dynamic> RepresentationXd;
typedef Representation<float, Eigen::Dynamic> RepresentationXf;

template <typename _Scalar, int _Dimension>
int Representation<_Scalar, _Dimension>::mDimension = _Dimension == Eigen::Dynamic ? 0 : _Dimension;

template <typename _Scalar, int _Dimension>
Representation<_Scalar, _Dimension>::Representation(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>>& matrices)
	: mMatrices(matrices)
{
	checkDimension();
}

template <typename _Scalar, int _Dimension>
const int& Representation<_Scalar, _Dimension>::dimension()
{
	return mDimension;
}

template <typename _Scalar, int _Dimension>
void Representation<_Scalar, _Dimension>::load(const std::string& fileName, const std::string& fileDir)
{
	auto filePath = std::filesystem::path(fileDir + '/' + fileName);
	std::fstream ifile;
	ifile.open(filePath, std::ios::in);
	if (ifile.is_open() == false) {
		std::cerr << filePath << " file not opening properly!" << std::endl;
		exit(EXIT_FAILURE);
	}

	MyMatrix<_Scalar, _Dimension, _Dimension> matrix;
	std::string matrixRow;
	std::stringstream ss;
	size_t dimController = 0;

	mMatrices.clear();
	while (std::getline(ifile, matrixRow)) {
		ss << matrixRow + "\n";
		if (++dimController == _Dimension) {
			matrix.load(ss);
			mMatrices.push_back(matrix);
			ss.str(std::string());
			ss.clear();
			dimController = 0;
		}
	}
}

template <typename _Scalar, int _Dimension>
const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>>& Representation<_Scalar, _Dimension>::matrices() const
{
	return mMatrices;
}

template<typename _Scalar, int _Dimension>
const MyMatrix<_Scalar, _Dimension, _Dimension>& Representation<_Scalar, _Dimension>::matrix(size_t ith) const
{
	return mMatrices.at(ith);
}

template <typename _Scalar, int _Dimension>
size_t Representation<_Scalar, _Dimension>::numberOfMatrices() const
{
	return mMatrices.size();
}

template <typename _Scalar, int _Dimension>
void Representation<_Scalar, _Dimension>::setMatrices(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>>& matrices)
{
	mMatrices = matrices;
	checkDimension();
}

template<typename _Scalar, int _Dimension>
void Representation<_Scalar, _Dimension>::checkDimension()
{
	if (mDimension == 0 && mMatrices.empty() == false) {
		int cols = mMatrices.front().cols();
		int rows = mMatrices.front().rows();
		assert(cols == rows && "Matrix representation must be square");
		std::for_each(mMatrices.cbegin() + 1, mMatrices.cend(), [&](const auto& matrix)
			{ assert(cols == matrix.cols() && rows == matrix.rows()
				&& "All matrices must be of the same dimension"); });
		mDimension = cols;
	}
}

// TODO: loadFromFile method for RepresentationX class needs to provide any information about dimension (solution: introduce ctr with dimension as an argument)
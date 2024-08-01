#ifndef INCLUDE_3HDM_REPRESENTATION_H
#define INCLUDE_3HDM_REPRESENTATION_H

#include <filesystem>
#include <string>
#include <vector>

#include "mymatrix.h"

template <typename _Scalar, int _Dimension>
class Representation
{
public:
    Representation() = default;
    explicit Representation(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> & matrices);
    virtual ~Representation() = default;

    static int dimension();
    void load(const std::string & file_name, const std::string & file_directory);
    const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> & matrices() const;
    const MyMatrix<_Scalar, _Dimension, _Dimension> & matrix(const size_t ith) const;
    size_t numberOfMatrices() const;
    void setMatrices(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> & matrices);

private:
    void checkDimension();

    std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> matrices_{};
    static int dimension_;
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
int Representation<_Scalar, _Dimension>::dimension_ = _Dimension == Eigen::Dynamic ? 0 : _Dimension;

template <typename _Scalar, int _Dimension>
Representation<_Scalar, _Dimension>::Representation(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> & matrices)
    : matrices_(matrices)
{
    checkDimension();
}

template <typename _Scalar, int _Dimension>
int Representation<_Scalar, _Dimension>::dimension()
{
    return dimension_;
}

template <typename _Scalar, int _Dimension>
void Representation<_Scalar, _Dimension>::load(const std::string & file_name, const std::string & file_directory)
{
    const std::filesystem::path file_path{file_directory + '/' + file_name};
    std::fstream ifile{};

    ifile.open(file_path, std::ios::in);
    if (false == ifile.is_open())
    {
        std::cerr << file_path << " file not opening properly!" << '\n';
        exit(EXIT_FAILURE);
    }

    MyMatrix<_Scalar, _Dimension, _Dimension> matrix{};
    std::string matrix_row{};
    std::stringstream ss{};
    size_t dimension{0};

    matrices_.clear();
    while (std::getline(ifile, matrix_row))
    {
        ss << matrix_row + "\n";
        if (++dimension == _Dimension)
        {
            matrix.load(ss);
            matrices_.push_back(matrix);
            ss.str(std::string());
            ss.clear();
            dimension = 0;
        }
    }
}

template <typename _Scalar, int _Dimension>
const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> & Representation<_Scalar, _Dimension>::matrices() const
{
    return matrices_;
}

template<typename _Scalar, int _Dimension>
const MyMatrix<_Scalar, _Dimension, _Dimension> & Representation<_Scalar, _Dimension>::matrix(const size_t ith) const
{
    return matrices_.at(ith);
}

template <typename _Scalar, int _Dimension>
size_t Representation<_Scalar, _Dimension>::numberOfMatrices() const
{
    return matrices_.size();
}

template <typename _Scalar, int _Dimension>
void Representation<_Scalar, _Dimension>::setMatrices(const std::vector<MyMatrix<_Scalar, _Dimension, _Dimension>> & matrices)
{
    matrices_ = matrices;
    checkDimension();
}

template<typename _Scalar, int _Dimension>
void Representation<_Scalar, _Dimension>::checkDimension()
{
    if ((0 == dimension_) && (false == matrices_.empty()))
    {
        const Eigen::Index cols{matrices_.front().cols()};
        const Eigen::Index rows{matrices_.front().rows()};

        assert(cols == rows && "Matrix representation must be square");
        std::for_each(matrices_.cbegin() + 1, matrices_.cend(), [&](const auto & matrix) {
            assert((cols == matrix.cols()) && (rows == matrix.rows())
            && "All matrices must be of the same dimension"); });

        dimension_ = cols;
    }
}

#endif  // INCLUDE_3HDM_REPRESENTATION_H

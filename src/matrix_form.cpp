#include "3hdm/matrix_form.h"

namespace
{

bool indexCompare(const MyVectorXcd & lhs_vector, const MyVectorXcd & rhs_vector)
{
    auto isNonZero = [](const auto & element) { return abs(element) > 0.000001; };
    auto firstNonZeroElement = [&](const auto & block) { return std::find_if(block.cbegin(), block.cend(), isNonZero); };
    auto indexOfFirstNonZeroElement = [&](const auto & block) { return std::distance(block.cbegin(), firstNonZeroElement(block)); };

    return indexOfFirstNonZeroElement(lhs_vector) < indexOfFirstNonZeroElement(rhs_vector);
}

void sortByIndex(MyMatrixXcd::ColXpr & column)
{
    std::vector<MyVectorXcd> subvectors{};
    for (auto i = 0; i < column.size(); i += 9)
    {
        subvectors.push_back(column.segment(i, 9));
    }

    std::sort(subvectors.begin(), subvectors.end(), indexCompare);
    for (auto i = 0; i < column.size(); i += 9)
    {
        column.segment(i, 9) = subvectors[i/9];
    }
}

void setFirstElementTo(MyMatrixXcd::ColXpr & column, const std::complex<double> & value)
{
    auto isNonZero = [](const auto & element) { return abs(element) > 0.000001; };
    auto isZero = [&](const auto & block) { return std::none_of(block.cbegin(), block.cend(), isNonZero); };
    auto firstNonZeroElement = [&](const auto & block) { return *std::find_if(block.cbegin(), block.cend(), isNonZero); };
    auto isFirstNonZeroElementEqual = [&](const auto & block) { return abs(firstNonZeroElement(block) - value) < 0.000001; };

    if (isZero(column) || isFirstNonZeroElementEqual(column)) { return; }
    column = (value / firstNonZeroElement(column)) * column;
}

void extractColumnAndPhase(MyMatrixXcd::ColXpr & column, MyVectorXcd & phase)
{
    auto non_zero_elements = (column.array().abs() > 0.00001).count();
    if (non_zero_elements < 2) { return; }
    phase.resize(non_zero_elements - 1);

    Eigen::Index i{column.size() - 1};
    while (non_zero_elements > 1)
    {
        if (abs(column[i]) > 0.00001)
        {
            phase[non_zero_elements - 2] = column[i];
            column[i] = { 1.0,0.0 };
            --non_zero_elements;
        }
        --i;
    }
}

}

MatrixForm::MatrixForm(const MyMatrixXcd & matrix, const Form form)
    : matrix_(matrix)
    , phases_(std::vector<MyVectorXcd>(matrix.cols(), MyVectorXcd::Zero(1)))
{
    setMatrixForm(form);
}

const MyMatrixXcd & MatrixForm::matrix() const
{
    return matrix_;
}

const MyVectorXcd & MatrixForm::phase(const size_t ith) const
{
    return phases_.at(ith);
}

const std::vector<MyVectorXcd> & MatrixForm::phases() const
{
    return phases_;
}

void MatrixForm::setGeneralForm()
{
    sortByIndex();
    setFirstElementTo(1.0);
    setActualZero();
    extractColumnAndPhase();
}

void MatrixForm::setOriginalForm()
{
    setActualZero();
}

void MatrixForm::setParticularForm()
{
    setFirstElementTo(1.0);
    setActualZero();
}

void MatrixForm::setMatrixForm(const Form form)
{
    if (Form::Original == form)
    {
        setOriginalForm();
    }

    if (Form::Particular == form)
    {
        setParticularForm();
    }

    if (Form::General == form)
    {
        setGeneralForm();
    }
}

void MatrixForm::setActualZero()
{
    matrix_.setActualZero();
}

void MatrixForm::sortByIndex()
{
    for (auto && column : matrix_.colwise())
    {
        ::sortByIndex(column);
    }
}

void MatrixForm::setFirstElementTo(const std::complex<double> & value)
{
    for (auto && column : matrix_.colwise())
    {
        ::setFirstElementTo(column, value);
    }
}

void MatrixForm::extractColumnAndPhase()
{
    phases_.resize(matrix_.cols());
    size_t i{0};
    for (auto && column : matrix_.colwise())
    {
        ::extractColumnAndPhase(column, phases_[i++]);
    }
}

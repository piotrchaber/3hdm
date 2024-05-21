#include "3hdm/matrix_form.h"

MatrixForm::MatrixForm(const MyMatrixXcd & matrix, const Form & form)
    : mInitialMatrix(matrix)
    , mMatrix(matrix)
    , mForm(form)
    , mInitialPhases(std::vector<MyVectorXcd>(matrix.cols(), MyVectorXcd::Zero(1)))
    , mPhases(std::vector<MyVectorXcd>(matrix.cols(), MyVectorXcd::Zero(1)))
{
    setMatrixForm();
}

const MatrixForm::Form & MatrixForm::form() const
{
    return mForm;
}

const MyMatrixXcd & MatrixForm::matrix() const
{
    return mMatrix;
}

const MyVectorXcd & MatrixForm::phase(size_t ith) const
{
    return mPhases.at(ith);
}

const std::vector<MyVectorXcd> & MatrixForm::phases() const
{
    return mPhases;
}

void MatrixForm::switchFormTo(const Form & form)
{
    if (mForm == form) { return; }
    mMatrix = mInitialMatrix;
    mForm = form;
    mPhases = mInitialPhases;
    setMatrixForm();
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

void MatrixForm::setMatrixForm()
{
    if (mForm == Form::Original)
    {
        setOriginalForm();
    }

    if (mForm == Form::Particular)
    {
        setParticularForm();
    }

    if (mForm == Form::General)
    {
        setGeneralForm();
    }
}

void MatrixForm::setActualZero()
{
    mMatrix.setActualZero();
}

static bool indexCompare(const MyVectorXcd & lhs_vector, const MyVectorXcd & rhs_vector)
{
    auto isNonZero = [](const auto & element) { return abs(element) > 0.000001; };
    auto firstNonZeroElement = [&](const auto & block) { return std::find_if(block.cbegin(), block.cend(), isNonZero); };
    auto indexOfFirstNonZeroElement = [&](const auto & block) { return std::distance(block.cbegin(), firstNonZeroElement(block)); };

    return indexOfFirstNonZeroElement(lhs_vector) < indexOfFirstNonZeroElement(rhs_vector);
}

static void sortByIndex(MyMatrixXcd::ColXpr & column)
{
    std::vector<MyVectorXcd> subvectors;
    for (int i = 0; i < column.size(); i += 9)
    {
        subvectors.push_back(column.segment(i, 9));
    }
	
    std::sort(subvectors.begin(), subvectors.end(), indexCompare);
    for (int i = 0; i < column.size(); i += 9)
    {
        column.segment(i, 9) = subvectors[i/9];
    }
}

void MatrixForm::sortByIndex()
{
    for (auto && column : mMatrix.colwise())
    {
        ::sortByIndex(column);
    }
}

static void setFirstElementTo(MyMatrixXcd::ColXpr & column, const std::complex<double> & value)
{
    auto isNonZero = [](const auto & element) { return abs(element) > 0.000001; };
    auto isZero = [&](const auto & block) { return std::none_of(block.cbegin(), block.cend(), isNonZero); };
    auto firstNonZeroElement = [&](const auto & block) { return *std::find_if(block.cbegin(), block.cend(), isNonZero); };
    auto isFirstNonZeroElementEqual = [&](const auto & block) { return abs(firstNonZeroElement(block) - value) < 0.000001; };

    if (isZero(column) || isFirstNonZeroElementEqual(column)) { return; }
    column = (value / firstNonZeroElement(column)) * column;
}

void MatrixForm::setFirstElementTo(const std::complex<double> & value)
{
    for (auto && column : mMatrix.colwise())
    {
        ::setFirstElementTo(column, value);
    }
}

static void extractColumnAndPhase(MyMatrixXcd::ColXpr & column, MyVectorXcd & phase)
{
    auto nonZeroElements = (column.array().abs() > 0.00001).count();
    if (nonZeroElements < 2) { return; }
    phase.resize(nonZeroElements - 1);

    int i = column.size() - 1;
    while (nonZeroElements > 1)
    {
        if (abs(column[i]) > 0.00001)
        {
            phase[nonZeroElements - 2] = column[i];
            column[i] = { 1.0,0.0 };
            --nonZeroElements;
	}
        --i;
    }
}

void MatrixForm::extractColumnAndPhase()
{
    mPhases.resize(mMatrix.cols());
    size_t i = 0;
    for (auto && column : mMatrix.colwise())
    {
        ::extractColumnAndPhase(column, mPhases[i++]);
    }
}

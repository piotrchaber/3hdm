#include "tutorial.h"

#include "3hdm/matrix_form.h"

int main()
{
    MyMatrixXcd matrix(MyMatrixXcd::Random(27, 3));
    std::cout << "initial matrix" << '\n' << matrix << "\n\n";

    MatrixForm matrixFormGeneral(matrix, MatrixForm::Form::General);
    print(matrixFormGeneral, "general form");

    MatrixForm matrixFormParticular(matrix, MatrixForm::Form::Particular);
    print(matrixFormParticular, "particular form");

    MatrixForm matrixFormOriginal(matrix, MatrixForm::Form::Original);
    print(matrixFormOriginal, "original form");

    MyMatrixXcd matrixZero(MyMatrixXcd::Zero(27, 3));
    MatrixForm matrixZeroForm(matrixZero, MatrixForm::Form::General);
    print(matrixZeroForm, "general form of zero matrix");

    MyMatrixXcd matrixIdentity(MyMatrixXcd::Identity(27, 3));
    MatrixForm matrixIdentityForm(matrixIdentity, MatrixForm::Form::General);
    print(matrixIdentityForm, "general form of identity matrix");
}

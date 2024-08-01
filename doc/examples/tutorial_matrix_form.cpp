#include "tutorial.h"

#include "3hdm/matrix_form.h"

int main()
{
    const MyMatrixXcd matrix(MyMatrixXcd::Random(27, 3));
    std::cout << "initial matrix" << '\n' << matrix << "\n\n";

    const MatrixForm matrix_form_general(matrix, MatrixForm::Form::General);
    print(matrix_form_general, "general form");

    const MatrixForm matrix_form_particular(matrix, MatrixForm::Form::Particular);
    print(matrix_form_particular, "particular form");

    const MatrixForm matrix_form_original(matrix, MatrixForm::Form::Original);
    print(matrix_form_original, "original form");

    const MyMatrixXcd matrix_zero(MyMatrixXcd::Zero(27, 3));
    const MatrixForm matrix_zero_form_general(matrix_zero, MatrixForm::Form::General);
    print(matrix_zero_form_general, "general form of zero matrix");

    const MyMatrixXcd matrix_identity(MyMatrixXcd::Identity(27, 3));
    const MatrixForm matrix_identity_form_general(matrix_identity, MatrixForm::Form::General);
    print(matrix_identity_form_general, "general form of identity matrix");
}

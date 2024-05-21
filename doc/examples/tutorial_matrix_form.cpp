#include <iostream>

#include "3hdm/matrix_form.h"

int main()
{
    MyMatrixXcd matrix(MyMatrixXcd::Random(27, 3));
    std::cout << matrix << "\n\n";

    MatrixForm matrix_form(matrix, MatrixForm::Form::General);
    std::cout << matrix_form.matrix() << "\n\n";
    std::cout << "Phases" << '\n';
    for (const auto & phase : matrix_form.phases())
    {
        std::cout << phase << "\n\n";
    }

    matrix_form.switchFormTo(MatrixForm::Form::Particular);
    std::cout << matrix_form.matrix() << "\n\n";
    std::cout << "Phases" << '\n';
    for (const auto & phase : matrix_form.phases())
    {
        std::cout << phase << "\n\n";
    }

    matrix_form.switchFormTo(MatrixForm::Form::Original);
    std::cout << matrix_form.matrix() << '\n';
    std::cout << "Phases" << '\n';
    for (const auto & phase : matrix_form.phases())
    {
        std::cout << phase << "\n\n";
    }

    MyMatrixXcd matrix_zero(MyMatrixXcd::Zero(27, 3));
    MatrixForm matrix_zero_form(matrix_zero, MatrixForm::Form::General);
    std::cout << matrix_zero_form.matrix() << "\n\n";
    std::cout << "Phases" << '\n';
    for (const auto & phase : matrix_zero_form.phases())
    {
        std::cout << phase << "\n\n";
    }

    MyMatrixXcd matrix_identity(MyMatrixXcd::Identity(27, 3));
    MatrixForm matrix_identity_form(matrix_identity, MatrixForm::Form::General);
    std::cout << matrix_identity_form.matrix() << "\n\n";
    std::cout << "Phases" << '\n';
    for (const auto & phase : matrix_identity_form.phases())
    {
        std::cout << phase << "\n\n";
    }
}

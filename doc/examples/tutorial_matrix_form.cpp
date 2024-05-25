#include <iostream>

#include "3hdm/matrix_form.h"

int main()
{
    MyMatrixXcd matrix(MyMatrixXcd::Random(27, 3));
    std::cout << "initial matrix" << '\n' << matrix << "\n\n";

    MatrixForm matrix_form_general(matrix, MatrixForm::Form::General);
    std::cout << "general form" << '\n' << matrix_form_general.matrix() << "\n\n";
    std::cout << "phases" << '\n';
    for (const auto & phase : matrix_form_general.phases())
    {
        std::cout << phase << "\n\n";
    }

    MatrixForm matrix_form_particular(matrix, MatrixForm::Form::Particular);
    std::cout << "particular form" << '\n' << matrix_form_particular.matrix() << "\n\n";
    std::cout << "phases" << '\n';
    for (const auto & phase : matrix_form_particular.phases())
    {
        std::cout << phase << "\n\n";
    }

    MatrixForm matrix_form_original(matrix, MatrixForm::Form::Original);
    std::cout << "original form" << '\n' << matrix_form_original.matrix() << "\n\n";
    std::cout << "phases" << '\n';
    for (const auto & phase : matrix_form_original.phases())
    {
        std::cout << phase << "\n\n";
    }

    MyMatrixXcd matrix_zero(MyMatrixXcd::Zero(27, 3));
    MatrixForm matrix_zero_form(matrix_zero, MatrixForm::Form::General);
    std::cout << "general form of zero matrix" << '\n' << matrix_zero_form.matrix() << "\n\n";
    std::cout << "phases" << '\n';
    for (const auto & phase : matrix_zero_form.phases())
    {
        std::cout << phase << "\n\n";
    }

    MyMatrixXcd matrix_identity(MyMatrixXcd::Identity(27, 3));
    MatrixForm matrix_identity_form(matrix_identity, MatrixForm::Form::General);
    std::cout << "general form of identity matrix" << '\n' << matrix_identity_form.matrix() << "\n\n";
    std::cout << "phases" << '\n';
    for (const auto & phase : matrix_identity_form.phases())
    {
        std::cout << phase << "\n\n";
    }
}

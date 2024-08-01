#include "tutorial.h"

#include "3hdm/mymatrix.h"

int main()
{
    const MyMatrix3cd matrix(MyMatrix3cd::Random());
    std::cout << matrix << "\n\n";

    std::stringstream ss{};
    ss << 1 << " " << 2 << " " << 3 << " " << 4;

    MyMatrix2d matrix_ss{};
    matrix_ss.load(ss);
    std::cout << matrix_ss << "\n\n";

    const auto build_path = findBuildPath();

    MyMatrix3cf matrix_file{};
    matrix_file.load("tutorial_mymatrix.txt", build_path);
    std::cout << matrix_file << '\n';
}

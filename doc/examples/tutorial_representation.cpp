#include "tutorial.h"

#include "3hdm/representation.h"

int main()
{
    const MyMatrix3cd matrix1{MyMatrix3cd::Random()};
    const MyMatrix3cd matrix2{MyMatrix3cd::Random()};
    const std::vector<MyMatrix3cd> matrices = { matrix1, matrix2 };

    Representation3cd representation{};
    representation.setMatrices(matrices);
    print(representation);

    //const Representation3cd representation(matrices);
    //print(representation);

    const auto build_path = findBuildPath();

    Representation3cd representation2{};
    representation2.load("tutorial_representation.txt", build_path);
    print(representation2);

    std::cout << "Dimension: " << representation2.dimension() << '\n';
    std::cout << "Size: " << representation2.numberOfMatrices() << '\n';
}

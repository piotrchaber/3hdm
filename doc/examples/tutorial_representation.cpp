#include "tutorial.h"

#include "3hdm/representation.h"

int main()
{
    const MyMatrix3cd matrix1{MyMatrix3cd::Random()};
    const MyMatrix3cd matrix2{MyMatrix3cd::Random()};
    const std::vector<MyMatrix3cd> matrices{ matrix1, matrix2 };

    Representation3cd representation{};
    representation.setMatrices(matrices);
    print(representation);

    //const Representation3cd representation(matrices);
    //print(representation);

    std::cout << "Dimension: " << representation.dimension() << '\n';
    std::cout << "Size: " << representation.numberOfMatrices() << '\n';
}

#include "tutorial.h"

#include "3hdm/representation.h"

int main()
{
	MyMatrix3cd matrix1 = MyMatrix3cd::Random();
	MyMatrix3cd matrix2 = MyMatrix3cd::Random();
	std::vector<MyMatrix3cd> matrices = { matrix1, matrix2 };

	Representation3cd representation;
	representation.setMatrices(matrices);
	print(representation);

	//Representation3cd representation(matrices);
	//print(representation);

	auto buildPath = findBuildPath();

	Representation3cd representation2;
	representation2.load("tutorial_representation.txt", buildPath);
	print(representation2);

	std::cout << "Dimension: " << representation2.dimension() << '\n';
	std::cout << "Size: " << representation2.numberOfMatrices() << '\n';
}

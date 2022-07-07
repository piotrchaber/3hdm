#include <iostream>

#include "../../include/3hdm/representation.h"

void print(const Representation3cd& representation)
{
	for (const auto& matrix : representation.matrices()) {
		std::cout << matrix << '\n';
	}
	std::cout << '\n';
}

int main()
{
	MyMatrix3cd matrix1 = MyMatrix3cd::Random();
	MyMatrix3cd matrix2 = MyMatrix3cd::Random();
	std::vector<MyMatrix3cd> matrices = { matrix1, matrix2 };

	Representation3cd rep;
	rep.setMatrices(matrices);
	print(rep);

	//Representation3cd rep(matrices);
	//print(rep);

	Representation3cd rep2;
	rep2.loadFromFile("tutorial_representation.txt");
	print(rep2);

	std::cout << "Dimension: " << rep2.dimension() << std::endl;
	std::cout << "Size: " << rep2.numberOfMatrices() << std::endl;
	
	return EXIT_SUCCESS;
}
#include <fstream>
#include <iostream>

#include "3hdm/representation.h"

std::filesystem::path findBuildPath()
{
	auto buildPath = std::filesystem::current_path();
	auto buildName = buildPath.filename();
	while (buildName != "build")
	{
		buildPath = buildPath.parent_path();
		buildName = buildPath.filename();
	}
	return buildPath / "";
}

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

	auto buildPath = findBuildPath();

	Representation3cd rep2;
	rep2.load("tutorial_representation.txt", buildPath);
	print(rep2);

	std::cout << "Dimension: " << rep2.dimension() << std::endl;
	std::cout << "Size: " << rep2.numberOfMatrices() << std::endl;
}
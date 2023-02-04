#include <iostream>

#include "3hdm/mymatrix.h"

std::filesystem::path findBuildPath()
{
	auto buildPath = std::filesystem::current_path();
	while (buildPath.filename() != "build")
	{
		buildPath = buildPath.parent_path();
	}
	return buildPath;
}

int main()
{
	MyMatrix3cd matrix(MyMatrix3cd::Random());
	std::cout << matrix << "\n\n";

	std::stringstream ss;
	ss << 1 << " " << 2 << " " << 3 << " " << 4;

	MyMatrix2d matrixss;
	matrixss.load(ss);
	std::cout << matrixss << "\n\n";

	auto buildPath = findBuildPath();

	MyMatrix3cf matrixfile;
	matrixfile.load("tutorial_mymatrix.txt", buildPath);
	std::cout << matrixfile << '\n';
}

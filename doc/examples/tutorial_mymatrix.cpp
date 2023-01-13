#include <iostream>

#include "3hdm/mymatrix.h"

int main()
{
	MyMatrix3cd matrix(MyMatrix3cd::Random());
	std::cout << matrix << "\n\n";

	std::stringstream ss;
	ss << 1 << " " << 2 << " " << 3 << " " << 4;

	MyMatrix2d matrixss;
	matrixss.loadFromStringStream(ss);
	std::cout << matrixss << "\n\n";

	MyMatrix3cf matrixfile;
	matrixfile.loadFromFile("tutorial_mymatrix.txt");
	std::cout << matrixfile << '\n';

	return EXIT_SUCCESS;
}
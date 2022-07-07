#include <iostream>

#include "../../include/3hdm/group.h"

void print(const Group& group)
{
	for (const auto& rep : group.representations()) {
		for (const auto& matrix : rep.matrices()) {
			std::cout << matrix << '\n';
		}
	}
	std::cout << '\n';
}

int main()
{
	using cd = std::complex<double>;

	MyMatrix3cd matrix1; matrix1 << cd(0, 0), cd(1, 0), cd(0, 0), cd(0, 0), cd(0, 0), cd(1, 0), cd(1, 0), cd(0, 0), cd(0, 0);
	MyMatrix3cd matrix2; matrix2 << cd(-1, 0), cd(0, 0), cd(0, 0), cd(0, 0), cd(1, 0), cd(0, 0), cd(0, 0), cd(0, 0), cd(-1, 0);
	MyMatrix3cd matrix3; matrix3 << cd(-1, 0), cd(0, 0), cd(0, 0), cd(0, 0), cd(-1, 0), cd(0, 0), cd(0, 0), cd(0, 0), cd(1, 0);
	Representation3cd representation({ matrix1, matrix2, matrix3 });

	Group group;
	group.setStructure("[ 12, 3 ]");
	group.setNumberOfGenerators(3);
	group.setRepresentations({ representation });

	//Group group("[ 12, 3 ]", 3);
	//group.setRepresentations({ representation });

	//Group group({ representation }, "[ 12, 3 ]");
	//group.setNumberOfGenerators(3);

	//Group group({ representation }, "[ 12, 3 ]", 3);

	Group group2("[ 21, 1 ]", 2);
	group2.loadFromFile("doc/examples/", "tutorial_group");
	std::cout << "Group representations:" << '\n';
	print(group2);

	//Group group2("tutorial_group", 2);
	//group2.loadFromFile("doc/examples/");
	//std::cout << "Group representations:" << '\n';
	//print(group2);

	std::cout << "GroupStructure: " << group2.structure() << '\n';
	std::cout << "GeneratorsNumber: " << group2.numberOfGenerators() << '\n';
	std::cout << "RepresentationsNumber: " << group2.numberOfRepresentations() << '\n';
	std::cout << '\n';

	auto generator = group2.generator(1);
	std::cout << "1stGeneratorMatrices:" << '\n';
	for (const auto& matrix : generator) {
		std::cout << matrix << '\n';
	}
	std::cout << '\n';

	return EXIT_SUCCESS;
}
#include "tutorial.h"

#include "3hdm/group_list.h"
#include "3hdm/group.h"

int main()
{
    const auto build_path = findBuildPath();
    const auto input_path = build_path / "input";
    GroupList::Init(input_path);
    const GroupList::Data group_info{GroupList::Structure(21, 1)};

    Group group(group_info);
    group.load(input_path);

    //Group group(group_info.structure, group_info.generators, group_info.representations);
    //group.load("tutorial_group", build_path);

    //Group group{};
    //group.setStructure("[ 21, 1 ]");
    //group.setNumberOfGenerators(2);
    //group.setNumberOfRepresentations(2);
    //group.load(input_path);

    std::cout << "Structure: " << group.structure() << '\n';
    std::cout << "Generators: " << group.numberOfGenerators() << '\n';
    std::cout << "Representations: " << group.numberOfRepresentations() << '\n';
    std::cout << "Group representations:" << '\n';
    print(group);

    const auto generator = group.generator(1);
    std::cout << "Matrices of first generator:" << '\n';
    for (const auto & matrix : generator)
    {
        std::cout << matrix << '\n' << '\n';
    }
}

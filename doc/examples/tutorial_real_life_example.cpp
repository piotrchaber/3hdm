#include "tutorial.h"

int main()
{
    auto buildPath = findBuildPath();
    auto inputsPath = buildPath / "inputs";
    GroupList::Init(inputsPath);

    InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular);
    Group group;
    Solutions solutions;
    UniqueSolutionsSeeker uniqueParticularSolutionsSeeker;
    UniqueSolutionsSeeker uniqueGeneralSolutionsSeeker;
    
    std::vector<GroupList::Data> firstNineGroups{GroupList::First(9)};
    for (const auto & groupInfo : firstNineGroups)
    {
        group.setStructure(groupInfo.structure);
        group.setNumberOfGenerators(groupInfo.gen);
        group.load(inputsPath / "groups");

        ies.compute(group);
        solutions = ies.solutions();
        //print(solutions);

        uniqueParticularSolutionsSeeker.find(solutions);
        for (auto & solution : solutions) { solution.switchFormTo(Solution::Form::General); }
        uniqueGeneralSolutionsSeeker.find(solutions);
    }

    UniqueSolutions uniqueParticularSolutions{uniqueParticularSolutionsSeeker.items()};
    std::cout << "Unique particular solutions:" << '\n';
	print(uniqueParticularSolutions);

    UniqueSolutions uniqueGeneralSolutions{uniqueGeneralSolutionsSeeker.items()};
    std::cout << "Unique general solutions:" << '\n';
    print(uniqueGeneralSolutions);
}

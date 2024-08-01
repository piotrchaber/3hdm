#include "tutorial.h"

#include "3hdm/unique_solutions_seeker.h"

int main()
{
    const auto build_path = findBuildPath();

    Group group("tutorial_group", 2);
    group.load(build_path);

    InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular, group);
    auto solutions = ies.solutions();

    UniqueSolutionsSeeker ussp{};
    ussp.find(solutions);

    const UniqueSolutions usp{ussp.items()};
    std::cout << "Unique particular solutions:" << '\n';
    print(usp);

    for (auto & solution : solutions)
    {
        solution.switchFormTo(Solution::Form::General);
    }

    UniqueSolutionsSeeker ussg{};
    ussg.find(solutions);

    const UniqueSolutions usg{ussg.items()};
    std::cout << "Unique general solutions:" << '\n';
    print(usg);
}

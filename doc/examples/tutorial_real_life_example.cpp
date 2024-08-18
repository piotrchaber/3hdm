#include "tutorial.h"

int main()
{
    const auto build_path = findBuildPath();
    const auto input_path = build_path / "input";
    GroupList::Init(input_path);

    InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular);
    Group group{};
    Solutions solutions{};
    UniqueSolutionsSeeker unique_particular_solutions_seeker{};
    UniqueSolutionsSeeker unique_general_solutions_seeker{};

    const std::vector<GroupList::Data> first_nine_groups{GroupList::First(9)};
    for (const auto & group_info : first_nine_groups)
    {
        group.setData(group_info);
        group.load(input_path);

        ies.compute(group);
        solutions = ies.solutions();

        unique_particular_solutions_seeker.find(solutions);
        for (auto & solution : solutions) { solution.switchFormTo(Solution::Form::General); }
        unique_general_solutions_seeker.find(solutions);
    }

    const UniqueSolutions unique_particular_solutions{unique_particular_solutions_seeker.items()};
    std::cout << "Unique particular solutions:" << '\n';
    print(unique_particular_solutions);

    const UniqueSolutions unique_general_solutions{unique_general_solutions_seeker.items()};
    std::cout << "Unique general solutions:" << '\n';
    print(unique_general_solutions);
}

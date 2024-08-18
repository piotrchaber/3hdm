#include "tutorial.h"

#include "3hdm/invariance_equation_solver.h"

int main()
{
    const auto build_path = findBuildPath();
    Group group("tutorial_group", 2, 2);
    group.load(build_path);

    InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular);
    ies.compute(group);
    const auto solutions = ies.solutions();
    print(solutions);

    //InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular);
    //ies.compute(group, {1, 1, 1});
    //const auto solution = ies.solution();
    //print(solution);

    //InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular, group);
    //const auto solutions = ies.solutions();
    //print(solutions);

    //InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular, group, {1, 1, 1});
    //const auto solution = ies.solution();
    //print(solution);
}

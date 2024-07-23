#include "tutorial.h"

#include "3hdm/invariance_equation_solver.h"

int main()
{
    auto buildPath = findBuildPath();
    Group group("tutorial_group", 2);
    group.load(buildPath);

    InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular);
    ies.compute(group);
    Solutions solutions = ies.solutions();
    print(solutions);

    //InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular);
    //ies.compute(group, {1, 1, 1});
    //Solution solution = ies.solution();
    //print(solution);

    //InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular, group);
    //Solutions solutions = ies.solutions();
    //print(solutions);

    //InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular, group, {1, 1, 1});
    //Solution solution = ies.solution();
    //print(solution);
}

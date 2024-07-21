#include "tutorial.h"

#include "3hdm/unique_solutions_seeker.h"

int main()
{
	auto buildPath = findBuildPath();

	Group group("tutorial_group", 2);
	group.load(buildPath);

	InvarianceEquationSolver ies(Particles::ChargedLeptons, Solution::Form::Particular, group);
	Solutions solutions = ies.solutions();

	UniqueSolutionsSeeker ussp;
	ussp.find(solutions);
	UniqueSolutions usp;
	usp = ussp.items();
	std::cout << "Unique particular solutions:" << '\n';
	print(usp);

	for (auto & solution : solutions)
	{
		solution.switchFormTo(Solution::Form::General);
	}

	UniqueSolutionsSeeker ussg;
	ussg.find(solutions);
	UniqueSolutions usg;
	usg = ussg.items();
	std::cout << "Unique general solutions:" << '\n';
	print(usg);
}

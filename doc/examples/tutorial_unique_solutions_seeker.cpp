#include "../../include/3hdm/unique_solutions_seeker.h"

void print(UniqueSolution& unique, std::ostream& os = std::cout)
{
	const Eigen::IOFormat fmtVector(6, Eigen::DontAlignCols, " ", " ", "", "", "[", "]");
	const Eigen::IOFormat fmtPhase(6, Eigen::DontAlignCols, " ", " ", "", "", "{", "}");

	unique.setActualZero();
	os << unique.transpose().format(fmtVector) << '\n'
		<< unique.groups() << '\n';
	if (unique.phases().empty() == false) {
		auto phases = unique.phases();
		for (auto& phase : phases) {
			phase.setActualZero();
			os << phase.transpose().format(fmtPhase) << " ";
		}
		os << '\n';
	}
	os << '\n';
}

void print(UniqueSolutions& uniques, std::ostream& os = std::cout)
{
	for (auto& unique : uniques) {
		print(unique, os);
	}
}

int main()
{
	Group group("tutorial_group", 2);
	group.loadFromFile("doc/examples/");

	InvarianceEquationSolver ies(group, Particles::ChargedLeptons, Solution::Form::Particular);
	Solutions solutions = ies.solutions();

	UniqueSolutionsSeeker ussp;
	ussp.find(solutions);
	UniqueSolutions usp;
	usp = ussp.items();
	std::cout << "Uniques particular solutions:" << '\n';
	print(usp);

	for (auto& solution : solutions) {
		solution.switchForm();
	}

	UniqueSolutionsSeeker ussg;
	ussg.find(solutions);
	UniqueSolutions usg;
	usg = ussg.items();
	std::cout << "Uniques general solutions:" << '\n';
	print(usg);

	return EXIT_SUCCESS;
}
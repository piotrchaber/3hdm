#include <filesystem>
#include <iostream>

#include "3hdm/invariance_equation_solver.h"

std::filesystem::path findBuildPath()
{
	auto buildPath = std::filesystem::current_path();
	auto buildName = buildPath.filename();
	while (buildName != "build")
	{
		buildPath = buildPath.parent_path();
		buildName = buildPath.filename();
	}
	return buildPath / "";
}

const std::string toString(const std::vector<size_t>& vector, const char& sep = ' ')
{
	std::string result;

	for (size_t i = 0; i < vector.size(); ++i) {
		result += (i == vector.size() - 1) ? std::to_string(vector[i]) : std::to_string(vector[i]) + sep;
	}

	return result;
}

void print(Solution& solution)
{
	const Eigen::IOFormat fmtMatrix(6, Eigen::DontAlignCols, " ", "\n", "[", "]");

	solution.setActualZero();
	std::cout << solution.origin().group << '\n'
		<< toString(solution.origin().combination, 'x') << " "
		<< std::boolalpha << solution.isGood() << '\n'
		<< solution.transpose().format(fmtMatrix) << '\n';
}

void print(Solutions& solutions)
{
	const Eigen::IOFormat fmtMatrix(6, Eigen::DontAlignCols, " ", "\n", "[", "]");

	std::cout << (solutions.front()).origin().group << '\n';
	for (auto& solution : solutions) {
		solution.setActualZero();
		std::cout << toString(solution.origin().combination, 'x') << " "
			<< std::boolalpha << solution.isGood() << '\n'
			<< solution.transpose().format(fmtMatrix) << '\n';
	}
}

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

	//InvarianceEquationSolver ies(group, Particles::ChargedLeptons, Solution::Form::Particular);
	//Solutions solutions = ies.solutions();
	//print(solutions);

	//InvarianceEquationSolver ies(group, {1, 1, 1}, Particles::ChargedLeptons, Solution::Form::Particular);
	//Solution solution = ies.solution();
	//print(solution);

	return EXIT_SUCCESS;
}
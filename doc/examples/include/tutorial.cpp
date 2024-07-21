#include "tutorial.h"

std::filesystem::path findBuildPath()
{
	std::filesystem::path buildPath{std::filesystem::current_path()};
	while (buildPath.filename() != "build")
	{
		buildPath = buildPath.parent_path();
	}
	return buildPath;
}

void print(const std::vector<size_t> & combination)
{
    for (auto const & coefficient : combination)
    {
        std::cout << coefficient << " ";
    }
    std::cout << '\n';
}

void print(const std::vector<size_t> & combination, const std::string & message)
{
    std::cout << message << '\n';
    print(combination);
}

void print(const Group & group)
{
	for (const auto & representation : group.representations())
	{
		print(representation);
	}
	std::cout << '\n';
}

void print(const GroupList::Data & groupInfo, const std::string & message)
{
    if (message.empty() == false)
    {
        std::cout << message << '\n';
    }
    std::cout << groupInfo.structure << " " << groupInfo.gen << '\n';
}

void print(const std::vector<GroupList::Data> & groupsInfo, const std::string & message)
{
    if (message.empty() == false)
    {
        std::cout << message << '\n';
    }

    for (const auto & groupInfo : groupsInfo)
    {
        print(groupInfo);
    }
}

void print(const MatrixForm & matrixForm, const std::string & message)
{
    std::cout << message << '\n';
    std::cout << matrixForm.matrix() << '\n' << '\n';
    std::cout << "phases" << '\n';
    for (const auto & phase : matrixForm.phases())
    {
        std::cout << phase << "\n\n";
    }
}

void print(const Representation3cd & representation)
{
	for (const auto & matrix : representation.matrices())
	{
		std::cout << matrix << '\n';
	}
	std::cout << '\n';
}

void print(const Solution & solution)
{
	const Eigen::IOFormat fmtMatrix(6, Eigen::DontAlignCols, " ", "\n", "[", "]");

	std::cout << solution.origin().group << '\n'
		<< toString(solution.origin().combination, 'x') << " "
		<< std::boolalpha << solution.isGood() << '\n'
		<< solution.transpose().format(fmtMatrix) << '\n';
}

void print(const Solutions & solutions)
{
	const Eigen::IOFormat fmtMatrix(6, Eigen::DontAlignCols, " ", "\n", "[", "]");

	std::cout << (solutions.front()).origin().group << '\n';
	for (const auto & solution : solutions)
	{
		std::cout << toString(solution.origin().combination, 'x') << " "
			<< std::boolalpha << solution.isGood() << '\n'
			<< solution.transpose().format(fmtMatrix) << '\n';
	}
    std::cout << '\n';
}

void print(const UniqueSolution & unique, std::ostream & os)
{
	const Eigen::IOFormat fmtVector(6, Eigen::DontAlignCols, " ", " ", "", "", "[", "]");
	const Eigen::IOFormat fmtPhase(6, Eigen::DontAlignCols, " ", " ", "", "", "{", "}");

	os << unique.transpose().format(fmtVector) << '\n';
	if (unique.phases().empty() == false)
	{
		auto phases = unique.phases();
		for (auto & phase : phases)
		{
			os << phase.transpose().format(fmtPhase) << " ";
		}
		os << '\n';
	}
    os << unique.groups() << '\n' << '\n';
}

void print(const UniqueSolutions & uniques, std::ostream & os)
{
	for (const auto & unique : uniques)
	{
		print(unique, os);
	}
}

std::string toString(const std::vector<size_t> & vector, const char sep)
{
	std::string result;
	for (auto i = 0; i < vector.size(); ++i)
	{
		result += (i == vector.size() - 1) ? std::to_string(vector[i]) : std::to_string(vector[i]) + sep;
	}
	return result;
}

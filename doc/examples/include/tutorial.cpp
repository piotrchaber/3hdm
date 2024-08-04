#include "tutorial.h"

std::filesystem::path findBuildPath()
{
    std::filesystem::path build_path{std::filesystem::current_path()};
    while (build_path.filename() != "build")
    {
        build_path = build_path.parent_path();
    }
    return build_path;
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

void print(const GroupList::Data & group_info, const std::string & message)
{
    if (false == message.empty())
    {
        std::cout << message << '\n';
    }
    std::cout << group_info.structure << " " << group_info.generators << '\n';
}

void print(const std::vector<GroupList::Data> & groups_info, const std::string & message)
{
    if (false == message.empty())
    {
        std::cout << message << '\n';
    }

    for (const auto & group_info : groups_info)
    {
        print(group_info);
    }
}

void print(const MatrixForm & matrix_form, const std::string & message)
{
    std::cout << message << '\n';
    std::cout << matrix_form.matrix() << '\n' << '\n';
    std::cout << "phases" << '\n';
    for (const auto & phase : matrix_form.phases())
    {
        std::cout << phase << '\n' << '\n';
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
    const Eigen::IOFormat fmt_matrix(6, Eigen::DontAlignCols, " ", "\n", "[", "]");

    std::cout << solution.origin().group << '\n'
        << toString(solution.origin().combination, 'x') << " "
        << std::boolalpha << solution.isGood() << '\n'
        << solution.transpose().format(fmt_matrix) << '\n';
}

void print(const Solutions & solutions)
{
    const Eigen::IOFormat fmt_matrix(6, Eigen::DontAlignCols, " ", "\n", "[", "]");

    std::cout << (solutions.front()).origin().group << '\n';
    for (const auto & solution : solutions)
    {
        std::cout << toString(solution.origin().combination, 'x') << " "
            << std::boolalpha << solution.isGood() << '\n'
            << solution.transpose().format(fmt_matrix) << '\n';
    }
    std::cout << '\n';
}

void print(const UniqueSolution & unique, std::ostream & os)
{
    const Eigen::IOFormat fmt_vector(6, Eigen::DontAlignCols, " ", " ", "", "", "[", "]");
    const Eigen::IOFormat fmt_phase(6, Eigen::DontAlignCols, " ", " ", "", "", "{", "}");

    os << unique.transpose().format(fmt_vector) << '\n';
    if (false == unique.phases().empty())
    {
        for (auto & phase : unique.phases())
        {
            os << phase.transpose().format(fmt_phase) << " ";
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
    std::string result{};
    for (auto i = 0; i < vector.size(); ++i)
    {
        result += (i == vector.size() - 1) ? std::to_string(vector[i]) : std::to_string(vector[i]) + sep;
    }
    return result;
}

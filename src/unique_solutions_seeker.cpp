#include "3hdm/unique_solutions_seeker.h"

void UniqueSolutionsSeeker::Item::check(const std::string & group)
{
    const size_t found{groups_.find(group)};
    if (std::string::npos == found)
    {
        groups_ += group;
    }
}

void UniqueSolutionsSeeker::Item::check(const MyVectorXcd & phase)
{
    if (phase.isZero()) { return; }

    auto found = std::find_if(phases_.begin(), phases_.end(), [&](const auto & item) {
        return phase.isApprox(item, 0.00001); });
    if (found == phases_.end())
    {
        phases_.push_back(phase);
    }
}

const std::string & UniqueSolutionsSeeker::Item::groups() const
{
    return groups_;
}

const std::vector<MyVectorXcd> & UniqueSolutionsSeeker::Item::phases() const
{
    return phases_;
}

UniqueSolutionsSeeker::UniqueSolutionsSeeker(const Solutions & solutions)
{
    find(solutions);
}

void UniqueSolutionsSeeker::check(const Solution::ConstColXpr & column, const std::string & group)
{
    check(column, group, MyVectorXcd(0));
}

void UniqueSolutionsSeeker::check(const Solution::ConstColXpr & column, const std::string & group, const MyVectorXcd & phase)
{
    auto found = std::find_if(items_.begin(), items_.end(), [&](const auto & item) {
        return column.isApprox(item, 0.00001); });
    if (found == items_.end())
    {
        items_.push_back(column);
        found = items_.end() - 1;
    }
    found->check(group);
    found->check(phase);
}

void UniqueSolutionsSeeker::find(const Solution & solution)
{
    for (auto i = 0; i < solution.cols(); ++i)
    {
        solution.phases() == 0 ? check(solution.col(i), solution.origin().group)
            : check(solution.col(i), solution.origin().group, solution.phase(i));
    }
}

void UniqueSolutionsSeeker::find(const Solutions & solutions)
{
    for (const auto & solution : solutions)
    {
        find(solution);
    }
}

const UniqueSolutionsSeeker::Item & UniqueSolutionsSeeker::item(const size_t ith) const
{
    return items_.at(ith);
}

const std::vector<UniqueSolutionsSeeker::Item> & UniqueSolutionsSeeker::items() const
{
    return items_;
}

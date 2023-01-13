#include "3hdm/unique_solutions_seeker.h"

void UniqueSolutionsSeeker::Item::check(const std::string& group)
{
	size_t found = mGroups.find(group);
	if (found == std::string::npos) {
		mGroups += group;
	}
}

void UniqueSolutionsSeeker::Item::check(const MyVectorXcd& phase)
{
	if (phase.isZero()) { return; }
	auto found = std::find_if(mPhases.begin(), mPhases.end(), [&](const auto& item)
		{ return phase.isApprox(item, 0.00001); });
	if (found == mPhases.end()) {
		mPhases.push_back(phase);
	}
}

const std::string& UniqueSolutionsSeeker::Item::groups() const
{
	return mGroups;
}

const std::vector<MyVectorXcd>& UniqueSolutionsSeeker::Item::phases() const
{
	return mPhases;
}

UniqueSolutionsSeeker::UniqueSolutionsSeeker(const Solutions& solutions)
{
	find(solutions);
}

void UniqueSolutionsSeeker::check(const Solution::ConstColXpr& column, const std::string& group)
{
	check(column, group, MyVectorXcd(0));
}

void UniqueSolutionsSeeker::check(const Solution::ConstColXpr& column, const std::string& group, const MyVectorXcd& phase)
{
	auto found = std::find_if(mItems.begin(), mItems.end(), [&](const auto& item)
		{ return column.isApprox(item, 0.00001); });
	if (found == mItems.end()) {
		mItems.push_back(column);
		found = mItems.end() - 1;
	}
	found->check(group);
	found->check(phase);
}

void UniqueSolutionsSeeker::find(const Solution& solution)
{
	for (int i = 0; i < solution.cols(); ++i) {
		solution.phases() == 0 ? check(solution.col(i), solution.origin().group)
			: check(solution.col(i), solution.origin().group, solution.phase(i));
	}
}

void UniqueSolutionsSeeker::find(const Solutions& solutions)
{
	for (const auto& solution : solutions) {
		find(solution);
	}
}

const UniqueSolutionsSeeker::Item& UniqueSolutionsSeeker::item(size_t ith) const
{
	return mItems.at(ith);
}

const std::vector<UniqueSolutionsSeeker::Item>& UniqueSolutionsSeeker::items() const
{
	return mItems;
}
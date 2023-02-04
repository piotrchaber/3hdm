#pragma once

#include "invariance_equation_solver.h"

class UniqueSolutionsSeeker
{
public:
	class Item : public MyVectorXcd
	{
	public:
		virtual ~Item() = default;

		void check(const std::string & group);
		void check(const MyVectorXcd & phase);
		const std::string & groups() const;
		const std::vector<MyVectorXcd> & phases() const;

	private:
		using MyVectorXcd::MyVectorXcd;
		std::string mGroups;
		std::vector<MyVectorXcd> mPhases;
	};

	UniqueSolutionsSeeker() = default;
	explicit UniqueSolutionsSeeker(const Solutions & solutions);
	virtual ~UniqueSolutionsSeeker() = default;

	void find(const Solution & solution);
	void find(const Solutions & solutions);
	const Item & item(size_t ith) const;
	const std::vector<Item> & items() const;

protected:
	void check(const Solution::ConstColXpr & column, const std::string & group);
	void check(const Solution::ConstColXpr & column, const std::string & group, const MyVectorXcd & phase);

private:
	std::vector<Item> mItems;
};

typedef UniqueSolutionsSeeker::Item UniqueSolution;
typedef std::vector<UniqueSolution> UniqueSolutions;
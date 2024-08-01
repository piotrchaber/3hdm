#ifndef INCLUDE_3HDM_UNIQUE_SOLUTIONS_SEEKER_H
#define INCLUDE_3HDM_UNIQUE_SOLUTIONS_SEEKER_H

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
        std::string groups_{};
        std::vector<MyVectorXcd> phases_{};
    };

    UniqueSolutionsSeeker() = default;
    explicit UniqueSolutionsSeeker(const Solutions & solutions);
    virtual ~UniqueSolutionsSeeker() = default;

    void find(const Solution & solution);
    void find(const Solutions & solutions);
    const Item & item(const size_t ith) const;
    const std::vector<Item> & items() const;

private:
    void check(const Solution::ConstColXpr & column, const std::string & group);
    void check(const Solution::ConstColXpr & column, const std::string & group, const MyVectorXcd & phase);

    std::vector<Item> items_{};
};

typedef UniqueSolutionsSeeker::Item UniqueSolution;
typedef std::vector<UniqueSolution> UniqueSolutions;

#endif  // INCLUDE_3HDM_UNIQUE_SOLUTIONS_SEEKER_H

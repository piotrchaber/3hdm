#include "3hdm/combination.h"

#include <algorithm>
#include <set>

Combination::Combination(const std::string & base, size_t numbersUpTo)
    : mBase(base), mNumbersUpTo(numbersUpTo)
{
    findUniqueCoefficients();
    set(LowerLimitExtendedCombination());
}

Combination::Combination(const std::string & base, size_t numbersUpTo, const std::vector<size_t> & initialCombination)
    : mBase(base), mNumbersUpTo(numbersUpTo)
{
    findUniqueCoefficients();
    set(initialCombination);
}

void Combination::extend()
{
    int reducedIndex = 0;
    for (auto & uniqueCoefficient : mUniqueCoefficients)
    {
        uniqueCoefficient.second = mReducedCombination.at(reducedIndex++);
    }

    int extendedIndex = 0;
    for (auto const & coefficient : mBase)
    {
        mExtendedCombination.at(extendedIndex++) = mUniqueCoefficients[coefficient];
    }
}

void Combination::findUniqueCoefficients()
{
    for (auto const & coefficient : mBase) { mUniqueCoefficients[toupper(coefficient)]; }
}

const std::vector<size_t> & Combination::get() const
{
    return mExtendedCombination;
}

void Combination::invalidate()
{
    mReducedCombination = LowerLimitReducedCombination();
    mExtendedCombination = LowerLimitExtendedCombination();
}

bool Combination::isValid(const std::vector<size_t> & combination) const
{
    auto predicate = [&](auto coefficient) { return coefficient > mNumbersUpTo; };
    if ((mBase.size() != combination.size()) || std::any_of(combination.begin(), combination.end(), predicate))
    {
        return false;
    }

    std::set<std::string> uniquePairs;
    for (auto index = 0; index < mBase.size(); ++index)
    {
        uniquePairs.insert(mBase.at(index) + std::to_string(combination.at(index)));
    }

    return mUniqueCoefficients.size() == uniquePairs.size();
}

bool Combination::next()
{
    int index = mUniqueCoefficients.size() - 1;
    
    mReducedCombination[index]++;
    while (mReducedCombination[index] == mNumbersUpTo + 1)
    {
        mReducedCombination[index] = 1;
        if (index == 0) break;
        mReducedCombination[--index]++;
    }

    extend();
	
    auto predicate = [](auto coefficient) { return coefficient != 1; };
    return std::any_of(mReducedCombination.begin(), mReducedCombination.end(), predicate);
}

bool Combination::previous()
{
    int index = mUniqueCoefficients.size() - 1;

    mReducedCombination[index]--;
    while (mReducedCombination[index] == 0)
    {
        mReducedCombination[index] = mNumbersUpTo;
        if (index == 0) break;
        mReducedCombination[--index]--;
    }

    extend();
	
    auto predicate = [&](auto coefficient) { return coefficient != mNumbersUpTo; };
    return std::any_of(mReducedCombination.begin(), mReducedCombination.end(), predicate);
}

void Combination::reduce()
{
    mReducedCombination.reserve(mUniqueCoefficients.size());
    size_t index;

    for (auto const & uniqueCoefficient : mUniqueCoefficients)
    {
        index = mBase.find(uniqueCoefficient.first);
        mReducedCombination.push_back(mExtendedCombination.at(index));
    }
}

void Combination::set(const std::vector<size_t> & combination)
{
    if (isValid(combination))
    {
        mExtendedCombination = combination;
        reduce();
    }
    else
    {
        invalidate();
    }
}

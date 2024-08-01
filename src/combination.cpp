#include "3hdm/combination.h"

#include <algorithm>
#include <set>

Combination::Combination(const std::string & base, const size_t numbers_up_to)
    : base_(base), numbers_up_to_(numbers_up_to)
{
    findUniqueCoefficients();
    set(kLowerLimitExtendedCombination());
}

Combination::Combination(const std::string & base, const size_t numbers_up_to, const std::vector<size_t> & initial_combination)
    : base_(base), numbers_up_to_(numbers_up_to)
{
    findUniqueCoefficients();
    set(initial_combination);
}

void Combination::extend()
{
    size_t reduced_index{0};
    for (auto & unique_coefficient : unique_coefficients_)
    {
        unique_coefficient.second = reduced_combination_.at(reduced_index++);
    }

    size_t extended_index{0};
    for (auto const & coefficient : base_)
    {
        extended_combination_.at(extended_index++) = unique_coefficients_[coefficient];
    }
}

void Combination::findUniqueCoefficients()
{
    for (auto const & coefficient : base_) { unique_coefficients_[toupper(coefficient)]; }
}

const std::vector<size_t> & Combination::get() const
{
    return extended_combination_;
}

void Combination::invalidate()
{
    reduced_combination_ = kLowerLimitReducedCombination();
    extended_combination_ = kLowerLimitExtendedCombination();
}

bool Combination::isValid(const std::vector<size_t> & combination) const
{
    auto predicate = [&](auto coefficient) { return coefficient > numbers_up_to_; };
    if ((base_.size() != combination.size()) || std::any_of(combination.begin(), combination.end(), predicate))
    {
        return false;
    }

    std::set<std::string> unique_pairs{};
    for (auto index = 0; index < base_.size(); ++index)
    {
        unique_pairs.insert(base_.at(index) + std::to_string(combination.at(index)));
    }

    return unique_coefficients_.size() == unique_pairs.size();
}

std::vector<size_t> Combination::kLowerLimitExtendedCombination() const
{
    return std::vector<size_t>(base_.size(), 1);
}

std::vector<size_t> Combination::kLowerLimitReducedCombination() const
{
    return std::vector<size_t>(unique_coefficients_.size(), 1);
}

bool Combination::next()
{
    size_t index{unique_coefficients_.size() - 1};

    reduced_combination_[index]++;
    while (numbers_up_to_ + 1 == reduced_combination_[index])
    {
        reduced_combination_[index] = 1;
        if (0 == index) break;
        reduced_combination_[--index]++;
    }

    extend();

    auto predicate = [](auto coefficient) { return 1 != coefficient; };
    return std::any_of(reduced_combination_.begin(), reduced_combination_.end(), predicate);
}

bool Combination::previous()
{
    size_t index{unique_coefficients_.size() - 1};

    reduced_combination_[index]--;
    while (0 == reduced_combination_[index])
    {
        reduced_combination_[index] = numbers_up_to_;
        if (0 == index) break;
        reduced_combination_[--index]--;
    }

    extend();

    auto predicate = [&](auto coefficient) { return numbers_up_to_ != coefficient; };
    return std::any_of(reduced_combination_.begin(), reduced_combination_.end(), predicate);
}

void Combination::reduce()
{
    reduced_combination_.reserve(unique_coefficients_.size());
    size_t index{};

    for (auto const & unique_coefficient : unique_coefficients_)
    {
        index = base_.find(unique_coefficient.first);
        reduced_combination_.push_back(extended_combination_.at(index));
    }
}

void Combination::set(const std::vector<size_t> & combination)
{
    if (isValid(combination))
    {
        extended_combination_ = combination;
        reduce();
    }
    else
    {
        invalidate();
    }
}

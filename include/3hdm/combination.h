#ifndef INCLUDE_3HDM_COMBINATION_H
#define INCLUDE_3HDM_COMBINATION_H

#include <map>
#include <string>
#include <vector>

class Combination
{
    public:
        Combination(const std::string & base, const size_t numbers_up_to);
        Combination(const std::string & base, const size_t numbers_up_to, const std::vector<size_t> & initial_combination);

        const std::vector<size_t> & get() const;
        bool next();
        bool previous();
        void set(const std::vector<size_t> & combination);

    private:
        void extend();
        void findUniqueCoefficients();
        void invalidate();
        bool isValid(const std::vector<size_t> & combination) const;
        std::vector<size_t> kLowerLimitExtendedCombination() const;
        std::vector<size_t> kLowerLimitReducedCombination() const;
        void reduce();

        std::string base_{};
        size_t numbers_up_to_{};
        std::map<char, size_t> unique_coefficients_{};
        std::vector<size_t> reduced_combination_{};
        std::vector<size_t> extended_combination_{};
};

#endif  // INCLUDE_3HDM_COMBINATION_H

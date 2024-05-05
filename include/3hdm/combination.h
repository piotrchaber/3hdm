#ifndef COMBINATION_H
#define COMBINATION_H

#include <map>
#include <string>
#include <vector>

class Combination
{
    public:
        Combination(const std::string & base, size_t numbersUpTo);
        Combination(const std::string & base, size_t numbersUpTo, const std::vector<size_t> & initialCombination);

        const std::vector<size_t> & get() const;
        bool next();
        bool previous();
        void set(const std::vector<size_t> & combination);

    protected:
        void extend();
        void findUniqueCoefficients();
        void invalidate();
        bool isValid(const std::vector<size_t> & combination) const;
        void reduce();
        std::vector<size_t> LowerLimitExtendedCombination() const
        {
            return std::vector<size_t>(mBase.size(), 1);
        }
        std::vector<size_t> LowerLimitReducedCombination() const
        {
            return std::vector<size_t>(mUniqueCoefficients.size(), 1);
        }

    private:
        std::string mBase;
        size_t mNumbersUpTo;
        std::map<char, size_t> mUniqueCoefficients;
        std::vector<size_t> mReducedCombination;
        std::vector<size_t> mExtendedCombination;
};

#endif // COMBINATION_H
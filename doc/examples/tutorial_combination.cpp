#include "tutorial.h"

#include "3hdm/combination.h"

int main()
{
    Combination combination_next("AABB", 2);
    do
    {
        print(combination_next.get());
    } while (combination_next.next());
    print(combination_next.get(), "When we cross upper limit combination.");
    std::cout << '\n';

    Combination combination_previous("AABB", 2, {2,2,2,2});
    do
    {
        print(combination_previous.get());
    } while (combination_previous.previous());
    print(combination_previous.get(), "When we cross lower limit combination.");
    std::cout << '\n';

    Combination combination_invalid("AABB", 2, {3,3,3,3});
    print(combination_invalid.get(), "One of coefficients greater then max number.");

    Combination combination_invalid2("AABB", 2, {1,1,2,2,2});
    print(combination_invalid2.get(), "Too many coefficients.");
}

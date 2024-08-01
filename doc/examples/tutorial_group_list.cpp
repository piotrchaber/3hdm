#include "tutorial.h"

#include "3hdm/group_list.h"

int main()
{
    const auto build_path = findBuildPath();
    const auto inputs_path = build_path / "inputs";
    GroupList::Init(inputs_path);

    const auto order_24 = GroupList::Order(24);
    print(order_24, "Groups of order 24");

    const auto orders_21_24 = GroupList::Orders({21, 24});
    print(orders_21_24, "Groups of order 21 and 24");

    const auto orders_from_24_to_45 = GroupList::Orders(24, 45);
    print(orders_from_24_to_45, "Groups of order from 24 to 45");

    const auto random_group = GroupList::Random();
    print(random_group, "Random group");

    const auto random_groups = GroupList::Random(5);
    print(random_groups, "Random groups");

    const auto first_groups = GroupList::First(5);
    print(first_groups, "First five groups");

    const auto range_groups = GroupList::Range(5, 5);
    print(range_groups, "Range groups");

    const auto selected_group = GroupList::Structure(21, 1);
    print(selected_group, "Selected group");

    const auto selected_groups = GroupList::Structures({{21, 1}, {24, 3}});
    print(selected_groups, "Selected groups");
}

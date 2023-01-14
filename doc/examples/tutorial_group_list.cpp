#include <iostream>

#include "3hdm/group_list.h"

void print(const GroupList::Data& group, const std::string & message = "")
{
    if (message.empty() == false) {
        std::cout << message << '\n';
    }
    std::cout << group.structure << " " << group.gen << '\n';
}

void print(const std::vector<GroupList::Data>& groups, const std::string & message = "")
{
    if (message.empty() == false) {
        std::cout << message << '\n';
    }

    for (const auto & group : groups)
    {
        print(group);
    }
}

int main()
{
    auto order_24 = GroupList::Order(24);
    print(order_24, "Groups of order 24");

    auto orders_21_24 = GroupList::Orders({21, 24});
    print(orders_21_24, "Groups of order 21 and 24");

    auto random_group = GroupList::Random();
    print(random_group, "Random group");

    auto random_groups = GroupList::Random(5);
    print(random_groups, "Random groups");

    auto range_groups = GroupList::Range(0, 5);
    print(range_groups, "Range groups");

    auto selected_group = GroupList::Structure(21, 1);
    print(selected_group, "Selected group");

    auto selected_groups = GroupList::Structures({{21, 1}, {24, 3}});
    print(selected_groups, "Selected groups");
    
    return EXIT_SUCCESS;
}
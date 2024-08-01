#include "3hdm/group_list.h"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace
{

size_t takeStructure(const std::string & group, size_t start)
{
    std::string result{};
    while (isdigit(group[++start])) { result += (group[start]); }
    return stoi(result);
}

size_t takeOrder(const std::string & group)
{
    return takeStructure(group, 1);
}

size_t takeId(const std::string & group)
{
    return takeStructure(group, group.find(',') + 1);
}

}

bool GroupList::Data::operator<(const GroupList::Data & right) const
{
    if (takeOrder(this->structure) == takeOrder(right.structure))
    {
        return takeId(this->structure) < takeId(right.structure);
    }
    return takeOrder(this->structure) < takeOrder(right.structure);
}

std::string GroupList::path_{};
std::vector<GroupList::Data> GroupList::data_{};

void GroupList::Init(const std::string & path)
{
    path_ = path;
    data_ = loadData();
}

std::vector<GroupList::Data> GroupList::All()
{
    return data_;
}

std::vector<GroupList::Data> GroupList::First(const size_t length)
{
    return Range(0, length);
}

std::vector<GroupList::Data> GroupList::Order(const size_t order)
{
    std::vector<Data> result{};

    auto found = std::find_if(data_.cbegin(), data_.cend(), [&](const auto & group) {
        return order == takeOrder(group.structure); });
    while ((found != data_.cend()) && (order == takeOrder(found->structure)))
    {
        result.push_back(*found);
        ++found;
    }

    return result;
}

std::vector<GroupList::Data> GroupList::Orders(const std::vector<size_t> & orders)
{
    std::vector<Data> result{};
    std::vector<Data> subresult{};

    for (auto const & order : orders)
    {
        subresult = Order(order);
        result.insert(result.end(), subresult.begin(), subresult.end());
    }

    return result;
}

std::vector<GroupList::Data> GroupList::Orders(const size_t from, const size_t to)
{
    assert(from <= to && "The lower limit is greater than the upper one");

    std::vector<Data> result{};

    std::copy_if(data_.cbegin(), data_.cend(), std::back_inserter(result), [&](const auto & group) {
            return (takeOrder(group.structure) >= from) && (takeOrder(group.structure) < to); });

    return result;
}

GroupList::Data GroupList::Random()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    const size_t index{rand() % data_.size()};
    return data_.at(index);
}

std::vector<GroupList::Data> GroupList::Random(const size_t how_many)
{
    assert(how_many <= data_.size() && "The number of groups has been exceeded");

    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<Data> result{};
    size_t index{};

    while (result.size() < how_many)
    {
        index = rand() % data_.size();
        auto found = std::binary_search(result.begin(), result.end(), data_.at(index));
        if (false == found)
        {
            result.insert(std::upper_bound(result.begin(), result.end(), data_.at(index)), data_.at(index));
        }
    }

    return result;
}

std::vector<GroupList::Data> GroupList::Range(const size_t first, const size_t length)
{
    assert(first + length <= data_.size() && "The number of groups has been exceeded");

    std::vector<Data> result{};

    for (auto index = first; index < std::min(first + length, data_.size()); ++index)
    {
        result.push_back(data_.at(index));
    }

    return result;
}

GroupList::Data GroupList::Structure(const size_t order, const size_t id)
{
    Data result{};

    auto found = std::find_if(data_.cbegin(), data_.cend(), [&](const auto & group) {
        return (order == takeOrder(group.structure)) && (id == takeId(group.structure)); });
    if (found != data_.cend())
    {
        result = *found;
    }

    return result;
}

std::vector<GroupList::Data> GroupList::Structures(const std::vector<std::pair<size_t, size_t>> & structures)
{
    std::vector<Data> result{};
    Data subresult{};

    for (auto const & structure : structures)
    {
        subresult = Structure(structure.first, structure.second);
        if (false == subresult.structure.empty())
        {
            result.push_back(subresult);
        }
    }

    return result;
}

std::vector<GroupList::Data> GroupList::loadData()
{
    std::vector<Data> result{};
    Data data{};
    const std::vector<std::string> structures{loadStructures()};
    const std::vector<size_t> generators{loadGenerators()};

    for (auto index = 0; index < std::min(structures.size(), generators.size()); ++index)
    {
        data.generators = generators.at(index);
        data.structure = structures.at(index);
        result.push_back(data);
    }

    return result;
}

std::vector<size_t> GroupList::loadGenerators()
{
    const std::filesystem::path file_path{path_ + "/generators.txt"};
    std::fstream ifile{};

    ifile.open(file_path, std::ios::in);
    if (false == ifile.is_open())
    {
        std::cerr << file_path << " file not opening properly!" << '\n';
        exit(EXIT_FAILURE);
    }

    std::vector<size_t> result{};
    size_t data{};

    while (ifile >> data)
    {
        result.push_back(data);
    }

    return result;
}

std::vector<std::string> GroupList::loadStructures()
{
    const std::filesystem::path file_path{path_ + "/groups.txt"};
    std::fstream ifile{};

    ifile.open(file_path, std::ios::in);
    if (false == ifile.is_open())
    {
        std::cerr << file_path << " file not opening properly!" << '\n';
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> result{};
    std::string data{};

    while (getline(ifile, data))
    {
        result.push_back(data);
    }

    return result;
}

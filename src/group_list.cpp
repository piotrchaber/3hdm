#include "3hdm/group_list.h"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

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
    if (false == std::filesystem::is_directory(path_))
    {
        std::cerr << path_ << " directory does not exist!" << '\n';
        exit(EXIT_FAILURE);
    }

    std::vector<Data> result{};
    for (const auto & entry : std::filesystem::directory_iterator(path_))
    {
        result.push_back(loadFile(entry.path()));
    }
    std::sort(result.begin(), result.end());

    return result;
}

GroupList::Data GroupList::loadFile(const std::string & file_path)
{
    std::fstream ifile{};

    ifile.open(file_path, std::ios::in);
    if (false == ifile.is_open())
    {
        std::cerr << file_path << " file not opening properly!" << '\n';
        exit(EXIT_FAILURE);
    }

    nlohmann::json json_data{nlohmann::json::object()};
    ifile >> json_data;

    Data data{};
    data.structure = json_data["structure"];
    data.generators = json_data["generators"];
    data.representations = json_data["representations"];

    return data;
}

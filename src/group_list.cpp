#include "3hdm/group_list.h"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

static size_t takeStructure(const std::string & group, size_t start)
{
	std::string result;
	while (isdigit(group[++start])) { result += (group[start]); }
	return stoi(result);
}

static size_t takeOrder(const std::string & group)
{
	return takeStructure(group, 1);
}

static size_t takeId(const std::string & group)
{
	return takeStructure(group, group.find(',') + 1);
}

bool GroupList::Data::operator<(const GroupList::Data & right) const
{
	if (takeOrder(this->structure) == takeOrder(right.structure))
	{
		return takeId(this->structure) < takeId(right.structure);
	}
	return takeOrder(this->structure) < takeOrder(right.structure);
}

std::string GroupList::mPath;
std::vector<GroupList::Data> GroupList::mData;

void GroupList::Init(const std::string & path)
{
    mPath = path;
	mData = loadData();
}

std::vector<GroupList::Data> GroupList::All()
{
	return mData;
}

std::vector<GroupList::Data> GroupList::First(size_t length)
{
	return Range(0, length);
}

std::vector<GroupList::Data> GroupList::Order(size_t order)
{
	std::vector<Data> result;

	auto found = std::find_if(mData.cbegin(), mData.cend(), [&](const auto & group) {
		return order == takeOrder(group.structure); });
	while (found != mData.cend() && takeOrder(found->structure) == order)
	{
		result.push_back(*found);
		++found;
	}

	return result;
}

std::vector<GroupList::Data> GroupList::Orders(const std::vector<size_t> & orders)
{
	std::vector<Data> result;
	std::vector<Data> subresult;

	for (auto const & order : orders)
	{
		subresult = Order(order);
		result.insert(result.end(), subresult.begin(), subresult.end());
	}

	return result;
}

std::vector<GroupList::Data> GroupList::Orders(size_t from, size_t to)
{
    assert(from <= to && "The lower limit is greater than the upper one");

    std::vector<Data> result;

	std::copy_if(mData.cbegin(), mData.cend(), std::back_inserter(result), [&](const auto & group) {
			return takeOrder(group.structure) >= from && takeOrder(group.structure) < to; });

	return result;
}

GroupList::Data GroupList::Random()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	size_t index = rand() % mData.size();
	return mData.at(index);
}

std::vector<GroupList::Data> GroupList::Random(size_t howMany)
{
	assert(howMany <= mData.size() && "The number of groups has been exceeded");

	srand(static_cast<unsigned int>(time(nullptr)));
	std::vector<Data> result;
	size_t index;

	while (result.size() < howMany)
	{
		index = rand() % mData.size();
		auto founded = std::binary_search(result.begin(), result.end(), mData.at(index));
		if (founded == false)
		{
			result.insert(std::upper_bound(result.begin(), result.end(), mData.at(index)), mData.at(index));
		}
	}

	return result;
}

std::vector<GroupList::Data> GroupList::Range(size_t first, size_t length)
{
	assert(first + length <= mData.size() && "The number of groups has been exceeded");

	std::vector<Data> result;
	for (auto i = first; i < std::min(first + length, mData.size()); ++i)
	{
		result.push_back(mData.at(i));
	}
	return result;
}

GroupList::Data GroupList::Structure(size_t order, size_t id)
{
	Data result;

	auto found = std::find_if(mData.cbegin(), mData.cend(), [&](const auto & group) {
		return order == takeOrder(group.structure) && id == takeId(group.structure); });
	if (found != mData.cend())
	{
		result = *found;
	}

	return result;
}

std::vector<GroupList::Data> GroupList::Structures(const std::vector<std::pair<size_t, size_t>> & structures)
{
	std::vector<Data> result;
	Data subresult;

	for (auto const & structure : structures)
	{
		subresult = Structure(structure.first, structure.second);
		if (subresult.structure.empty() == false)
		{
			result.push_back(subresult);
		}
	}

	return result;
}

std::vector<GroupList::Data> GroupList::loadData()
{
	std::vector<Data> result;
	Data data;
	auto structures = loadStructures();
	auto gens = loadGens();

	for (auto i = 0; i < std::min(structures.size(), gens.size()); ++i)
	{
		data.gen = gens.at(i);
		data.structure = structures.at(i);
		result.push_back(data);
	}

	return result;
}

std::vector<int> GroupList::loadGens()
{
	auto filePath = std::filesystem::path(mPath + "/gens.txt");
	std::fstream ifile;
	ifile.open(filePath, std::ios::in);
	if (ifile.is_open() == false)
	{
		std::cerr << "File not opening properly!" << '\n';
		exit(EXIT_FAILURE);
	}

	std::vector<int> result;
	int data;
	while (ifile >> data)
	{
		result.push_back(data);
	}

	return result;
}

std::vector<std::string> GroupList::loadStructures()
{
	auto filePath = std::filesystem::path(mPath + "/groups.txt");
	std::fstream ifile;
	ifile.open(filePath, std::ios::in);
	if (ifile.is_open() == false)
	{
		std::cerr << "File not opening properly!" << '\n';
		exit(EXIT_FAILURE);
	}

	std::vector<std::string> result;
	std::string data;
	while (getline(ifile, data))
	{
		result.push_back(data);
	}

	return result;
}

#pragma once

#include <map>
#include <string>
#include <vector>

class GroupList
{
public:
	struct Data
	{
		std::string structure;
		size_t gen;
		bool operator<(const Data& right) const;
	};

	static std::vector<Data> All();
	static std::vector<Data> Order(size_t order);
	static std::vector<Data> Orders(const std::vector<size_t>& orders);
	static Data Random();
	static std::vector<Data> Random(size_t howMany);
	static std::vector<Data> Range(size_t first, size_t length);
	static Data Structure(size_t order, size_t id);
	static std::vector<Data> Structures(const std::vector<std::pair<size_t, size_t>>& structures);


protected:
    static std::vector<Data> loadData();
	static std::vector<int> loadGens();
	static std::vector<std::string> loadStructures();

private:
	static std::vector<Data> mData;
};

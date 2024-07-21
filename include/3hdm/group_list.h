#ifndef GROUPLIST_H
#define GROUPLIST_H

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
		bool operator<(const Data & right) const;
	};

	static void Init(const std::string & path);
	static std::vector<Data> All();
	static std::vector<Data> First(size_t length);
	static std::vector<Data> Order(size_t order);
	static std::vector<Data> Orders(const std::vector<size_t> & orders);
	static std::vector<Data> Orders(size_t from, size_t to);
	static Data Random();
	static std::vector<Data> Random(size_t howMany);
	static std::vector<Data> Range(size_t first, size_t length);
	static Data Structure(size_t order, size_t id);
	static std::vector<Data> Structures(const std::vector<std::pair<size_t, size_t>> & structures);

protected:
    static std::vector<Data> loadData();
	static std::vector<int> loadGens();
	static std::vector<std::string> loadStructures();

private:
	static std::string mPath;
	static std::vector<Data> mData;
};

#endif // GROUPLIST_H

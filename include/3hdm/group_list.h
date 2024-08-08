#ifndef INCLUDE_3HDM_GROUP_LIST_H
#define INCLUDE_3HDM_GROUP_LIST_H

#include <string>
#include <vector>

class GroupList
{
public:
    struct Data
    {
        std::string structure{};
        size_t generators{};
        size_t representations{};
        bool operator<(const Data & right) const;
    };

    static void Init(const std::string & path);
    static std::vector<Data> All();
    static std::vector<Data> First(const size_t length);
    static std::vector<Data> Order(const size_t order);
    static std::vector<Data> Orders(const std::vector<size_t> & orders);
    static std::vector<Data> Orders(const size_t from, const size_t to);
    static Data Random();
    static std::vector<Data> Random(const size_t how_many);
    static std::vector<Data> Range(const size_t first, const size_t length);
    static Data Structure(const size_t order, const size_t id);
    static std::vector<Data> Structures(const std::vector<std::pair<size_t, size_t>> & structures);

private:
    static std::vector<Data> loadData();
    static Data loadFile(const std::string & path);

    static std::string path_;
    static std::vector<Data> data_;
};

#endif  // INCLUDE_3HDM_GROUP_LIST_H

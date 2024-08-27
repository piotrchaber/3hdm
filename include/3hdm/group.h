#ifndef INCLUDE_3HDM_GROUP_H
#define INCLUDE_3HDM_GROUP_H

#include <string>
#include <vector>

#include "group_list.h"
#include "mymatrix.h"
#include "representation.h"

#include "nlohmann/json.hpp"

class Group
{
public:
    Group() = default;
    explicit Group(const GroupList::Data & data);
    Group (const std::string & structure, const size_t number_of_generators, const size_t number_of_representations);
    virtual ~Group() = default;

    std::vector<MyMatrix3cd> generator(const size_t ith) const;
    std::vector<MyMatrix3cd> generator(const size_t ith, const std::vector<size_t> & combination) const;
    void load(const std::string & file_directory);
    void load(const std::string & file_name, const std::string & file_directory);
    size_t numberOfGenerators() const;
    size_t numberOfRepresentations() const;
    const Representation3cd & representation(const size_t ith) const;
    const std::vector<Representation3cd> & representations() const;
    void setData(const GroupList::Data & data);
    void setNumberOfGenerators(const size_t number_of_generators);
    void setNumberOfRepresentations(const size_t number_of_representations);
    void setStructure(const std::string & structure);
    const std::string & structure() const;

private:
    void check(const nlohmann::json & json_data) const;
    void loadRepresentations(const nlohmann::json & json_data);

    std::string structure_{};
    size_t number_of_generators_{};
    size_t number_of_representations_{};
    std::vector<Representation3cd> representations_{};
};

#endif  // INCLUDE_3HDM_GROUP_H

#ifndef INCLUDE_3HDM_GROUP_H
#define INCLUDE_3HDM_GROUP_H

#include <string>
#include <vector>

#include "mymatrix.h"
#include "representation.h"

class Group
{
public:
    explicit Group(const std::string & structure = "");
    Group(const std::string & structure, const size_t number_of_generators);
    explicit Group(const std::vector<Representation3cd> & representations, const std::string & structure = "");
    Group(const std::vector<Representation3cd> & representations, const std::string & structure, const size_t number_of_generators);
    virtual ~Group() = default;

    std::vector<MyMatrix3cd> generator(const size_t ith) const;
    std::vector<MyMatrix3cd> generator(const size_t ith, const std::vector<size_t> & combination) const;
    void load(const std::string & file_directory);
    void load(const std::string & file_name, const std::string & file_directory);
    size_t numberOfGenerators() const;
    size_t numberOfRepresentations() const;
    const Representation3cd & representation(const size_t ith) const;
    const std::vector<Representation3cd> & representations() const;
    void setNumberOfGenerators(const size_t number_of_generators);
    void setRepresentations(const std::vector<Representation3cd> & representations);
    void setStructure(const std::string & structure);
    const std::string & structure() const;

private:
    std::vector<Representation3cd> representations_{};
    std::string structure_{};
    size_t number_of_generators_{};
};

#endif  // INCLUDE_3HDM_GROUP_H

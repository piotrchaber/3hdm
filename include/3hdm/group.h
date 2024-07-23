#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

#include "mymatrix.h"
#include "representation.h"

class Group
{
public:
    explicit Group(const std::string & structure = "");
    Group(const std::string & structure, size_t numberOfGenerators);
    explicit Group(const std::vector<Representation3cd> & representations, const std::string & structure = "");
    Group(const std::vector<Representation3cd> & representations, const std::string & structure, size_t numberOfGenerators);
    virtual ~Group() = default;

    std::vector<MyMatrix3cd> generator(size_t ith) const;
    std::vector<MyMatrix3cd> generator(size_t ith, const std::vector<size_t> & combination) const;
    void load(const std::string & fileDir);
    void load(const std::string & fileName, const std::string & fileDir);
    const size_t & numberOfGenerators() const;
    size_t numberOfRepresentations() const;
    const Representation3cd & representation(size_t ith) const;
    const std::vector<Representation3cd> & representations() const;
    void setNumberOfGenerators(size_t numberOfGenerators);
    void setRepresentations(const std::vector<Representation3cd> & representations);
    void setStructure(const std::string & structure);
    const std::string & structure() const;

private:
    std::vector<Representation3cd> mRepresentations;
    std::string mStructure;
    size_t mNumberOfGenerators;
};

#endif // GROUP_H

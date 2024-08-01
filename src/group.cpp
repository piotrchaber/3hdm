#include "3hdm/group.h"

#include <cassert>
#include <filesystem>

Group::Group(const std::string & structure)
    : structure_(structure), number_of_generators_(0)
{
}

Group::Group(const std::string & structure, const size_t number_of_generators)
    : structure_(structure), number_of_generators_(number_of_generators)
{
}

Group::Group(const std::vector<Representation3cd> & representations, const std::string & structure)
    : representations_(representations), structure_(structure), number_of_generators_(0)
{
}

Group::Group(const std::vector<Representation3cd> & representations, const std::string & structure, const size_t number_of_generators)
    : representations_(representations), structure_(structure), number_of_generators_(number_of_generators)
{
}

std::vector<MyMatrix3cd> Group::generator(const size_t ith) const
{
    assert((ith > 0 || ith <= number_of_generators_) && "Generator number has been exceeded");

    std::vector<MyMatrix3cd> result{};

    for (const auto & representation : representations_)
    {
        result.push_back(representation.matrices().at(ith - 1));
    }

    return result;
}

std::vector<MyMatrix3cd> Group::generator(const size_t ith, const std::vector<size_t> & combination) const
{
    const std::vector<MyMatrix3cd> matrices{generator(ith)};
    std::vector<MyMatrix3cd> result{};

    for (const auto coefficient : combination)
    {
        result.push_back(matrices.at(coefficient - 1));
    }

    return result;
}


void Group::load(const std::string & file_directory)
{
    load(structure_, file_directory);
}

void Group::load(const std::string & file_name, const std::string & file_directory)
{
    const std::filesystem::path file_path{file_directory + '/' + file_name};
    std::fstream ifile{};

    ifile.open(file_path, std::ios::in);
    if (false == ifile.is_open())
    {
        std::cerr << file_path << " file not opening properly!" << '\n';
        exit(EXIT_FAILURE);
    }

    MyMatrix3cd matrix{};
    std::vector<MyMatrix3cd> matrices{};
    std::string matrix_row{};
    std::stringstream ss{};
    size_t dimension{0};
    size_t generators{0};

    representations_.clear();
    while (std::getline(ifile, matrix_row))
    {
        ss << matrix_row + '\n';
        if (3 == ++dimension)
        {
            ++generators;
            matrix.load(ss);
            matrices.push_back(matrix);
            ss.str(std::string());
            ss.clear();
            dimension = 0;
        }
        if (generators == number_of_generators_)
        {
            representations_.push_back(Representation3cd(matrices));
            matrices.clear();
            generators = 0;
        }
    }
}

size_t Group::numberOfGenerators() const
{
    return number_of_generators_;
}

size_t Group::numberOfRepresentations() const
{
    return representations_.size();
}

const Representation3cd & Group::representation(const size_t ith) const
{
    return representations_.at(ith - 1);
}

const std::vector<Representation3cd> & Group::representations() const
{
    return representations_;
}

void Group::setNumberOfGenerators(const size_t number_of_generators)
{
    number_of_generators_ = number_of_generators;
}

void Group::setRepresentations(const std::vector<Representation3cd> & representations)
{
    representations_ = representations;
}

void Group::setStructure(const std::string & structure)
{
    structure_ = structure;
}

const std::string & Group::structure() const
{
    return structure_;
}

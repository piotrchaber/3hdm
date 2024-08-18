#include "3hdm/group.h"

#include <cassert>
#include <filesystem>

#include "nlohmann/json.hpp"

Group::Group(const GroupList::Data & data)
    : structure_(data.structure), number_of_generators_(data.generators), number_of_representations_(data.representations)
{
}

Group::Group(const std::string & structure, const size_t number_of_generators, const size_t number_of_representations)
    : structure_(structure), number_of_generators_(number_of_generators), number_of_representations_(number_of_representations)
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
    const std::filesystem::path file_path{file_directory + '/' + file_name + ".json"};
    std::fstream ifile{};

    ifile.open(file_path, std::ios::in);
    if (false == ifile.is_open())
    {
        std::cerr << file_path << " file not opening properly!" << '\n';
        exit(EXIT_FAILURE);
    }

    nlohmann::json json_data{nlohmann::json::object()};
    ifile >> json_data;

    MyMatrix3cd matrix{};
    std::vector<MyMatrix3cd> matrices{};
    std::stringstream ss{};

    representations_.clear();
    for (auto const & json_representation : json_data["matrices"])
    {
        for (auto const & json_matrix : json_representation)
        {
            ss << json_matrix.get<std::string>();
            matrix.load(ss);
            matrices.push_back(matrix);
            ss.str(std::string());
            ss.clear();
        }
        representations_.push_back(Representation3cd(matrices));
        matrices.clear();
    }
}

void Group::setData(const GroupList::Data & data)
{
    setStructure(data.structure);
    setNumberOfGenerators(data.generators);
    setNumberOfRepresentations(data.representations);
}

size_t Group::numberOfGenerators() const
{
    return number_of_generators_;
}

size_t Group::numberOfRepresentations() const
{
    return number_of_representations_;
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

void Group::setNumberOfRepresentations(const size_t number_of_representations)
{
    number_of_representations_ = number_of_representations;
}

void Group::setStructure(const std::string & structure)
{
    structure_ = structure;
}

const std::string & Group::structure() const
{
    return structure_;
}

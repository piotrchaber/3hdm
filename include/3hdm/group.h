#pragma once

#include <string>
#include <vector>

#include "../../include/3hdm/mymatrix.h"
#include "../../include/3hdm/representation.h"

class Group
{
public:
	explicit Group(const std::string& structure = "");
	Group(const std::string& structure, size_t numberOfGenerators);
	explicit Group(const std::vector<Representation3cd>& representations, const std::string& structure = "");
	Group(const std::vector<Representation3cd>& representations, const std::string& structure, size_t numberOfGenerators);
	virtual ~Group() = default;

	std::vector<MyMatrix3cd> generator(size_t ith) const;
	void loadFromFile(const std::string& fileDir = "", const std::string& fileName = "");
	const size_t& numberOfGenerators() const;
	size_t numberOfRepresentations() const;
	const Representation3cd& representation(size_t ith) const;
	const std::vector<Representation3cd>& representations() const;
	void setNumberOfGenerators(size_t numberOfGenerators);
	void setRepresentations(const std::vector<Representation3cd>& representations);
	void setStructure(const std::string& structure);
	const std::string& structure() const;

private:
	std::vector<Representation3cd> mRepresentations;
	std::string mStructure;
	size_t mNumberOfGenerators;
};
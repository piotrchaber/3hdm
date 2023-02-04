#include "3hdm/group.h"

#include <filesystem>

Group::Group(const std::string & structure)
	: mStructure(structure), mNumberOfGenerators(0)
{
}

Group::Group(const std::string & structure, size_t numberOfGenerators)
	: mStructure(structure), mNumberOfGenerators(numberOfGenerators)
{
}

Group::Group(const std::vector<Representation3cd> & representations, const std::string & structure)
	: mRepresentations(representations), mStructure(structure), mNumberOfGenerators(0)
{
}

Group::Group(const std::vector<Representation3cd> & representations, const std::string & structure, size_t numberOfGenerators)
	: mRepresentations(representations), mStructure(structure), mNumberOfGenerators(numberOfGenerators)
{
}

std::vector<MyMatrix3cd> Group::generator(size_t ith) const
{
	std::vector<MyMatrix3cd> result;

	for (const auto & representation : mRepresentations) {
		result.push_back(representation.matrices().at(ith - 1));
	}

	return result;
}

void Group::load(const std::string & fileDir)
{
    load(mStructure, fileDir);
}

void Group::load(const std::string & fileName, const std::string & fileDir)
{
	auto filePath = std::filesystem::path(fileDir + '/' + fileName);
	std::fstream ifile;
	ifile.open(filePath, std::ios::in);
	if (ifile.is_open() == false) {
		std::cerr << filePath << " file not opening properly!" << std::endl;
		exit(EXIT_FAILURE);
	}

	MyMatrix3cd matrix;
	std::vector<MyMatrix3cd> matrices;
	std::string matrixRow;
	std::stringstream ss;
	size_t dimController = 0;
	size_t genController = 0;

	mRepresentations.clear();
	while (std::getline(ifile, matrixRow)) {
		ss << matrixRow + '\n';
		if (++dimController == 3) {
			++genController;
			matrix.load(ss);
			matrices.push_back(matrix);
			ss.str(std::string());
			ss.clear();
			dimController = 0;
		}
		if (genController == mNumberOfGenerators) {
			mRepresentations.push_back(Representation3cd(matrices));
			matrices.clear();
			genController = 0;
		}
	}
}

const size_t & Group::numberOfGenerators() const
{
	return mNumberOfGenerators;
}

size_t Group::numberOfRepresentations() const
{
	return mRepresentations.size();
}

const Representation3cd & Group::representation(size_t ith) const
{
	return mRepresentations.at(ith - 1);
}

const std::vector<Representation3cd> & Group::representations() const
{
	return mRepresentations;
}

void Group::setNumberOfGenerators(size_t numberOfGenerators)
{
	mNumberOfGenerators = numberOfGenerators;
}

void Group::setRepresentations(const std::vector<Representation3cd> & representations)
{
	mRepresentations = representations;
}

void Group::setStructure(const std::string & structure)
{
	mStructure = structure;
}

const std::string & Group::structure() const
{
	return mStructure;
}

// TODO: write an assert for ith < 1 && ith > mNumberOfGenerators in generator method
// TODO: examine the case when the mNumberOfGenerators is equal to 0 (exception)
// TODO: break loadFromFile method into smaller functions
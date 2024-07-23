#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <filesystem>
#include <iostream>
#include <vector>

#include "3hdm/group_list.h"
#include "3hdm/group.h"
#include "3hdm/invariance_equation_solver.h"
#include "3hdm/unique_solutions_seeker.h"

std::filesystem::path findBuildPath();
void print(const std::vector<size_t> & combination);
void print(const std::vector<size_t> & combination, const std::string & message);
void print(const Group & group);
void print(const GroupList::Data & groupInfo, const std::string & message = "");
void print(const std::vector<GroupList::Data> & groupsInfo, const std::string & message = "");
void print(const MatrixForm & matrixForm, const std::string & message);
void print(const Representation3cd & representation);
void print(const Solution & solution);
void print(const Solutions & solutions);
void print(const UniqueSolution & unique, std::ostream & os = std::cout);
void print(const UniqueSolutions & uniques, std::ostream & os = std::cout);
std::string toString(const std::vector<size_t> & vector, const char sep = ' ');

#endif // TUTORIAL_H

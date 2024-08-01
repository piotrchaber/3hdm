#ifndef INCLUDE_3HDM_INVARIANCE_EQUATION_SOLVER_H
#define INCLUDE_3HDM_INVARIANCE_EQUATION_SOLVER_H

#include <map>
#include <string>
#include <vector>

#include "combination.h"
#include "group.h"
#include "matrix_form.h"
#include "mymatrix.h"

class InvarianceEquationSolver
{
public:
    class Solution : public MyMatrixXcd
    {
        struct Origin
        {
            std::string group{};
            std::vector<size_t> combination{};
        };

    public:
        enum class Form { Original, Particular, General };

        virtual ~Solution() = default;

        bool isGood() const;
        Form form() const;
        const Origin & origin() const;
        const MyVectorXcd & phase(const size_t ith) const;
        size_t phases() const;
        void switchFormTo(const Form form);

    private:
        void takeForm();

        using MyMatrixXcd::operator=;
        Form form_{};
        Origin origin_{};
        bool is_good_{false};
        std::vector<MyVectorXcd> phases_{};
        MyMatrixXcd initial_form_{};
        friend class InvarianceEquationSolver;
    };

    enum class Particles { ChargedLeptons, DiracNeutrino, MajoranaNeutrino };

    InvarianceEquationSolver(const Particles particles, const Solution::Form form);
    InvarianceEquationSolver(const Particles particles, const Solution::Form form, const Group & group);
    InvarianceEquationSolver(const Particles particles, const Solution::Form form, const Group & group, const std::vector<size_t> & combination);
    virtual ~InvarianceEquationSolver() = default;

    void compute(const Group & group, const std::vector<size_t> & combination);
    void compute(const Group & group);
    const std::vector<MyMatrixXcd> & eigenvectors1() const;
    const std::vector<MyMatrixXcd> & invarianceMatrices() const;
    const MyMatrixXcd & intersectionBasis() const;
    const Solution & solution() const;
    const std::vector<Solution> & solutions() const;

private:
    enum class EquationState { NoProblem, NoEigenvectors, NoEigensubspace };

    bool checkSolution() const;
    MyMatrixXcd findEigenvectors1(const MyMatrixXcd & matrix);
    void findEigenvectors1();
    MyMatrixXcd findIntersectionBasis(const MyMatrixXcd & lhs_matrix, const MyMatrixXcd & rhs_matrix);
    void findIntersectionBasis();
    std::vector<MyMatrix3cd> prepareMatrices(const Group & group, const size_t ith_generator, const std::vector<size_t> & combination);
    MyMatrixXcd generateInvarianceMatrix(const Group & group, const size_t ith_generator, const std::vector<size_t> & combination);
    void generateInvarianceMatrices(const Group & group, const std::vector<size_t> & combination);
    void prepareSolution(const Group & group, const std::vector<size_t> & combination);
    void reset();
    void setForm(const Solution::Form form);
    void setParticles(const Particles particles);

    EquationState equation_state_{EquationState::NoProblem};
    std::vector<MyMatrixXcd> invariance_matrices_{};
    std::vector<MyMatrixXcd> eigenvectors1_{};
    MyMatrixXcd intersection_basis_{};
    Solution solution_{};
    std::vector<Solution> solutions_{};
    std::string shape_{};
    std::string operation_{};
};

typedef InvarianceEquationSolver::Particles Particles;
typedef InvarianceEquationSolver::Solution Solution;
typedef std::vector<InvarianceEquationSolver::Solution> Solutions;

#endif  // INCLUDE_3HDM_INVARIANCE_EQUATION_SOLVER_H

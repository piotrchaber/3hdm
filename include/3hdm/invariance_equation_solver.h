#ifndef INVARIANCEEQUATIONSOLVER_H
#define INVARIANCEEQUATIONSOLVER_H

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
			std::string group;
			std::vector<size_t> combination;
		};

	public:
		enum class Form { Original, Particular, General };

		virtual ~Solution() = default;

		const bool & isGood() const;
		const Form & form() const;
		const Origin & origin() const;
		const MyVectorXcd & phase(size_t ith) const;
		int phases() const;
		void switchFormTo(Form form);

	private:
		void takeForm();

		using MyMatrixXcd::operator=;
		Form mForm;
		Origin mOrigin;
		bool mIsGood = false;
		std::vector<MyVectorXcd> mPhases;
		MyMatrixXcd mInitialForm;
		friend class InvarianceEquationSolver;
	};

	enum class Particles { ChargedLeptons, DiracNeutrino, MajoranaNeutrino };
	typedef Solution::Form Form;

	InvarianceEquationSolver(const Particles & particles, const Form & form);
	InvarianceEquationSolver(const Particles & particles, const Form & form, const Group & group);
	InvarianceEquationSolver(const Particles & particles, const Form & form, const Group & group, const std::vector<size_t> & combination);
	virtual ~InvarianceEquationSolver() = default;

    void compute(const Group & group, const std::vector<size_t> & combination);
	void compute(const Group & group);
	const std::vector<MyMatrixXcd> & eigenvectors1() const;
	const std::vector<MyMatrixXcd> & invarianceMatrices() const;
	const MyMatrixXcd & intersectionBasis() const;
	const Solution & solution() const;
	const std::vector<Solution> & solutions() const;

protected:
	bool checkSolution() const;
	MyMatrixXcd findEigenvectors1(const MyMatrixXcd & matrix);
	void findEigenvectors1();
	MyMatrixXcd findIntersectionBasis(const MyMatrixXcd & matrix1, const MyMatrixXcd & matrix2);
	void findIntersectionBasis();
	std::vector<MyMatrix3cd> prepareMatrices(const Group & group, size_t generator, const std::vector<size_t> & combination);
	MyMatrixXcd generateInvarianceMatrix(const Group & group, size_t generator, const std::vector<size_t> & combination);
	void generateInvarianceMatrices(const Group & group, const std::vector<size_t> & combination);
	void prepareSolution(const Group & group, const std::vector<size_t> & combination);
	void reset();
	void setForm(const Form & form);
	void setParticles(const Particles & particles);

private:
	enum class EquationState { NoProblem, NoEigenvectors, NoEigensubspace };

	EquationState mEquationState = EquationState::NoProblem;
	std::vector<MyMatrixXcd> mInvarianceMatrices;
	std::vector<MyMatrixXcd> mEigenvectors1;
	MyMatrixXcd mIntersectionBasis;
	Solution mSolution;
	std::vector<Solution> mSolutions;
	std::string mShape;
	std::string mOperation;
};

typedef InvarianceEquationSolver::Particles Particles;
typedef InvarianceEquationSolver::Solution Solution;
typedef std::vector<InvarianceEquationSolver::Solution> Solutions;

#endif // INVARIANCEEQUATIONSOLVER_H

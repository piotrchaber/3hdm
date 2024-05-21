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
		using MyMatrixXcd::operator=;
		using MyMatrixXcd::MyMatrixXcd;
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
	InvarianceEquationSolver(const Group & group, const Particles & particles, const Form & form);
	InvarianceEquationSolver(const Group & group, const std::vector<size_t> & combination, const Particles & particles, const Form & form);
	virtual ~InvarianceEquationSolver() = default;

	void compute(const Group & group);
	void compute(const Group & group, const std::vector<size_t> & combination);
	const std::vector<MyMatrixXcd> & eigenvectors1() const;
	const std::vector<MyMatrixXcd> & invarianceMatrices() const;
	const Solution & solution() const;
	const std::vector<Solution> & solutions() const;

protected:
	bool checkSolution() const;
	void findEigenvector1(const MyMatrixXcd & matrix);
	void findEigenvectors1();
	void findIntersectionBasis();
	void findIntersectionBasis(const MyMatrixXcd & matrix1, const MyMatrixXcd & matrix2);
	void generateInvarianceMatrices(const Group & group, const std::vector<size_t> & combination);
	void generateInvarianceMatrix(std::vector<MyMatrix3cd> & matrices);
	void reset();
	void setParticles(const Particles & particles);

private:
	enum class EquationState { NoProblem, NoEigenvectors, NoEigensubspace };

	EquationState mEquationState = EquationState::NoProblem;
	std::vector<MyMatrixXcd> mInvarianceMatrices;
	std::vector<MyMatrixXcd> mEigenvectors1;
	Solution mIntersectionBasis;
	std::vector<Solution> mIntersectionBases;
	std::string mShape;
	std::string mOperation;
};

typedef InvarianceEquationSolver::Particles Particles;
typedef InvarianceEquationSolver::Solution Solution;
typedef std::vector<InvarianceEquationSolver::Solution> Solutions;

#endif // INVARIANCEEQUATIONSOLVER_H

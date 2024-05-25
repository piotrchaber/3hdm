#ifndef MATRIXFORM_H
#define MATRIXFORM_H

#include <vector>

#include "mymatrix.h"

class MatrixForm
{
public:
    enum class Form { Original, Particular, General };

    MatrixForm(const MyMatrixXcd & matrix, const Form & form);
    
    const MyMatrixXcd & matrix() const;
    const MyVectorXcd & phase(size_t ith) const;
    const std::vector<MyVectorXcd> & phases() const;

protected:
    void setGeneralForm();
    void setOriginalForm();
    void setParticularForm();
    void setMatrixForm(const Form & form);
    void setActualZero();
    void sortByIndex();
    void setFirstElementTo(const std::complex<double> & value);
    void extractColumnAndPhase();

private:
    MyMatrixXcd mMatrix;
    std::vector<MyVectorXcd> mPhases;
};

#endif // MATRIXFORM_H

#ifndef MATRIXFORM_H
#define MATRIXFORM_H

#include <vector>

#include "mymatrix.h"

class MatrixForm
{
public:
    enum class Form { Original, Particular, General };

    MatrixForm(const MyMatrixXcd & matrix, const Form & form);
    
    const Form & form() const;
    const MyMatrixXcd & matrix() const;
    const MyVectorXcd & phase(size_t ith) const;
    const std::vector<MyVectorXcd> & phases() const;
    void switchFormTo(const Form & form);

protected:
    void setGeneralForm();
    void setOriginalForm();
    void setParticularForm();
    void setMatrixForm();
    void setActualZero();
    void sortByIndex();
    void setFirstElementTo(const std::complex<double> & value);
    void extractColumnAndPhase();

private:
    const MyMatrixXcd mInitialMatrix;
    MyMatrixXcd mMatrix;
    Form mForm;
    std::vector<MyVectorXcd> mInitialPhases;
    std::vector<MyVectorXcd> mPhases;
};

#endif // MATRIXFORM_H

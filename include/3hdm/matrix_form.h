#ifndef INCLUDE_3HDM_MATRIX_FORM_H
#define INCLUDE_3HDM_MATRIX_FORM_H

#include <vector>

#include "mymatrix.h"

class MatrixForm
{
public:
    enum class Form { Original, Particular, General };

    MatrixForm(const MyMatrixXcd & matrix, const Form form);

    const MyMatrixXcd & matrix() const;
    const MyVectorXcd & phase(const size_t ith) const;
    const std::vector<MyVectorXcd> & phases() const;

private:
    void setGeneralForm();
    void setOriginalForm();
    void setParticularForm();
    void setMatrixForm(const Form form);
    void setActualZero();
    void sortByIndex();
    void setFirstElementTo(const std::complex<double> & value);
    void extractColumnAndPhase();

    MyMatrixXcd matrix_{};
    std::vector<MyVectorXcd> phases_{};
};

#endif  // INCLUDE_3HDM_MATRIX_FORM_H

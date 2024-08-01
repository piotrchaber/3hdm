#ifndef INCLUDE_3HDM_MYMATRIX_SIMPL_H
#define INCLUDE_3HDM_MYMATRIX_SIMPL_H

template <typename Object, bool is_complex>
struct setActualZeroImpl
{
    void operator()(Object & object);
};

template <typename Object, bool is_complex>
void setActualZeroImpl<Object, is_complex>::operator()(Object & object)
{
    for (auto row = 0; row < object.rows(); ++row)
    {
        for (auto col = 0; col < object.cols(); ++col)
        {
            if (fabs(object(row, col)) < 0.000001)
            {
                object(row, col) = 0.0;
            }
        }
    }
}

template <typename Object>
struct setActualZeroImpl<Object, true>
{
    void operator()(Object & object);
};

template<typename Object>
void setActualZeroImpl<Object, true>::operator()(Object & object)
{
    for (auto row = 0; row < object.rows(); ++row)
    {
        for (auto col = 0; col < object.cols(); ++col)
        {
            if (fabs(object(row, col).imag()) < 0.000001)
            {
                object(row, col).imag(0.0);
            }
            if (fabs(object(row, col).real()) < 0.000001)
            {
                object(row, col).real(0.0);
            }
        }
    }
}

#endif  // INCLUDE_3HDM_MYMATRIX_SIMPL_H

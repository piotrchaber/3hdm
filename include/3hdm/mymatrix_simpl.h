#ifndef MYMATRIXSIMPL_H
#define MYMATRIXSIMPL_H

template <typename Object, bool isComplex>
struct setActualZeroImpl
{
    void operator()(Object & object);
};

template <typename Object, bool isComplex>
void setActualZeroImpl<Object, isComplex>::operator()(Object & object)
{
    for (int row = 0; row < object.rows(); ++row)
    {
        for (int col = 0; col < object.cols(); ++col)
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
    for (int row = 0; row < object.rows(); ++row)
    {
        for (int col = 0; col < object.cols(); ++col)
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

#endif // MYMATRIXSIMPL_H

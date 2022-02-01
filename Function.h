#ifndef LAB3_FUNCTION_H
#define LAB3_FUNCTION_H

template <class T>
int compareT1(T a, T b)
{
    if (a < b)
    {
        return 0;
    }
    if (a > b)
    {
        return 1;
    }
    return 2;
}
#endif


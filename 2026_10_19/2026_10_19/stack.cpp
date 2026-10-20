#include "stack.h"
template<class T>
T Add(const T& left, const T& right)
{
    return left + right;
}

int Func(int x, int y) {
    return x + y;
}

//1.
template
int Add<int>(const int& left, const int& right);

template
double Add<double>(const double& left, const double& right);
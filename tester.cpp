#include <bits/stdc++.h>

#include "CNN/CNN.hpp"

#include "MNIST/mnist.hpp"

int main()
{
    Matrix<double> a={{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0}};
    Matrix<double> b={{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0}};
    col_valarray<double> c={2,2};
    row_valarray<double> d={2,2,2,2};

    a/=c;
    b/=d;

    out(a);
    out(b);
}
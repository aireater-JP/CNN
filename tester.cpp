#include <bits/stdc++.h>

#include "CNN/CNN.hpp"

#include "MNIST/mnist.hpp"

int main()
{
    Matrix<double> a={{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0}};
    col_valarray<double> b={2,2};

    out(a/b);
}
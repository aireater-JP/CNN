#include <bits/stdc++.h>

#include "CNN/CNN.hpp"

int main()
{
    ReLU r;
    r.initialize({1,2,4});

    std::vector<Matrix<double>> a={{{1,2,-1,-2},{-9,-9,9,-9}}};
    std::vector<Matrix<double>> b={{{100,100,100,100},{100,100,100,100}}};

    out(a[0]);

    out(r.forward(a)[0]);

    out(r.backward(b)[0]);
}
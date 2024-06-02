#include <bits/stdc++.h>

#include "CNN/out.hpp"
#include "CNN/CNN.hpp"

int main()
{
    NN nn;
    nn.add_Layer(Affine(64));
    nn.add_Layer(ReLU());
    nn.add_Layer(Affine(10));
    nn.set_Loss(Softmax_with_Loss());

    std::vector<Matrix<double>> x={{{1,2,3},{4,5,6}},{{7,8,9},{10,11,12}}};
    std::vector<Matrix<double>> t={{{-1,-2,-3},{-4,-5,-6}},{{-7,-8,-9},{-10,-11,-12}}};

    nn.initialize({2,2,3});

    out(nn.gradient(x,t));
}
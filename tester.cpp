#include <bits/stdc++.h>

#include "CNN/CNN.hpp"

int main()
{
    NN nn;
    nn.add_Layer(Convolution2D(2, {0, 0}, {2, 2}, {2, 2}));
    nn.add_Layer(ReLU());
    nn.add_Layer(Flatten());
    nn.add_Layer(Affine(16));
    nn.set_Loss(Identity_with_Loss());

    nn.initialize({1, 4, 4});

    std::vector<Matrix<double>> x = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}};
    std::vector<Matrix<double>> t = {{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}}};

    for (size_t i = 0; i < 100; ++i)
    {
        out(nn.gradient(x, t));
        nn.update(0.1);
    }

    out(nn.predict(x)[0]);
}
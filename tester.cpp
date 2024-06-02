#include <bits/stdc++.h>

#include "CNN/CNN.hpp"

#include "MNIST/mnist.hpp"

Matrix<double> change(const std::vector<unsigned char> &x)
{
    Matrix<double> y(28, 28);
    for (size_t i = 0; i < MNIST_size; ++i)
    {
        y.at(i) = x[i] / 255.0;
    }
    return y;
}

int main()
{
    mnist m;

    NN nn;
    nn.add_Layer(Convolution2D(16, {0, 0}, {2, 2}, {2, 2}));
    nn.add_Layer(ReLU());
    nn.add_Layer(MaxPooling({2, 2}));

    nn.add_Layer(Flatten());
    nn.add_Layer(Affine(64));
    nn.add_Layer(ReLU());
    nn.add_Layer(Affine(10));

    nn.set_Loss(Softmax_with_Loss());

    nn.initialize({1, 28, 28});

    Random<std::uniform_int_distribution<>> R(0, 60000 - 1);

    for (size_t i = 0; i < 1024 * 1024; ++i)
    {
        double average = 0;
        int r = R();
        for (size_t j = 0; j < 100; ++j)
        {
            std::vector<Matrix<double>> x = {change(m.get_trai_img(r))};
            std::vector<Matrix<double>> t = {Matrix<double>(1, 10)};
            t[0].at(0, m.get_trai_label(r)) = 1;

            average += nn.gradient(x, t);
        }

        out(average / 100);

        nn.update(0.005);
        newline();
    }
}
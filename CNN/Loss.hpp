#pragma once

#include "Matrix.hpp"

class Loss
{
public:
    virtual double forward(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &t) = 0;
    virtual std::vector<Matrix<double>> backward() = 0;
};

#include "Loss/Softmax.hpp"
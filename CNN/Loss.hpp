#pragma once

#include "Utility.hpp"

class Loss
{
public:
    virtual double forward(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &t) = 0;
    virtual std::vector<Matrix<double>> backward() = 0;

    void initialize(const Matrix_size input_size) { Loss::input_size = input_size; };

protected:
    Matrix_size input_size;
};

#include "Loss/Softmax.hpp"
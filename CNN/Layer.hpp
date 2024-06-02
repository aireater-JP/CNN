#pragma once

#include "Utility.hpp"

class Layer
{
public:
    virtual Matrix_size initialize(const Matrix_size input_size) = 0;

    virtual std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) = 0;
    virtual std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y) = 0;

    virtual void update(const double learning_rate) {};

protected:
    Matrix_size input_size;
};

enum Init_type
{
    // Sigmoid
    Xavier,
    // ReLU
    He
};

#include "Layer/Affine.hpp"
#include "Layer/Convolutional2D.hpp"
#include "Layer/MaxPooling.hpp"
#include "Layer/ReLU.hpp"
#include "Layer/Flatten.hpp"
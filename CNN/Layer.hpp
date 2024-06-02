#pragma once

#include "Matrix.hpp"

struct Matrix_size
{
    size_t x, y, z;
};

class Layer
{
public:
    virtual void set_input_size(const Matrix_size input_size) = 0;
    virtual Matrix_size get_output_size() = 0;

    virtual std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) = 0;
    virtual std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y) = 0;

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

std::vector<Matrix<double>> make_vec_mat(Matrix_size size) { return std::vector<Matrix<double>>(size.x, Matrix<double>(size.y, size.z)); }

#include "Affine.hpp"
#include "Convolutional2D.hpp"
#include "MaxPooling.hpp"
#include "ReLU.hpp"
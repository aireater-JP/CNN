#pragma once

#include "Matrix.hpp"
#include "Random.hpp"
#include "out.hpp"

struct Matrix_size
{
    size_t x, y, z;
};

std::vector<Matrix<double>> make_vec_mat(Matrix_size size) { return std::vector<Matrix<double>>(size.x, Matrix<double>(size.y, size.z)); }
#pragma once

#include "../Layer.hpp"

class Flatten : public Layer
{
public:
    Matrix_size initialize(const Matrix_size input_size)
    {
        Layer::input_size = input_size;
        return {1, 1, input_size.x * input_size.y * input_size.z};
    }
    
    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)
    {
        std::vector<Matrix<double>> y(1, Matrix<double>(1, input_size.x * input_size.y * input_size.z));
        for (size_t i = 0; i < input_size.x; ++i)
        {
            for (size_t j = 0; j < input_size.y; ++j)
            {
                for (size_t k = 0; k < input_size.z; ++k)
                {
                    y[0].at(0, i * (input_size.y * input_size.z) + j * input_size.z + k) = x[i].at(j, k);
                }
            }
        }
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y)
    {
        std::vector<Matrix<double>> x(make_vec_mat(input_size));
        for (size_t i = 0; i < input_size.x; ++i)
        {
            for (size_t j = 0; j < input_size.y; ++j)
            {
                for (size_t k = 0; k < input_size.z; ++k)
                {
                    x[i].at(j, k) = y[0].at(0, i * (input_size.y * input_size.z) + j * input_size.z + k);
                }
            }
        }
        return x;
    }
};
#include "../Layer.hpp"

#include <cfloat>

class MaxPooling : public Layer
{
    std::pair<size_t, size_t> stride;

    std::vector<Matrix<size_t>> x_mask;
    std::vector<Matrix<size_t>> y_mask;

    Matrix_size input_size;
    std::pair<size_t, size_t> output_size;

public:
    MaxPooling(std::pair<size_t, size_t> stride)
        : stride(stride) {}

    void set_input_size(Matrix_size input_size) override
    {
        input_size = input_size;

        if (input_size.y % stride.first != 0 or input_size.z % stride.second != 0)
        {
            throw std::invalid_argument("出力サイズが確定できません");
        }

        output_size.first = input_size.y / stride.first;
        output_size.second = input_size.z / stride.second;
    }

    Matrix_size get_output_size() override { return {input_size.x, output_size.first, output_size.second}; }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) override
    {
        std::vector<Matrix<double>> y(input_size.x);
        for (size_t i = 0; i < input_size.x; ++i)
        {
            y[i] = forward_pooling(x[i], y_mask[i], x_mask[i]);
        }
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y) override
    {
        std::vector<Matrix<double>> x(input_size.x, Matrix<double>(input_size.y, input_size.z));
        for (size_t i = 0; i < input_size.x; ++i)
        {
            backward_pooling(y[i], x[i], y_mask[i], x_mask[i]);
        }
        return y;
    }

private:
    Matrix<double> forward_pooling(const Matrix<double> &x, Matrix<size_t> &y_mask, Matrix<size_t> &x_mask)
    {
        Matrix<double> y(output_size.first, output_size.second, -DBL_MAX);
        for (size_t i = 0; i < output_size.first; ++i)
        {
            for (size_t j = 0; j < output_size.second; ++j)
            {
                for (size_t m = 0; m < stride.first; ++m)
                {
                    for (size_t n = 0; n < stride.second; ++n)
                    {
                        size_t col = i * stride.first + m;
                        size_t row = j * stride.second + n;
                        if (y.at(i, j) >= x.at(col, row))
                        {
                            continue;
                        }
                        y.at(i, j) = x.at(col, row);
                        y_mask.at(i, j) = col;
                        x_mask.at(i, j) = row;
                    }
                }
            }
        }
        return y;
    }

    void backward_pooling(const Matrix<double> &y, Matrix<double> &x, Matrix<size_t> &y_mask, Matrix<size_t> &x_mask)
    {
        for (size_t i = 0; i < output_size.first; ++i)
        {
            for (size_t j = 0; j < output_size.second; ++j)
            {
                x.at(y_mask.at(i, j), x_mask.at(i, j)) = y.at(i, j);
            }
        }
    }
};
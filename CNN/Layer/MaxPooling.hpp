#include "../Layer.hpp"

class MaxPooling : public Layer
{
    std::pair<size_t, size_t> stride;

    std::vector<Matrix<std::pair<size_t, size_t>>> mask;

    std::pair<size_t, size_t> output_size;

public:
    MaxPooling(const std::pair<size_t, size_t> stride)
        : stride(stride) {}

    Matrix_size initialize(const Matrix_size input_size) override
    {
        Layer::input_size = input_size;

        if (input_size.y % stride.first != 0 or input_size.z % stride.second != 0)
        {
            throw std::invalid_argument("出力サイズが確定できません");
        }

        output_size.first = input_size.y / stride.first;
        output_size.second = input_size.z / stride.second;

        mask = std::vector<Matrix<std::pair<size_t, size_t>>>(input_size.x, Matrix<std::pair<size_t, size_t>>(output_size.first, output_size.second));

        return {input_size.x, output_size.first, output_size.second};
    }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) override
    {
        std::vector<Matrix<double>> y(input_size.x);
        for (size_t i = 0; i < input_size.x; ++i)
        {
            y[i] = forward_pooling(x[i], mask[i]);
        }
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y_gradient) override
    {
        std::vector<Matrix<double>> x_gradient(make_vec_mat(input_size));
        for (size_t i = 0; i < input_size.x; ++i)
        {
            backward_pooling(y_gradient[i], x_gradient[i], mask[i]);
        }
        return x_gradient;
    }

private:
    Matrix<double> forward_pooling(const Matrix<double> &x, Matrix<std::pair<size_t, size_t>> &mask)
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
                        mask.at(i, j).first = col;
                        mask.at(i, j).second = row;
                    }
                }
            }
        }
        return y;
    }

    void backward_pooling(const Matrix<double> &y_gradient, Matrix<double> &x_gradient, const Matrix<std::pair<size_t, size_t>> &mask)
    {
        for (size_t i = 0; i < output_size.first; ++i)
        {
            for (size_t j = 0; j < output_size.second; ++j)
            {
                x_gradient.at(mask.at(i, j).first, mask.at(i, j).second) = y_gradient.at(i, j);
            }
        }
    }
};
#include "../Layer.hpp"

#include <cfloat>

class MaxPooling : public Layer
{
    std::pair<size_t, size_t> stride;

    std::vector<Matrix<size_t>> x_mask;
    std::vector<Matrix<size_t>> y_mask;

public:
    MaxPooling(std::pair<size_t, size_t> stride)
        : stride(stride), Layer({0, 0, 0}) {}

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)
    {
        std::vector<Matrix<double>> y(x.size());
        for (size_t i = 0; i < x.size(); ++i)
        {
            y[i] = forward_pooling(x[i], y_mask[i], x_mask[i]);
        }
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y)
    {
        std::vector<Matrix<double>> x(y.size(), Matrix<double>(y[0].col_size() * stride.first, y[0].row_size() * stride.second));
        for (size_t i = 0; i < y.size(); ++i)
        {
            backward_pooling(y[i], x[i], y_mask[i], x_mask[i]);
        }
        return y;
    }

private:
    Matrix<double> forward_pooling(const Matrix<double> &x, Matrix<size_t> &y_mask, Matrix<size_t> &x_mask)
    {
        Matrix<double> y(x.col_size() / stride.first, x.row_size() / stride.second, -DBL_MAX);
        for (size_t i = 0; i < y.col_size(); ++i)
        {
            for (size_t j = 0; j < y.row_size(); ++j)
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
        for (size_t i = 0; i < y.col_size() / stride.first; ++i)
        {
            for (size_t j = 0; j < y.row_size() / stride.second; ++j)
            {
                x.at(y_mask.at(i, j), x_mask.at(i, j)) = y.at(i, j);
            }
        }
    }
};
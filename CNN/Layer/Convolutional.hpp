//plz be careful
//ミカン

#include "../Layer.hpp"

#include "../Random.hpp"

class Convolution2D : public Layer
{
    class Cell
    {
        std::vector<Matrix<double>> W;
        std::vector<Matrix<double>> W_gradient;

        double B;
        double B_gradient;

        size_t channel;
        std::pair<size_t, size_t> input_size;
        std::pair<size_t, size_t> output_size;
        std::pair<size_t, size_t> padding;
        std::pair<size_t, size_t> stride;

    public:
        Matrix<double> forward(const std::vector<Matrix<double>> &x)
        {
            Matrix<double> y(output_size.first, output_size.second);
            for (size_t i = 0; i < x.size(); ++i)
            {
                y += forward_cell(x[i], W[i]);
            }
            y += B;
            return y;
        }
        std::vector<Matrix<double>> backward(const Matrix<double> &y, const std::vector<Matrix<double>> &x)
        {
            std::vector<Matrix<double>> x_gradient(channel);
            for (size_t i = 0; i < channel; ++i)
            {
                x_gradient[i] = backward_cell(y, W[i], x[i], W_gradient[i]);
            }
            B_gradient += sum(y);
            return x_gradient;
        }

    private:
        // 定義通りに実装
        Matrix<double> forward_cell(const Matrix<double> &x, const Matrix<double> &w)
        {
            Matrix<double> y(output_size.first, output_size.second);
            for (size_t i = 0; i < output_size.first; ++i)
            {
                for (size_t j = 0; j < output_size.second; ++j)
                {
                    for (size_t m = 0; m < w.col_size(); ++m)
                    {
                        for (size_t n = 0; n < w.row_size(); ++n)
                        {
                            size_t col = i * stride.first + m - padding.first;
                            size_t row = j * stride.second + n - padding.second;
                            if (col >= x.col_size() or row >= x.row_size())
                            {
                                continue;
                            }
                            y.at(i, j) += x.at(col, row) * w.at(m, n);
                        }
                    }
                }
            }
            return y;
        }

        Matrix<double> backward_cell(const Matrix<double> &y, const Matrix<double> &x, const Matrix<double> &w, Matrix<double> &w_gradient)
        {
            Matrix<double> x_gradient(input_size.first, input_size.second);
            for (size_t i = 0; i < output_size.first; ++i)
            {
                for (size_t j = 0; j < output_size.second; ++j)
                {
                    for (size_t m = 0; m < w.col_size(); ++m)
                    {
                        for (size_t n = 0; n < w.row_size(); ++n)
                        {
                            size_t col = i * stride.first + m - padding.first;
                            size_t row = j * stride.second + n - padding.second;
                            if (col >= x.col_size() or row >= x.row_size())
                            {
                                continue;
                            }
                            x_gradient.at(col, row) += y.at(i, j) * w.at(m, n);
                            w_gradient.at(m, n) += y.at(i, j) * x.at(col, row);
                        }
                    }
                }
            }
            return x_gradient;
        }
    };
    std::vector<Cell> cell;
    size_t filter;

    std::vector<Matrix<double>> input_cash;

public:
    Convolution2D(const data_size input_size, size_t filter)
        : Layer(input_size), filter(filter), cell(filter)
    {
        for (size_t i = 0; i < filter; ++i)
        {
            cell.emplace_back(cell);
        }
    }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)
    {
        input_cash = x;
        std::vector<Matrix<double>> y(filter);
        for (size_t i = 0; i < filter; ++i)
        {
            y[i] = cell[i].forward(x);
        }
        return y;
    }
    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y)
    {
        std::vector<Matrix<double>> x(input_cash.size());
        for (size_t i = 0; i < y.size(); ++i)
        {
            std::vector<Matrix<double>> temp = cell[i].backward(y[i], input_cash);
            for (size_t j = 0; j < input_cash.size(); j++)
            {
                x[i] += temp[j];
            }
        }
        return x;
    }
};
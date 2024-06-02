#include "../Layer.hpp"

constexpr std::pair<size_t, size_t> PADDING_SAME = {-1, -1};

class Convolution2D : public Layer
{
    class Cell
    {
        // パラメーター
        std::vector<Matrix<double>> W;
        std::vector<Matrix<double>> W_gradient;

        double B;
        double B_gradient;

        // コンフィグ
        Matrix_size input_size;
        std::pair<size_t, size_t> output_size;
        std::pair<size_t, size_t> padding;
        std::pair<size_t, size_t> stride;
        std::pair<size_t, size_t> filter;

    public:
        Cell(const size_t filter_size,
             const Matrix_size input_size,
             const std::pair<size_t, size_t> output_size,
             const std::pair<size_t, size_t> padding,
             const std::pair<size_t, size_t> stride,
             const std::pair<size_t, size_t> filter,
             const Init_type init_type = Xavier)
            : input_size(input_size), output_size(output_size), padding(padding), stride(stride),

              W(input_size.x, Matrix<double>(filter.first, filter.second)),
              W_gradient(input_size.x, Matrix<double>(filter.first, filter.second))
        {
            // ここ用修正
            Random<std::normal_distribution<>> r;
            switch (init_type)
            {
            case Xavier:
                r.set(0.0, 2.0 / double((filter.first * filter.second * (input_size.x + filter_size))));
                break;
            }

            for (auto &i : W)
            {
                for (auto &j : i)
                {
                    j = r();
                }
            }
        }

        Matrix<double> forward(const std::vector<Matrix<double>> &x)
        {
            Matrix<double> y(output_size.first, output_size.second);
            for (size_t i = 0; i < input_size.x; ++i)
            {
                y += forward_cell(x[i], W[i]);
            }
            y += B;
            return y;
        }
        std::vector<Matrix<double>> backward(const Matrix<double> &y_gradient, const std::vector<Matrix<double>> &input_cash)
        {
            std::vector<Matrix<double>> x_gradient(input_size.x);
            for (size_t i = 0; i < input_size.x; ++i)
            {
                x_gradient[i] = backward_cell(y_gradient, W[i], input_cash[i], W_gradient[i]);
            }
            B_gradient += sum(y_gradient);
            return x_gradient;
        }

        void update(const double learning_rate)
        {
            for (size_t i = 0; i < input_size.x; ++i)
            {
                W[i] -= W_gradient[i] * learning_rate;

                for (auto &i : W_gradient[i])
                {
                    i = 0;
                }
            }
            B -= B_gradient * learning_rate;
            B = 0;
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

        Matrix<double> backward_cell(const Matrix<double> y_gradient, const Matrix<double> &input_cash, const Matrix<double> &w, Matrix<double> &w_gradient)
        {
            Matrix<double> x_gradient(input_size.y, input_size.z);
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
                            if (col >= input_cash.col_size() or row >= input_cash.row_size())
                            {
                                continue;
                            }
                            x_gradient.at(col, row) += y_gradient.at(i, j) * w.at(m, n);
                            w_gradient.at(m, n) += y_gradient.at(i, j) * input_cash.at(col, row);
                        }
                    }
                }
            }
            return x_gradient;
        }
    };

    // パラメーター
    std::vector<Cell> cell;

    // キャッシュ
    std::vector<Matrix<double>> input_cash;

    // コンフィグ
    size_t filter_size;
    std::pair<size_t, size_t> output_size;
    std::pair<size_t, size_t> padding;
    std::pair<size_t, size_t> stride;
    std::pair<size_t, size_t> filter;

public:
    Convolution2D(const size_t filter_size,
                  const std::pair<size_t, size_t> padding,
                  const std::pair<size_t, size_t> stride,
                  const std::pair<size_t, size_t> filter)
        : filter_size(filter_size), padding(padding), stride(stride), filter(filter) {}

    Matrix_size initialize(const Matrix_size input_size) override
    {
        Layer::input_size = input_size;

        // 入力サイズと出力サイズ同じにする
        if (padding == PADDING_SAME)
        {
            if ((input_size.y - filter.first - stride.first * input_size.y - stride.first) % 2 != 0 or
                (input_size.z - filter.second - stride.second * input_size.z - stride.second) % 2 != 0)
            {
                throw std::invalid_argument("出力サイズが確定できません");
            }

            output_size.first = input_size.y;
            output_size.second = input_size.z;

            padding.first = input_size.y - filter.first - stride.first * input_size.y - stride.first;
            padding.second = input_size.z - filter.second - stride.second * input_size.z - stride.second;
        }
        else
        {
            if ((input_size.y + 2 * padding.first - filter.first) % stride.first != 0 or
                (input_size.z + 2 * padding.second - filter.second) % stride.second != 0)
            {
                throw std::invalid_argument("出力サイズが確定できません");
            }
            output_size.first = (input_size.y + 2 * padding.first - filter.first) / stride.first + 1;
            output_size.second = (input_size.z + 2 * padding.second - filter.second) / stride.second + 1;
        }

        cell = std::vector<Cell>(filter_size, Cell(filter_size, input_size, output_size, padding, stride, filter));

        return {filter_size, output_size.first, output_size.second};
    }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) override
    {
        input_cash = x;
        std::vector<Matrix<double>> y(filter_size);
        for (size_t i = 0; i < filter_size; ++i)
        {
            y[i] = cell[i].forward(x);
        }
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y_gradient) override
    {
        std::vector<Matrix<double>> x_gradient(make_vec_mat(input_size));
        for (size_t i = 0; i < input_size.x; ++i)
        {
            std::vector<Matrix<double>> temp = cell[i].backward(y_gradient[i], input_cash);
            for (size_t j = 0; j < input_size.x; j++)
            {
                x_gradient[i] += temp[j];
            }
        }
        return x_gradient;
    }

    void update(const double learning_rate) override
    {
        for (auto &i : cell)
        {
            i.update(learning_rate);
        }
    };
};
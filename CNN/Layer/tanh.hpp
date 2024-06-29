#include "../Layer.hpp"

class Tanh : public Layer
{
    std::vector<Matrix<double>> output_cash;

public:
    Matrix_size initialize(const Matrix_size input_size) override
    {
        Layer::input_size = input_size;
        return input_size;
    }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) override
    {
        std::vector<Matrix<double>> y(x);
        for (auto &i : y)
        {
            i = tanh(i);
        }
        output_cash = y;
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y_gradient) override
    {
        std::vector<Matrix<double>> x_gradient(make_vec_mat(input_size));
        for (size_t i = 0; i < input_size.x; ++i)
        {
            x_gradient[i] = y_gradient[i] * (1.0 - output_cash[i] * output_cash[i]);
        }
        return x_gradient;
    }
};
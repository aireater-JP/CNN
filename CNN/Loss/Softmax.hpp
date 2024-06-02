#pragma once
#include "../Loss.hpp"

class Softmax_with_Loss : public Loss
{
    std::vector<Matrix<double>> Softmax_output_cash;
    std::vector<Matrix<double>> teacher_cash;

public:
    double forward(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &teacher) override
    {
        teacher_cash = teacher;
        Softmax_output_cash = Softmax(x);

        return cross_entropy_error(Softmax_output_cash, teacher);
    }

    std::vector<Matrix<double>> backward() override
    {
        std::vector<Matrix<double>> x_gradient(Softmax_output_cash);
        for (size_t i = 0; i < input_size.x; ++i)
        {
            x_gradient[i] -= teacher_cash[i];
        }

        return x_gradient;
    }

private:
    std::vector<Matrix<double>> Softmax(const std::vector<Matrix<double>> &x)
    {
        std::vector<Matrix<double>> y(make_vec_mat(input_size));

        for (size_t i = 0; i < x.size(); ++i)
        {
            Matrix<double> exp_temp = exp(x[i] - max_col(x[i]));
            y[i] = exp_temp / sum_col(exp_temp);
        }

        return y;
    }

    double cross_entropy_error(const std::vector<Matrix<double>> &x_gradient, const std::vector<Matrix<double>> &teacher)
    {
        double y_gradient = 0;
        for (size_t i = 0; i < input_size.x; ++i)
        {
            y_gradient += sum(teacher[i] * log(x_gradient[i] + DBL_MIN));
        }

        return -y_gradient / (input_size.x * input_size.y);
    }
};
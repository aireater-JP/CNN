#pragma once
#include "../Loss.hpp"

class Softmax_with_Loss : public Loss
{
    std::vector<Matrix<double>> output_cash;
    std::vector<Matrix<double>> teacher_cash;

public:
    double forward(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &teacher) override
    {
        teacher_cash = teacher;
        output_cash = Softmax(x);
        return cross_entropy_error(output_cash, teacher_cash);
    }

    std::vector<Matrix<double>> backward() override
    {
        std::vector<Matrix<double>> x(output_cash);
        for (size_t i = 0; i < x.size(); ++i)
        {
            x[i] -= teacher_cash[i];
        }
        return x;
    }

private:
    std::vector<Matrix<double>> Softmax(const std::vector<Matrix<double>> &x)
    {
        std::vector<Matrix<double>> y(make_vec_mat(x));

        for (size_t i = 0; i < x.size(); ++i)
        {
            Matrix<double> exp_temp = exp(x[i] - max_col(x[i]));
            y[i] = exp_temp / sum_col(exp_temp);
        }

        return y;
    }

    double cross_entropy_error(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &teacher)
    {
        double y = 0;
        for (size_t i = 0; i < x.size(); ++i)
        {
            y += sum(teacher[i] * log(x[i] + DBL_MIN));
        }

        return -y / (x.size() * x[0].col_size());
    }
};
#pragma once
#include "../Loss.hpp"

class Identity_with_Loss : public Loss
{
    std::vector<Matrix<double>> Identity_output_cash;
    std::vector<Matrix<double>> teacher_cash;

public:
    double forward(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &teacher) override
    {
        teacher_cash = teacher;
        Identity_output_cash = x;
        return sum_of_squared_error(x, teacher);
    }

    std::vector<Matrix<double>> backward() override
    {
        std::vector<Matrix<double>> x_gradient(Identity_output_cash);
        for (size_t i = 0; i < input_size.x; ++i)
        {
            x_gradient[i] -= teacher_cash[i];
        }
        return x_gradient;
    }

private:
    double sum_of_squared_error(const std::vector<Matrix<double>> &x_gradient, const std::vector<Matrix<double>> &teacher)
    {
        double y_gradient = 0;
        for (size_t i = 0; i < input_size.x; ++i)
        {
            Matrix<double> temp = x_gradient[i] - teacher[i];
            y_gradient += sum(temp * temp);
        }

        return (y_gradient * 0.5) / (input_size.x * input_size.y);
    }
};
#include "../Loss.hpp"

#include <algorithm>
#include <cmath>
#include <cfloat>

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
            for (size_t j = 0; j < x[i].col_size(); ++j)
            {
                for (size_t k = 0; k < x[i].row_size(); ++k)
                {
                    x[i].at(j, k) -= teacher_cash[i].at(j, k);
                }
            }
        }
        return x;
    }

private:
    std::vector<Matrix<double>> Softmax(const std::vector<Matrix<double>> &x)
    {
        std::vector<Matrix<double>> y(make_vec_mat(x));

        for (size_t i = 0; i < x.size(); ++i)
        {
            double C = *std::max_element(x[i].begin(), x[i].end());

            for (size_t j = 0; j < x[i].col_size(); ++j)
            {
                double sum = 0;
                for (size_t k = 0; k < x[i].row_size(); ++k)
                {
                    double exp_x = std::exp(x[i].at(j, k) - C);

                    y[i].at(j, k) = exp_x;
                    sum += exp_x;
                }

                for (size_t k = 0; k < x[i].row_size(); ++k)
                {
                    y[i].at(j, k) /= sum;
                }
            }
        }

        return y;
    }

    double cross_entropy_error(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &teacher)
    {
        double y = 0;
        for (size_t i = 0; i < x.size(); ++i)
        {
            for (size_t j = 0; j < x[i].col_size(); ++j)
            {
                for (size_t k = 0; k < x[i].row_size(); ++k)
                {
                    y += teacher[i].at(j, k) * std::log(x[i].at(j, k) + DBL_MIN);
                }
            }
        }

        return -y;
    }
};
#include "../Layer.hpp"

class ReLU : public Layer
{
    std::vector<Matrix<double>> mask;

public:
    ReLU(const data_size input_size)
        : Layer(input_size) {}

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)
    {
        mask = x;
        std::vector<Matrix<double>> y(make_vec_mat(x));

        for (size_t i = 0; i < x.size(); ++i)
        {
            for (size_t j = 0; j < x[i].col_size(); ++j)
            {
                for (size_t k = 0; k < x[i].row_size(); ++k)
                {
                    y[i].at(j, k) = std::max(0.0, x[i].at(j, k));
                }
            }
        }
        return y;
    }

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y)
    {
        std::vector<Matrix<double>> x(make_vec_mat(y));

        for (size_t i = 0; i < y.size(); ++i)
        {
            for (size_t j = 0; j < y[i].col_size(); ++j)
            {
                for (size_t k = 0; k < y[i].row_size(); ++k)
                {
                    x[i].at(j, k) = y[i].at(j, k) * (mask[i].at(j, k) > 0.0);
                }
            }
        }
        return x;
    }
};
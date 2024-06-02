#include "../Layer.hpp"

class ReLU : public Layer
{
    std::vector<Matrix<double>> mask;

    Matrix_size input_size;

public:
    ReLU() {}

    void set_input_size(Matrix_size input_size) override { input_size = input_size; }
    Matrix_size get_output_size() override { return input_size; }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)
    {
        mask = x;
        std::vector<Matrix<double>> y(make_vec_mat(x));

        for (size_t i = 0; i < input_size.x; ++i)
        {
            for (size_t j = 0; j < input_size.y; ++j)
            {
                for (size_t k = 0; k < input_size.z; ++k)
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

        for (size_t i = 0; i < input_size.x; ++i)
        {
            for (size_t j = 0; j < input_size.y; ++j)
            {
                for (size_t k = 0; k < input_size.z; ++k)
                {
                    x[i].at(j, k) = y[i].at(j, k) * (mask[i].at(j, k) > 0.0);
                }
            }
        }
        return x;
    }
};
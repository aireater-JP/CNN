#include "../Layer.hpp"

class ReLU : public Layer
{
    std::vector<Matrix<double>> input_cash;

public:
    ReLU() {}

    void set_input_size(const Matrix_size input_size) override { Layer::input_size = input_size; }
    Matrix_size get_output_size() override { return input_size; }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) override
    {
        input_cash = x;
        std::vector<Matrix<double>> y(make_vec_mat(input_size));

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

    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y_gradient) override
    {
        std::vector<Matrix<double>> x_gradient(make_vec_mat(input_size));

        for (size_t i = 0; i < input_size.x; ++i)
        {
            for (size_t j = 0; j < input_size.y; ++j)
            {
                for (size_t k = 0; k < input_size.z; ++k)
                {
                    x_gradient[i].at(j, k) = y_gradient[i].at(j, k) * (input_cash[i].at(j, k) > 0.0);
                }
            }
        }
        return x_gradient;
    }
};
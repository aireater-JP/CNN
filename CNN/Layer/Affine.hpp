#include "../Layer.hpp"

class Affine : public Layer
{
    Matrix<double> W;
    Matrix<double> W_gradient;

    std::valarray<double> B;
    std::valarray<double> B_gradient;

    std::vector<Matrix<double>> input_cache;

public:
    Affine(const data_size input_size, const init_type type)
        : Layer(input_size),
          W(input_size.y, input_size.z), W_gradient(input_size.y, input_size.z),
          B(input_size.z), B_gradient(input_size.z)
    {
        Random<std::normal_distribution<>> r;

        if (type == Xavier)
        {
            r.set(0.0, 1.0 / std::sqrt(input_size.z));
        }
        if (type == He)
        {
            r.set(0.0, std::sqrt(2.0 / input_size.z));
        }

        for (auto &i : W)
        {
            i = r();
        }
    }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)
    {
        input_cache = x;

        std::vector<Matrix<double>> y(x.size());

        for (size_t i = 0; i < y.size(); ++i)
        {
            y[i] = add_mat_colvec(dot(x[i], W), B);
        }
        return y;
    }
    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y)
    {
        std::vector<Matrix<double>> x(y.size());
        Matrix<double> W_transposed = W.transpose();

        for (size_t i = 0; i < x.size(); ++i)
        {
            x[i] = dot(y[i], W_transposed);
            W_gradient += dot(input_cache[i].transpose(), y[i]);
            B_gradient += sum_col(y[i]);
        }
        return x;
    }
};
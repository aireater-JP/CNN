#include "../Layer.hpp"

class Affine : public Layer
{
    // パタメーター
    Matrix<double> W;
    Matrix<double> W_gradient;

    row_valarray<double> B;
    row_valarray<double> B_gradient;

    // キャッシュ
    std::vector<Matrix<double>> input_cache;

    // コンフィグ
    size_t output_size;
    Init_type init_type;

public:
    Affine(const size_t output_size, const Init_type init_type = He)
        : output_size(output_size), init_type(init_type) {}

    Matrix_size initialize(const Matrix_size input_size) override
    {
        Layer::input_size = input_size;
        W = Matrix<double>(input_size.z, output_size);
        W_gradient = Matrix<double>(input_size.z, output_size);

        B = row_valarray<double>(output_size);
        B_gradient = row_valarray<double>(output_size);

        // 初期化しますぜ
        Random<std::normal_distribution<>> r;

        switch (init_type)
        {
        case Xavier:
            r.set(0.0, 1.0 / std::sqrt(input_size.y));
            break;

        case He:
            r.set(0.0, std::sqrt(2.0 / input_size.z));
            break;
        }

        for (auto &i : W)
        {
            i = r();
        }

        return {input_size.x, input_size.y, output_size};
    }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) override
    {
        input_cache = x;

        std::vector<Matrix<double>> y(input_size.x);

        for (size_t i = 0; i < input_size.x; ++i)
        {
            y[i] = dot(x[i], W) + B;
        }

        return y;
    }
    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y_gradient) override
    {
        std::vector<Matrix<double>> x_gradient(input_size.x);
        Matrix<double> W_transposed = W.transpose();

        for (size_t i = 0; i < input_size.x; ++i)
        {
            x_gradient[i] = dot(y_gradient[i], W_transposed);
            W_gradient += dot(input_cache[i].transpose(), y_gradient[i]);
            B_gradient += sum_row(y_gradient[i]);
        }

        return x_gradient;
    }

    void update(const double learning_rate)
    {
        W -= W_gradient * learning_rate;
        for (auto &i : W_gradient)
        {
            i = 0;
        }
        B -= B_gradient * learning_rate;
        for (auto &i : B_gradient)
        {
            i = 0;
        }
    };
};
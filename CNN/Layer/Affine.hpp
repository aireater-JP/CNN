#include "../Layer.hpp"

#include "../Random.hpp"

class Affine : public Layer
{
    // パタメーター
    Matrix<double> W;
    Matrix<double> W_gradient;

    std::valarray<double> B;
    std::valarray<double> B_gradient;

    // キャッシュ
    std::vector<Matrix<double>> input_cache;

    // コンフィグ
    Matrix_size input_size;
    size_t output_size;
    Init_type init_type;

public:
    Affine(size_t output_sizes, const Init_type init_type = He)
        : output_size(output_size), init_type(init_type) {}

    void set_input_size(Matrix_size input_size) override
    {
        input_size = input_size;
        W = Matrix<double>(input_size.z, output_size);
        W_gradient = Matrix<double>(input_size.z, output_size);

        B = std::valarray<double>(output_size);
        B_gradient = std::valarray<double>(output_size);

        // 初期化しますぜ
        Random<std::normal_distribution<>> r;

        switch (init_type)
        {
        case Xavier:
            r.set(0.0, 1.0 / std::sqrt(input_size.z));
            break;

        case He:
            r.set(0.0, std::sqrt(2.0 / input_size.z));
            break;
        }

        for (auto &i : W)
        {
            i = r();
        }
    }

    Matrix_size get_output_size() override { return {input_size.x, input_size.y, output_size}; }

    std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x)override
    {
        input_cache = x;

        std::vector<Matrix<double>> y(input_size.x);

        for (size_t i = 0; i < input_size.x; ++i)
        {
            y[i] = dot(x[i], W) + B;
        }
        return y;
    }
    std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y_gradient)override
    {
        std::vector<Matrix<double>> x_gradient(input_size.x);
        Matrix<double> W_transposed = W.transpose();

        for (size_t i = 0; i < input_size.x; ++i)
        {
            x_gradient[i] = dot(y_gradient[i], W_transposed);
            W_gradient += dot(input_cache[i].transpose(), y_gradient[i]);
            B_gradient += sum_col(y_gradient[i]);
        }
        return x_gradient;
    }
};
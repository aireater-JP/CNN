#include "Matrix.hpp"

#include <valarray>

#include "Random.hpp"

// 初期化を簡単にするぞ
std::vector<Matrix<double>> make_vec_mat(const std::vector<Matrix<double>> &x)
{
    return std::vector<Matrix<double>>(x.size(), Matrix<double>(x[0].col_size(), x[0].row_size()));
}

// 行列と列ベクトル足し算
Matrix<double> add_mat_colvec(const Matrix<double> &mat, const std::valarray<double> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("the number of columns in the mat and the size of the vec don't match");
    }

    Matrix<double> result(mat.col_size(), mat.row_size());

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) = mat.at(i, j) + vec[i];
        }
    }
    return result;
}

// 列個のベクトルを返す
std::valarray<double> sum_col(const Matrix<double> &x)
{
    std::valarray<double> y(x.col_size());

    for (size_t i = 0; i < x.col_size(); ++i)
    {
        for (size_t j = 0; j < x.row_size(); ++j)
        {
            y[i] = x.at(i, j);
        }
    }
    return y;
}
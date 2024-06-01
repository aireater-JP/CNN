#pragma once

////////////////////////////////////////////////////////////////
// valarray
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> operator+(const Matrix<T> &mat, const std::valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
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

template <typename T>
Matrix<T> operator-(const Matrix<T> &mat, const std::valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<double> result(mat.col_size(), mat.row_size());

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) = mat.at(i, j) - vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator/(const Matrix<T> &mat, const std::valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<double> result(mat.col_size(), mat.row_size());

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) = mat.at(i, j) / vec[i];
        }
    }
    return result;
}
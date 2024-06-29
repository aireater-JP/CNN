#include "Matrix.hpp"
#pragma once

////////////////////////////////////////////////////////////////
// 演算系
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> exp(const Matrix<T> &x)
{
    Matrix<T> y(x);
    y.data = exp(y.data);
    return y;
}

template <typename T>
Matrix<T> log(const Matrix<T> &x)
{
    Matrix<T> y(x);
    y.data = log(y.data);
    return y;
}

template <typename T>
Matrix<T> tanh(const Matrix<T> &x)
{
    Matrix<T> y(x);
    y.data = tanh(y.data);
    return y;
}

template <typename U>
Matrix<U> pow(const Matrix<U> &x, const U y)
{
    Matrix<U> res(x);
    res.data = pow(res.data, y);
    return res;
}

////////////////////////////////////////////////////////////////
// 便利系
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix transposed(row, col);

    for (size_t i = 0; i < col; ++i)
    {
        for (size_t j = 0; j < row; ++j)
        {
            transposed.at(j, i) = at(i, j);
        }
    }
    return transposed;
}

template <typename T>
T sum(const Matrix<T> &x)
{
    return x.data.sum();
}

template <typename T>
col_valarray<T> sum_col(const Matrix<T> &x)
{
    col_valarray<double> y(x.col_size());

    for (size_t i = 0; i < x.col_size(); ++i)
    {
        for (size_t j = 0; j < x.row_size(); ++j)
        {
            y[i] += x.at(i, j);
        }
    }
    return y;
}

template <typename T>
row_valarray<T> sum_row(const Matrix<T> &x)
{
    row_valarray<double> y(x.row_size());

    for (size_t i = 0; i < x.col_size(); ++i)
    {
        for (size_t j = 0; j < x.row_size(); ++j)
        {
            y[j] += x.at(i, j);
        }
    }
    return y;
}

template <typename T>
col_valarray<T> max_col(const Matrix<T> &x)
{
    col_valarray<double> y(-DBL_MAX, x.col_size());

    for (size_t i = 0; i < x.col_size(); ++i)
    {
        for (size_t j = 0; j < x.row_size(); ++j)
        {
            y[i] = std::max(y[i], x.at(i, j));
        }
    }
    return y;
}

////////////////////////////////////////////////////////////////
// 基礎系
////////////////////////////////////////////////////////////////

// コピー代入演算子
template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &other)
{
    if (this != &other)
    {
        col = other.col;
        row = other.row;
        data = other.data;
    }
    return *this;
}
// ムーブ代入演算子
template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept
{
    if (this != &other)
    {
        col = other.col;
        row = other.row;
        data = std::move(other.data);

        other.col = 0;
        other.row = 0;
    }
    return *this;
}
// コピー代入演算子
template <typename T>
Matrix<T> &Matrix<T>::operator=(const T &value)
{
    for (auto &i : *this)
    {
        i = value;
    }
    return *this;
}

// 要素アクセス
template <typename T>
T &Matrix<T>::at(size_t i, size_t j)
{
    if (i >= col || j >= row)
    {
        throw std::out_of_range("範囲外アクセスだよ！");
    }
    return data[i * row + j];
}
template <typename T>
const T &Matrix<T>::at(size_t i, size_t j) const
{
    if (i >= col || j >= row)
    {
        throw std::out_of_range("範囲外アクセスだよ！");
    }
    return data[i * row + j];
}
template <typename T>
T &Matrix<T>::at(size_t i)
{
    if (i >= data.size())
    {
        throw std::out_of_range("範囲外アクセスだよ！");
    }
    return data[i];
}
template <typename T>
const T &Matrix<T>::at(size_t i) const
{
    if (i >= data.size())
    {
        throw std::out_of_range("範囲外アクセスだよ！");
    }
    return data[i];
}

// コンストラクタ
template <typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept
    : col(other.col), row(other.row), data(std::move(other.data))
{
    other.col = 0;
    other.row = 0;
}
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init)
    : col(init.size()), row(init.begin()->size())
{
    data.resize(col * row);

    size_t count = 0;
    for (const auto &row : init)
    {
        for (const auto &col : row)
        {
            data[count] = col;
            count++;
        }
    }
}

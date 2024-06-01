////////////////////////////////////////////////////////////////
// 行列
// ver 0.0.1 prototype
// by Aireater
#pragma once

#include <valarray>
#include <stdexcept>
#include <cmath>
#include <cfloat>

template <typename T>
class Matrix
{
    std::vector<T> data;
    size_t col;
    size_t row;

public:
    ////////////////////////////////////////////////////////////////
    // コンストラクタ
    Matrix()
        : col(0), row(0), data() {}
    Matrix(size_t col, size_t row)
        : col(col), row(row), data(col * row) {}
    Matrix(size_t col, size_t row, const T &value)
        : col(col), row(row), data(col * row, value) {}
    Matrix(const Matrix &other)
        : col(other.col), row(other.row), data(other.data) {}
    Matrix(Matrix &&other) noexcept;
    Matrix(std::initializer_list<std::initializer_list<T>> init);

    ////////////////////////////////////////////////////////////////
    // 代入演算子
    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;

    ////////////////////////////////////////////////////////////////
    // 要素アクセス
    T &at(size_t i, size_t j);
    const T &at(size_t i, size_t j) const;
    T &at(size_t i);
    const T &at(size_t i) const;

    ////////////////////////////////////////////////////////////////
    // 要素数
    constexpr size_t col_size() const { return col; }
    constexpr size_t row_size() const { return row; }
    constexpr size_t size() const { return data.size(); }

    ////////////////////////////////////////////////////////////////
    // イテレータ
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

    ////////////////////////////////////////////////////////////////
    // 演算系
    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &a, const Matrix<U> &b);
    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &a, const U &b);
    Matrix &operator+=(const Matrix &other);
    Matrix &operator+=(const T &other);

    template <typename T_>
    friend Matrix<T_> operator-(const Matrix<T_> &a, const Matrix<T_> &b);
    Matrix &operator-=(const Matrix &other);

    template <typename T_>
    friend Matrix<T_> operator*(const Matrix<T_> &a, const Matrix<T_> &b);
    Matrix &operator*=(const Matrix &other);

    template <typename U>
    friend Matrix<U> exp(const Matrix<U> &x);
    template <typename U>
    friend Matrix<U> log(const Matrix<U> &x);

    ////////////////////////////////////////////////////////////////
    // 便利系
    // 転置
    Matrix transpose() const;

    // 合計
    template <typename U>
    friend U sum(const Matrix<U> &x);
    template <typename U>
    friend std::valarray<U> sum_col(const Matrix<U> &x);

    // 最大値
    template <typename U>
    friend std::valarray<U> max_col(const Matrix<U> &x);

    ////////////////////////////////////////////////////////////////
    // valarray
    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &mat, const std::valarray<U> &vec);
    template <typename U>
    friend Matrix<U> operator-(const Matrix<U> &mat, const std::valarray<U> &vec);
    template <typename U>
    friend Matrix<U> operator/(const Matrix<U> &mat, const std::valarray<U> &vec);
};

// ドット積
template <typename T>
Matrix<T> dot(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.row_size() != b.col_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col_size(), b.row_size());

    for (size_t i = 0; i < a.col_size(); ++i)
    {
        for (size_t j = 0; j < b.row_size(); ++j)
        {
            T sum = 0;
            for (size_t k = 0; k < a.row_size(); ++k)
            {
                sum += a.at(i, k) * b.at(k, j);
            }
            c.at(i, j) = sum;
        }
    }
    return c;
}

// 初期化を簡単にするぞ
std::vector<Matrix<double>> make_vec_mat(const std::vector<Matrix<double>> &x)
{
    return std::vector<Matrix<double>>(x.size(), Matrix<double>(x[0].col_size(), x[0].row_size()));
}

#include "Matrix_sub.hpp"
#include "Matrix_valarray.hpp"
////////////////////////////////////////////////////////////////
// 行列
// ver 0.1.0
// by Aireater
#pragma once

#include <valarray>
#include <stdexcept>
#include <cmath>
#include <cfloat>

template <typename T>
class col_valarray : public std::valarray<T>
{
    using std::valarray<T>::valarray;
};

template <typename T>
class row_valarray : public std::valarray<T>
{
    using std::valarray<T>::valarray;
};

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

    template <typename U>
    friend Matrix<U> operator-(const Matrix<U> &a, const Matrix<U> &b);
    Matrix &operator-=(const Matrix &other);

    template <typename U>
    friend Matrix<U> operator*(const Matrix<U> &a, const Matrix<U> &b);
    template <typename U>
    friend Matrix<U> operator*(const Matrix<U> &a, const U &b);
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
    friend col_valarray<U> sum_col(const Matrix<U> &x);
    template <typename U>
    friend row_valarray<U> sum_row(const Matrix<U> &x);
    // 最大値
    template <typename U>
    friend col_valarray<U> max_col(const Matrix<U> &x);

    ////////////////////////////////////////////////////////////////
    // valarray
    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &mat, const col_valarray<U> &vec);
    template <typename U>
    friend Matrix<U> operator-(const Matrix<U> &mat, const col_valarray<U> &vec);
    template <typename U>
    friend Matrix<U> operator/(const Matrix<U> &mat, const col_valarray<U> &vec);

    template <typename U>
    friend Matrix<U> operator+(const Matrix<U> &mat, const row_valarray<U> &vec);
    template <typename U>
    friend Matrix<U> operator-(const Matrix<U> &mat, const row_valarray<U> &vec);
    template <typename U>
    friend Matrix<U> operator/(const Matrix<U> &mat, const row_valarray<U> &vec);
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

// 出力関数
template <typename T>
inline void out(const Matrix<T> &x)
{
    std::cout << "[";
    for (size_t i = 0; i < x.col_size(); ++i)
    {
        if (i != 0)
        {
            std::cout << " ";
        }
        std::cout << "[";

        for (size_t j = 0; j < x.row_size(); ++j)
        {
            std::cout << x.at(i, j);

            if (j != x.row_size() - 1)
            {
                std::cout << ",";
            }
        }
        std::cout << "]";
        if (i != x.col_size() - 1)
        {
            std::cout << "\n";
        }
    }
    std::cout << "]\n";
}

#include "Matrix_sub.hpp"
#include "Matrix_valarray.hpp"
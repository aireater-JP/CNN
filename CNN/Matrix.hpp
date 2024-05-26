#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Matrix
{
    std::vector<T> data;
    size_t col;
    size_t row;

public:
    // コンストラクタ
    Matrix()
        : col(0), row(0), data() {}
    Matrix(size_t col, size_t row)
        : col(col), row(row), data(col * row) {}
    Matrix(size_t col, size_t row, const T &value)
        : col(col), row(row), data(col * row, value) {}

    // コピーコンストラクタ
    Matrix(const Matrix &other)
        : col(other.col), row(other.row), data(other.data) {}
    // ムーブコンストラクタ
    Matrix(Matrix &&other) noexcept
        : col(other.col), row(other.row), data(std::move(other.data))
    {
        other.col = 0;
        other.row = 0;
    }

    // コピー代入演算子
    Matrix &operator=(const Matrix &other)
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
    Matrix &operator=(Matrix &&other) noexcept
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

    // 要素アクセス
    T &at(size_t i, size_t j)
    {
        if (i >= col || j >= row)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[i * row + j];
    }
    const T &at(size_t i, size_t j) const
    {
        if (i >= col || j >= row)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[i * row + j];
    }

    // 列
    constexpr size_t col_size() const { return col; }
    // 行
    constexpr size_t row_size() const { return row; }

    // イテレータ

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

    // 転置
    Matrix transpose() const
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

    friend Matrix operator+(const Matrix &a, const Matrix &b)
    {
        if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
        {
            throw std::invalid_argument("Matrix dimensions must be the same for addition");
        }

        Matrix c(a.row, b.col);

        for (size_t i = 0; i < a.data.size(); ++i)
        {
            c.data[i] = a.data[i] + b.data[i];
        }
        return c;
    }

    Matrix &operator+=(const Matrix &other)
    {
        if (col != other.col || row != other.row)
        {
            throw std::invalid_argument("Matrix dimensions must be the same for addition");
        }

        *this = *this + other;
        return *this;
    }
};

// ドット積
template <typename T>
Matrix<T> dot(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.row_size() != b.col_size())
    {
        throw std::invalid_argument("Incompatible dimensions for matrix dot product");
    }

    Matrix<T> c(a.col_size(), b.row_size());

    for (size_t i = 0; i < a.col_size(); ++i)
    {
        for (size_t j = 0; j < b.row_size(); ++j)
        {
            int sum = 0;
            for (size_t k = 0; k < a.row_size(); ++k)
            {
                sum += a.at(i, k) * b.at(k, j);
            }
            c.at(i, j) = sum;
        }
    }
    return c;
}
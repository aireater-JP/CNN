#pragma once

////////////////////////////////////////////////////////////////
// 演算系
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, b.row);

    for (size_t i = 0; i < a.data.size(); ++i)
    {
        c.data[i] = a.data[i] + b.data[i];
    }
    return c;
}

template <typename U>
Matrix<U> operator+(const Matrix<U> &a, const U &b)
{
    Matrix<U> c(a);

    for (auto &i : c)
    {
        i += b;
    }
    return c;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &other)
{
    *this = *this + other;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const T &other)
{
    *this = *this + other;
    return *this;
}

template <typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, a.row);

    for (size_t i = 0; i < a.data.size(); ++i)
    {
        c.data[i] = a.data[i] - b.data[i];
    }
    return c;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &other)
{
    *this = *this - other;
    return *this;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, a.row);

    for (size_t i = 0; i < a.data.size(); ++i)
    {
        c.data[i] = a.data[i] * b.data[i];
    }
    return c;
}

template <typename U>
Matrix<U> operator*(const Matrix<U> &a, const U &b)
{
    Matrix<U> c(a);

    for (auto &i : c)
    {
        i *= b;
    }
    return c;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix &other)
{
    *this = *this * other;
    return *this;
}

template <typename T>
Matrix<T> exp(const Matrix<T> &x)
{
    Matrix<T> y(x);
    for (auto &i : y)
    {
        i = std::exp(i);
    }
    return y;
}

template <typename T>
Matrix<T> log(const Matrix<T> &x)
{
    Matrix<T> y(x);
    for (auto &i : y)
    {
        i = std::log(i);
    }
    return y;
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
    T y = 0;
    
    for (auto &i : x.data)
    {
        y += i;
    }
    return y;
}

template <typename T>
std::valarray<T> sum_col(const Matrix<T> &x)
{
    std::valarray<double> y(x.col_size());

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
std::valarray<T> max_col(const Matrix<T> &x)
{
    std::valarray<double> y(-DBL_MAX, x.col_size());

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
    data.reserve(col * row);

    for (const auto &row : init)
    {
        data.insert(data.end(), row.begin(), row.end());
    }
}
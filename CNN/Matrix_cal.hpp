#pragma once

////////////////////////////////////////////////////////////////
// 足し算
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, b.row);

    for (size_t i = 0; i < c.data.size(); ++i)
    {
        c.data[i] = a.data[i] + b.data[i];
    }
    return c;
}

template <typename U>
Matrix<U> operator+(const Matrix<U> &a, const U &b)
{
    Matrix<U> c(a.col, a.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a.data[i] + b;
    }
    return c;
}

template <typename U>
Matrix<U> operator+(const U &a, const Matrix<U> &b)
{
    Matrix<U> c(b.col, b.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a + b.data[i];
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

////////////////////////////////////////////////////////////////
// 引き算
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, b.row);

    for (size_t i = 0; i < c.data.size(); ++i)
    {
        c.data[i] = a.data[i] - b.data[i];
    }
    return c;
}

template <typename U>
Matrix<U> operator-(const Matrix<U> &a, const U &b)
{
    Matrix<U> c(a.col, a.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a.data[i] - b;
    }
    return c;
}

template <typename U>
Matrix<U> operator-(const U &a, const Matrix<U> &b)
{
    Matrix<U> c(b.col, b.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a - b.data[i];
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
Matrix<T> &Matrix<T>::operator-=(const T &other)
{
    *this = *this - other;
    return *this;
}

////////////////////////////////////////////////////////////////
// 掛け算
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, b.row);

    for (size_t i = 0; i < c.data.size(); ++i)
    {
        c.data[i] = a.data[i] * b.data[i];
    }
    return c;
}

template <typename U>
Matrix<U> operator*(const Matrix<U> &a, const U &b)
{
    Matrix<U> c(a.col, a.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a.data[i] * b;
    }
    return c;
}

template <typename U>
Matrix<U> operator*(const U &a, const Matrix<U> &b)
{
    Matrix<U> c(b.col, b.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a * b.data[i];
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
Matrix<T> &Matrix<T>::operator*=(const T &other)
{
    *this = *this * other;
    return *this;
}

////////////////////////////////////////////////////////////////
// 割り算
////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> operator/(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    Matrix<T> c(a.col, b.row);

    for (size_t i = 0; i < c.data.size(); ++i)
    {
        c.data[i] = a.data[i] / b.data[i];
    }
    return c;
}

template <typename U>
Matrix<U> operator/(const Matrix<U> &a, const U &b)
{
    Matrix<U> c(a.col, a.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a.data[i] / b;
    }
    return c;
}

template <typename U>
Matrix<U> operator/(const U &a, const Matrix<U> &b)
{
    Matrix<U> c(b.col, b.row);

    for (size_t i = 0; i < c.size(); ++i)
    {
        c.data[i] = a / b.data[i];
    }
    return c;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const Matrix &other)
{
    *this = *this / other;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const T &other)
{
    *this = *this / other;
    return *this;
}
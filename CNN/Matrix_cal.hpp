////////////////////////////////////////////////////////////////
// 行列の四則演算
#pragma once

////////////////////////////////////////////////////////////////
// 足し算
template <typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    auto c = a;
    c.data += b.data;

    return c;
}

template <typename U>
Matrix<U> operator+(const Matrix<U> &a, const U &b)
{
    auto c = a;
    c.data += b;

    return c;
}

template <typename U>
Matrix<U> operator+(const U &a, const Matrix<U> &b)
{
    auto c = b;
    c.data += a;

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
template <typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    auto c = a;
    c.data -= b.data;

    return c;
}

template <typename U>
Matrix<U> operator-(const Matrix<U> &a, const U &b)
{
    auto c = a;
    c.data -= b;

    return c;
}

template <typename U>
Matrix<U> operator-(const U &a, const Matrix<U> &b)
{
    auto c = -b;
    c.data += a;

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
template <typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    auto c = a;
    c.data *= b.data;

    return c;
}

template <typename U>
Matrix<U> operator*(const Matrix<U> &a, const U &b)
{
    auto c = a;
    c.data *= b;

    return c;
}

template <typename U>
Matrix<U> operator*(const U &a, const Matrix<U> &b)
{
    auto c = b;
    c.data *= a;

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
template <typename T>
Matrix<T> operator/(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.col_size() != b.col_size() || a.row_size() != b.row_size())
    {
        throw std::invalid_argument("この行列同士だと計算できないよ！");
    }

    auto c = a;
    c.data /= b.data;

    return c;
}

template <typename U>
Matrix<U> operator/(const Matrix<U> &a, const U &b)
{
    auto c = a;
    c.data /= b;

    return c;
}

//--------------------------------------------------------------
// 最適化ポイント
template <typename U>
Matrix<U> operator/(const U &a, const Matrix<U> &b)
{
    Matrix<U> c(b.col, b.row, a);
    c.data /= b.data;

    return c;
}
//--------------------------------------------------------------

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

////////////////////////////////////////////////////////////////
// 単項
template <typename T>
Matrix<T> Matrix<T>::operator+()const
{
    Matrix<T> y(col, row);
    y.data = +(this->data);

    return y;
}

template <typename T>
Matrix<T> Matrix<T>::operator-()const
{
    Matrix<T> y(col, row);
    y.data = -(this->data);

    return y;
}
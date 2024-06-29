////////////////////////////////////////////////////////////////
// 列ベクトル行ベクトルと行列の演算を定義
#pragma once

//col
template <typename T>
Matrix<T> operator+(const Matrix<T> &mat, const col_valarray<T> &vec);
template <typename T>
Matrix<T> operator+(const col_valarray<T> &vec, const Matrix<T> &mat);

template <typename T>
Matrix<T> operator-(const Matrix<T> &mat, const col_valarray<T> &vec);
template <typename T>
Matrix<T> operator-(const col_valarray<T> &vec, const Matrix<T> &mat);

template <typename T>
Matrix<T> operator*(const Matrix<T> &mat, const col_valarray<T> &vec);
template <typename T>
Matrix<T> operator*(const col_valarray<T> &vec, const Matrix<T> &mat);

template <typename T>
Matrix<T> operator/(const Matrix<T> &mat, const col_valarray<T> &vec);
template <typename T>
Matrix<T> operator/(const col_valarray<T> &vec, const Matrix<T> &mat);

// row
template <typename T>
Matrix<T> operator+(const Matrix<T> &mat, const row_valarray<T> &vec);
template <typename T>
Matrix<T> operator+(const row_valarray<T> &vec, const Matrix<T> &mat);

template <typename T>
Matrix<T> operator-(const Matrix<T> &mat, const row_valarray<T> &vec);
template <typename T>
Matrix<T> operator-(const row_valarray<T> &vec, const Matrix<T> &mat);

template <typename T>
Matrix<T> operator*(const Matrix<T> &mat, const row_valarray<T> &vec);
template <typename T>
Matrix<T> operator*(const row_valarray<T> &vec, const Matrix<T> &mat);

template <typename T>
Matrix<T> operator/(const Matrix<T> &mat, const row_valarray<T> &vec);
template <typename T>
Matrix<T> operator/(const row_valarray<T> &vec, const Matrix<T> &mat);

//--------------------------------------------------------------
// 足し算
template <typename T>
Matrix<T> operator+(const Matrix<T> &mat, const col_valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) += vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator+(const col_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) += vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator+=(const col_valarray<T> &vec)
{
    *this = *this + vec;
    return *this;
}

//--------------------------------------------------------------
// 引き算
template <typename T>
Matrix<T> operator-(const Matrix<T> &mat, const col_valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) -= vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator-(const col_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(-mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) += vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator-=(const col_valarray<T> &vec)
{
    *this = *this - vec;
    return *this;
}

//--------------------------------------------------------------
// 掛け算
template <typename T>
Matrix<T> operator*(const Matrix<T> &mat, const col_valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) *= vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator*(const col_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) *= vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator*=(const col_valarray<T> &vec)
{
    *this = *this * vec;
    return *this;
}
//--------------------------------------------------------------
// 割り算
template <typename T>
Matrix<T> operator/(const Matrix<T> &mat, const col_valarray<T> &vec)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) /= vec[i];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator/(const col_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.col_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat.col_size(), mat.row_size());

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) = vec[i] / mat.at(i, j);
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator/=(const col_valarray<T> &vec)
{
    *this = *this / vec;
    return *this;
}

////////////////////////////////////////////////////////////////
// row
//--------------------------------------------------------------
// 足し算
template <typename T>
Matrix<T> operator+(const Matrix<T> &mat, const row_valarray<T> &vec)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) += vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator+(const row_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) += vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator+=(const row_valarray<T> &vec)
{
    *this = *this + vec;
    return *this;
}

//--------------------------------------------------------------
// 引き算
template <typename T>
Matrix<T> operator-(const Matrix<T> &mat, const row_valarray<T> &vec)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) -= vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator-(const row_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(-mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) += vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator-=(const row_valarray<T> &vec)
{
    *this = *this - vec;
    return *this;
}

//--------------------------------------------------------------
// 掛け算
template <typename T>
Matrix<T> operator*(const Matrix<T> &mat, const row_valarray<T> &vec)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) *= vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator*(const row_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) *= vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator*=(const row_valarray<T> &vec)
{
    *this = *this * vec;
    return *this;
}

//--------------------------------------------------------------
// 割り算
template <typename T>
Matrix<T> operator/(const Matrix<T> &mat, const row_valarray<T> &vec)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat);

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) /= vec[j];
        }
    }
    return result;
}
template <typename T>
Matrix<T> operator/(const row_valarray<T> &vec, const Matrix<T> &mat)
{
    if (mat.row_size() != vec.size())
    {
        throw std::invalid_argument("この行列とベクトルだと計算できないよ！");
    }

    Matrix<T> result(mat.col_size(), mat.row_size());

    for (size_t i = 0; i < mat.col_size(); ++i)
    {
        for (size_t j = 0; j < mat.row_size(); ++j)
        {
            result.at(i, j) = vec[j] / mat.at(i, j);
        }
    }
    return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator/=(const row_valarray<T> &vec)
{
    *this = *this / vec;
    return *this;
}
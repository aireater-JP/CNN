#include <bits/stdc++.h>

#include "CNN/Matrix.hpp"

#include "CNN/out.hpp"

#include "CNN/Loss.hpp"

double cross_entropy_error(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &teacher)
{
    double y = 0;
    for (size_t i = 0; i < x.size(); ++i)
    {
        y += sum(teacher[i] * log(x[i] + DBL_MIN));
    }

    return -y / (x.size() * x[0].col_size());
}

int main()
{
    Matrix<double> t0 = {{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}};
    Matrix<double> t1 = {{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}};
    Matrix<double> x0 = {{0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0}};
    Matrix<double> x1 = {{0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0}};

    std::vector<Matrix<double>> X = {x0,x1};
    std::vector<Matrix<double>> T = {t0,t1};

    auto y = cross_entropy_error(X, T);

    out("a");
}
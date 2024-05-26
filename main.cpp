#include "CNN/Layer/Affine.hpp"

#include "CNN/out.hpp"

#include "CNN/Matrix.hpp"

int main()
{
    Matrix<double> c(1,1);
    
    std::vector<Matrix<double>> a(10,Matrix<double>(2,3));

    std::vector<Matrix<double>> b(make_vec_mat(a));

    out("test");
}
#include "Matrix.hpp"

struct data_size
{
    size_t x, y, z;
};

class Layer
{

public:
    Layer(const data_size input_size) : input_size(input_size) {}

    virtual std::vector<Matrix<double>> forward(const std::vector<Matrix<double>> &x) = 0;
    virtual std::vector<Matrix<double>> backward(const std::vector<Matrix<double>> &y) = 0;

protected:
    data_size input_size;
    data_size output_size;
};

enum init_type
{
    Xavier,
    He
};
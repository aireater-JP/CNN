#pragma once

#include "Layer.hpp"
#include "Loss.hpp"

#include <memory>

class NN
{
    std::vector<std::unique_ptr<Layer>> layer_ptrs;
    std::unique_ptr<Loss> loss_ptr;

public:
    template <class T>
    void add_Layer(T &&l)
    {
        layer_ptrs.emplace_back(std::make_unique<T>(std::move(l)));
    }

    template <class T>
    void set_Loss(T &&l)
    {
        loss_ptr = std::make_unique<T>(std::move(l));
    }

    std::vector<Matrix<double>> predict(const std::vector<Matrix<double>> &x)
    {
        std::vector<Matrix<double>> y = x;
        for (auto &i : layer_ptrs)
        {
            y = i->forward(y);
        }
        return y;
    }

    double loss(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &t)
    {
        return loss_ptr->forward(predict(x), t);
    }

    double gradient(const std::vector<Matrix<double>> &x, const std::vector<Matrix<double>> &t)
    {
        double y = loss(x, t);
        std::vector<Matrix<double>> g = loss_ptr->backward();

        for (size_t i = layer_ptrs.size() - 1; i < layer_ptrs.size(); i--)
        {
            g = layer_ptrs[i]->backward(g);
        }
        return y;
    }

    void update(const double lr)
    {
        for (auto &i : layer_ptrs)
        {
            //i->update(lr);
        }
    }
};
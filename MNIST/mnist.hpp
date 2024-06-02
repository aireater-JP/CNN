#pragma once

#include <vector>
#include <fstream>

// 784
const int MNIST_size = 28 * 28;

class mnist
{
    std::vector<unsigned char> trai_label;
    std::vector<std::vector<unsigned char>> trai_img;

    std::vector<unsigned char> test_label;
    std::vector<std::vector<unsigned char>> test_img;

public:
    mnist()
    {
        std::ifstream ifs;
        ifs.open("MNIST/train-images.idx3-ubyte", std::ios::binary);
        load_img(ifs, trai_img, 60000);
        ifs.close();

        ifs.open("MNIST/t10k-images.idx3-ubyte", std::ios::binary);
        load_img(ifs, test_img, 10000);
        ifs.close();

        ifs.open("MNIST/train-labels.idx1-ubyte", std::ios::binary);
        load_label(ifs, trai_label, 60000);
        ifs.close();

        ifs.open("MNIST/t10k-labels.idx1-ubyte", std::ios::binary);
        load_label(ifs, test_label, 10000);
        ifs.close();
    }

    std::vector<unsigned char> get_trai_img(const size_t id)
    {
        if (id >= trai_img.size())
        {
            return trai_img[0];
        }
        return trai_img[id];
    }

    std::vector<unsigned char> get_test_img(const size_t id)
    {
        if (id >= test_img.size())
        {
            return test_img[0];
        }
        return test_img[id];
    }

    unsigned char get_trai_label(const size_t id)
    {
        if (id >= trai_label.size())
        {
            return trai_label[0];
        }
        return trai_label[id];
    }

    unsigned char get_test_label(const size_t id)
    {
        if (id >= test_img.size())
        {
            return test_label[0];
        }
        return test_label[id];
    }

private:
    void load_img(std::ifstream &ifs, std::vector<std::vector<unsigned char>> &arr, int size)
    {
        ifs.seekg(16, std::ios::beg);

        arr.resize(size, std::vector<unsigned char>(MNIST_size));

        std::vector<unsigned char> temp(MNIST_size);

        for (int i = 0; i < size; i++)
        {
            ifs.read(reinterpret_cast<char *>(&arr[i].front()), MNIST_size);
        }
    }

    void load_label(std::ifstream &ifs, std::vector<unsigned char> &arr, int size)
    {
        ifs.seekg(8, std::ios::beg);

        arr.resize(size);

        ifs.read(reinterpret_cast<char *>(&arr.front()), size);
    }
};
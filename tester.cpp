#include <iostream>
#include <chrono>

#include "CNN/Utility.hpp"

#include "CNN/out.hpp"

constexpr int COUNT = 1024;

// ベンチマーク用のテンプレート関数
template <typename Func>
void benchmark(Func func, const std::string &funcName)
{
    auto start = std::chrono::high_resolution_clock::now();

    // 対象関数を実行
    for (int i = 0; i < COUNT; ++i)
    {
        func();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Execution time for " << funcName << ": " << duration.count() << " ms" << std::endl;
}

// ベンチマーク対象の関数
void testA()
{
    Matrix<int> a(3, 2, 1);
    a.at(0, 0) = 1;
    a.at(0, 1) = 2;
    a.at(1, 0) = 3;
    a.at(1, 1) = 4;
    a.at(2, 0) = 5;
    a.at(2, 1) = 6;

    auto c = dot(a, a.transpose());
}

void testB()
{
    Matrix<int> a(3, 2, 1);
    a.at(0, 0) = 1;
    a.at(0, 1) = 2;
    a.at(1, 0) = 3;
    a.at(1, 1) = 4;
    a.at(2, 0) = 5;
    a.at(2, 1) = 6;

    Matrix<int> c = dot(a, a.transpose());
}

int main()
{
    benchmark(testA, "test-A");
    benchmark(testB, "test-B");

    return 0;
}

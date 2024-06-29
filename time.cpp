#include <bits/stdc++.h>
// #include "CNN/Matrix.hpp"

constexpr int COUNT = 100000;

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

    std::cout << "計測結果 " << funcName << ": " << duration.count() << " ms" << std::endl;
}

// ベンチマーク対象の関数
void testA()
{
    std::valarray<std::valarray<double>> a(std::valarray<double>(9, 100), 100);

    auto c = a / 9.0;
}

void testB()
{
    std::valarray<std::valarray<double>> a(std::valarray<double>(9, 100), 100);
    auto b = a;
}

int main()
{
    benchmark(testA, "test-A");
    benchmark(testB, "test-B");

    return 0;
}

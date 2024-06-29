#include <bits/stdc++.h>
//#include "CNN/Matrix.hpp"

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

    auto b = a + a;
}

void testB()
{
    std::vector<std::vector<double>> a(100, std::vector<double>(100, 9));

    std::vector<std::vector<double>> b(100, std::vector<double>(100));

    for (size_t i = 0; i < 100; ++i)
    {
        for (size_t j = 0; j < 100; ++j)
        {
            b[i][j] = a[i][j] + a[i][j];
        }
    }
}

int main()
{
    benchmark(testA, "test-A");
    benchmark(testB, "test-B");

    return 0;
}

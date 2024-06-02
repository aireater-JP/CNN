#include <bits/stdc++.h>

#include "CNN/out.hpp"

template<typename T>
using row=std::valarray<T>;

template<typename T>
using col=std::valarray<T>;

template<typename T>
col<T> testA(col<T> &a){
    out("col");
    return a+a;
}

template<typename T>
row<T> testA(row<T> &a){
    out("row");
    return a+a;
}

int main()
{
    col a={1,1,1};
    testA(a);
}
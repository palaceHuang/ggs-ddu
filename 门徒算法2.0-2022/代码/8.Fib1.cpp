/*************************************************************************
	> File Name: 8.Fib1.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;

#define TEST(func) { \
    long long b, e; \
    b = clock(); \
    func; \
    e = clock(); \
    printf("Run %lld ms\n", (e - b) * 1000 / CLOCKS_PER_SEC); \
}

unordered_map<long long, long long> f_result;
long long f(long long n) {
    if (n <= 2) return !!(n);
    if (f_result.find(n) == f_result.end()) {
        long long a = n / 2, b = n - a;
        long long val1 = f(b), val2 = f(a + 1), val3 = f(b - 1), val4 = f(a);
        f_result[n] = (val1 * val2 + val3 * val4) % 9973;
    }
    return f_result[n];
}

long long normal_f(long long n) {
    long long a = 1, b = 0;
    for (int i = 0; i < n; i++) {
        b = (a + b) % 9973;
        a = b - a;
    }
    b = (b + 9973) % 9973;
    return b;
}

int main() {
    long long n;
    while (cin >> n) {
        TEST(printf("f[%lld] = %lld\n", n, normal_f(n)));
        TEST(printf("f[%lld] = %lld\n", n, f(n)));
    }
    return 0;
}

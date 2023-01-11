/*************************************************************************
	> File Name: 11.Fib2.cpp
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
using namespace std;

class Matrix {
public :
    Matrix(int n, int m, int e = 0) : n(n), m(m) {
        for (int i = 0; i < n; i++) c.push_back(vector<long long>(m, 0));
        for (int i = 0; i < n; i++) c[i][i] = 1;
    }
    vector<long long> &operator[](int ind) { return c[ind]; }
    Matrix &operator%(int x) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                c[i][j] %= x;
            }
        }
        return *this;
    }
    Matrix operator*(const Matrix &obj) {
        Matrix ret(n, obj.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < obj.m; j++) {
                ret[i][j] = 0;
                for (int k = 0; k < m; k++) {
                    ret[i][j] += c[i][k] * obj.c[k][j];
                }
            }
        }
        return ret;
    }

private:
    int n, m;
    vector<vector<long long>> c;
};

Matrix quick_power(Matrix a, int b) {
    Matrix ans(2, 2, 1), temp = a;
    while (b) {
        if (b % 2) ans = ans * temp % 9973;
        temp = temp * temp % 9973;
        b /= 2;
    }
    return ans;
}

int main() {
    Matrix a(2, 2);
    a[0][0] = 1, a[0][1] = 1, a[1][0] = 1, a[1][1] = 0;
    int n;
    while (cin >> n) {
        Matrix b = quick_power(a, n);
        printf("f[%d] = %lld\n", n, b[1][0]);
    }
    return 0;
}

/*************************************************************************
	> File Name: 6.inv.cpp
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

int ex_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int nx, ny;
    int r = ex_gcd(b, a % b, nx, ny);
    x = ny;
    y = nx - a / b * ny;
    return r;
}

int inv(int a, int b) {
    int x, y;
    ex_gcd(a, b, x, y);
    x %= b;
    x += b;
    x %= b;
    return x;
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        printf("%d * %d %% %d = 1\n", a, inv(a, b), b);
    }
    return 0;
}

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

int main() {
    int a, b, x, y, c;
    while (cin >> a >> b) {
        c = ex_gcd(a, b, x, y);
        printf("%d * %d + %d * %d = %d\n", a, x, b, y, c);
    }
    return 0;
}

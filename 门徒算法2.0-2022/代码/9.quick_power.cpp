/*************************************************************************
	> File Name: 9.quick_power.cpp
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

int quick_power(int a, int b) {
    int ans = 1, temp = a;
    while (b) {
        if (b % 2) ans *= temp;
        temp *= temp;
        b /= 2;
    }
    return ans;
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        printf("%d^%d = %d\n", a, b, quick_power(a, b));
    }
    return 0;
}

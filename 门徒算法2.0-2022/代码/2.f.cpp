/*************************************************************************
	> File Name: 2.f.cpp
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

int f(int n) {
    if (n == 1) return 1;
    return n * f(n - 1);
}

int main() {
    cout << f(5) << endl;
    return 0;
}

/*************************************************************************
	> File Name: 4.prime.cpp
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

#define MAX_N 10000
int prime[MAX_N + 5] = {0};

void init_prime() {
    for (int i = 2; i * i <= MAX_N; i++) {
        if (prime[i]) continue;
        for (int j = i * i; j <= MAX_N; j += i) prime[j] = 1;
    }
    for (int i = 2; i <= MAX_N; i++) {
        if (prime[i] == 0) prime[++prime[0]] = i;
    }
    return ;
}

int main() {
    init_prime();
    cout << "total prime : " << prime[0] << endl;
    int x;
    while (cin >> x) {
        printf("prime[%d] = %d\n", x, prime[x]);
    }
    return 0;
}

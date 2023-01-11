/*************************************************************************
	> File Name: 3.HZOJ-236.cpp
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

void output(int n, int m, int p, vector<int> &buff) {
    if (buff.size() == m) {
        for (int i = 0; i < m; i++) {
            if (i != 0)  cout << " ";
            cout << buff[i];
        }
        cout << endl;
        return ;
    }
    for (int i = p; i <= n; i++) {
        buff.push_back(i);
        output(n, m, i + 1, buff);
        buff.pop_back();
    }
    return ;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> buff;
    output(n, m, 1, buff);
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int> &a) {
    vector<int>::iterator it;
    for (it=a.begin();it!=a.end();++it)
        cout << *it << '\n';
}

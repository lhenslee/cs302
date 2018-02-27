#include <iostream>
#include <vector>
#include "print_vector.cpp"
using namespace std;

void bubble_sort(vector<int> &a) {
    int n = a.size();
    /* run sweeps until array is sorted */
    while (n!=0) {
        /* assume no swaps at the begining */
        int newn=0;
        /* run a sweep on the array */
        for (int i=1;i<n;i++) {
            if (a[i-1]>a[i]) {
                swap(a[i-1],a[i]);
                newn=i;
            }
        }
        /* the final swap at the end of a sweep */
        n = newn;
    }
}

int main() {
    vector<int> a;
    a.push_back(4); a.push_back(9); a.push_back(8);
    a.push_back(3); a.push_back(2); a.push_back(5);
    bubble_sort(a);
    print(a);
}

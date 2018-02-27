#include <iostream>
#include <vector>
using namespace std;

void selection_sort(vector<int> &A) {
    /* a[0] to a[n-1] is the array to sort */
    int i, j;
    int n = A.size();
    
    /* advance the position through the entire array */
    /*   (could do j < n-1 because single element is also min element) */
    for(j=0;j<n-1;j++) {
        /* find the min element in the unsorted a[j .. n-1] */

        /* assume the min is the first element */
        int iMin = j;
        /* test against elements after j to find the smallest */
        for (i = j+1; i < n; i++) {
            /* if this element is less, then it is the new minimum */
            if (A[i] < A[iMin]) {
                /* found new minimum; remember its index */
                iMin = i;
            }
        }
        if (iMin != j)
            swap(A[j],A[iMin]);
    }
}

int main() {
    vector<int> test;
    test.push_back(4); test.push_back(3);
    test.push_back(7); test.push_back(2);
    test.push_back(9); test.push_back(8);
    selection_sort(test);
    vector<int>::iterator it;
    for (it=test.begin();it!=test.end();++it) {
        cout << *it << '\n';
    }
}

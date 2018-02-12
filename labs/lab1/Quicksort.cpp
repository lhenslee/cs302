#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;


// Sort range a to b
template <typename Tdata>
void quicksort(vector<Tdata> & din, int a, int b) { 
    if(b<=a) return;
    int N = b-a+1;
    int pi = rand()%N+a;
    Tdata pivot = din[pi];
    swap(din,pi,b);
    int i = a, j = b-1;
    while (1) {
        while (din[i] < pivot && i<b) { i++; }
        while (j>=a && pivot < din[j]) { j--; }
        if (i>=j) break;
        swap(din, i, j);
    }

    swap(din,i,b);
    quicksort(din,a,i-1);
    quicksort(din,i+1,b);
}

// Find the correct data for a certain index and place it there
template <typename Tdata>
void quickselect(vector<Tdata> &A,int left, int k,int right) {
    while (1) {
        int N = right-left+1;
        int pi = rand()%N+left;
        Tdata pivot = A[pi];
        swap(A,pi,right);
        int i = left, j = right-1;
        while (1) {
            while (A[i] < pivot && i<right) { i++; }
            while (j>=left && pivot < A[j]) { j--; }
            if (i>=j) break;
            swap(A, i, j);
        }
        swap(A,i,right);
        int pindex = i;
        if (pindex == k) return;

        if (k < pindex) right = pindex-1;
        else            left = pindex+1;
    }
}

// Swap data in an array
template <typename Tdata>
void swap(vector<Tdata> &din, int a, int b) {
    Tdata left = din[a];
    Tdata right = din[b];
    din[a] = right;
    din[b] = left;
}

class person_t {
    public:
        person_t() { }

        // Comparison operator of lastname, firstname, phone number
        friend bool operator<(const person_t &l, const person_t &r) {
            string left = l.lastname+' '+l.firstname+' '+l.phonenum;
            string right = r.lastname+' '+r.firstname+' '+r.phonenum;
            return (left < right);
        }
        friend istream & operator>>(istream &, person_t &);
        friend ostream & operator<<(ostream &, const person_t &);

    private:
        string firstname;
        string lastname;
        string phonenum;
};

// Input each line into a person_t first, last, phone
istream & operator>>(istream &in, person_t &r) { 
    in >> r.firstname >> r.lastname >> r.phonenum;
    return in;
}

// Output for a person_t last, first, phone
ostream & operator<<(ostream &out, const person_t &r) {
    int len = r.lastname.size()+r.firstname.size();
    out << r.lastname << ' ' << r.firstname << setw(35-len) << r.phonenum;
    return out;
}

// Print the array with iterators
void printlist(const vector<person_t>::iterator &start,const vector<person_t>::iterator &end,int k0,int k1) {
    vector<person_t>::iterator it = start;
    while (it!=end) {
        cout << *it  << '\n';
        ++it; 
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    vector<person_t> A;   
    person_t din;
    while (cin >> din)
        A.push_back(din);
    int N = (int)A.size();

    // perform command-line check 
    // if given as command-line arguments,
    // update k0, k1 and apply quickselect
    int k0 = 0, k1 = N-1;
    if (argv[1]) k0 = atoi(argv[1]);
    if (argv[2]) k1 = atoi(argv[2]);
    if (k1<k0) {
        cerr << "Please enter a valid range\n";
        return 0;
    }
    if (k0<0 || k0>=A.size() || k1<0 || k1>=A.size()) {
        cerr << "Please enter a valid index\n";
        return 0;
    }
    
    // to partition A accordingly
    quickselect(A,0,k0,N-1);
    quickselect(A,k0,k1,N-1);
    quicksort(A, k0, k1);
    printlist(A.begin(),A.end(),k0,k1);
}

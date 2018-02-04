#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
// include header files needed
using namespace std;

// template <typename Tdata>
// void quickselect(...) { write this }

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

        // add operator< using lastname, firstname, phone number
        friend bool operator<(const person_t &l, const person_t &r) {
            string left = l.lastname+' '+l.firstname+l.phonenum;
            string right = r.lastname+' '+r.firstname+r.phonenum;
            return (left < right);
        }
        friend istream & operator>>(istream &, person_t &);
        friend ostream & operator<<(ostream &, const person_t &);

    private:
        string firstname;
        string lastname;
        string phonenum;
};

istream & operator>>(istream &in, person_t &r) { 
    in >> r.firstname >> r.lastname >> r.phonenum;
    return in;
}

ostream & operator<<(ostream &out, const person_t &r) {
    int len = r.lastname.size()+r.firstname.size();
    out << r.lastname << ' ' << r.firstname << setw(30-len) << r.phonenum << '\n';
    return out;
}

void printlist(const vector<person_t>::iterator &start,const vector<person_t>::iterator &end) {
    vector<person_t>::iterator it = start;
    while (it!=end) {
        cout << *it; ++it;
    }
}

int main(int argc, char *argv[]) {
    // perform command-line check 
    srand(time(NULL));
    vector<person_t> A;

    person_t din;
    while (cin >> din)
        A.push_back(din);

    int N = (int)A.size();

    int k0 = 0;
    int k1 = N-1;

    // if given as command-line arguments,
    // update k0, k1 and apply quickselect
    // to partition A accordingly

    quicksort(A, k0, k1);
    //sort(A.begin(),A.end());
    printlist(A.begin(), A.end());
}

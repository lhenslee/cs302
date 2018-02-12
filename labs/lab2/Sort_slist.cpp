// icnlude header files needed
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

// template <typename T>
template <class T>
class slist {
  private:
    struct node {
      node() { data = T(); next = NULL; }
      // add node(const T &key) { write this }
      node(const T &key) { data = key; next = NULL; }
      // add overloaded operator< code
      bool operator<(const node&r) const { return (data<r.data); }

      T data;
      node *next;
    };

   // add class sptr { write this for node data }
    class sptr {
        public:
            sptr(node *_ptr=NULL) { ptr = _ptr; }

            bool operator< (const sptr &rhs) const {
                return *ptr < *rhs.ptr;
            }
            node *operator*(){ return ptr; }

        private:
            node *ptr;
    };

  public:
	class iterator {
	public:
	  iterator() { p = NULL; }
	  T & operator*() { return p->data; }
	  iterator & operator++() { p = p->next; return *this; }
	  bool operator!=(const iterator & rhs) const { return p != rhs.p; }

	  friend class slist<T>;

	private:
	  iterator(node *n_p) { p = n_p; }
	  node *p;
	};

  public:
    slist();
	~slist();

    void push_back(const T &);
	void sort();

	iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(NULL); }

  private:
    node *head;
    node *tail;
};


template <typename T>
slist<T>::slist() {
    head = new node();
    tail = head;
}

template <typename T>
slist<T>::~slist() {
    while (head->next != NULL) {
        node *p = head->next;
        head->next = p->next;
        delete p;
    }
    delete head;

    head = NULL;
    tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
    tail->next = new node(din);
    tail = tail->next;
}

template <typename T>
void slist<T>::sort() {
    //std::sort(begin(),end());
    // determine number of list elements
    // set up smart pointer array called Ap
    // apply std::sort(Ap.begin(), Ap.end())
    // use sorted Ap array to relink list
    int count = 0;
    iterator start = begin(), finish = end();
    while(start!=finish) {
        count++; ++start;
    }
    vector<sptr> Ap(count);
    start = begin();
    for(int i=0; i<count; i++) {
        Ap[i] = (sptr(start.p)); ++start;
    }
    std::sort(Ap.begin(),Ap.end());
    node *p = *Ap[0];
    node *q = *Ap[1];
    head->next = p; p->next = q;
    p = p->next;
    for(int i=2; i<count; i++) {
        q = *Ap[i]; p->next = q;
        p = p->next;
    }
    p->next = NULL;
    
}

class person_t {
    public:
        person_t() { }

        // Comparison operator of lastname, firstname, phone number
        bool operator<(const person_t &r) const {
            string left = lastname+' '+firstname+' '+phonenum;
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
void printlist(const slist<person_t>::iterator &start,const slist<person_t>::iterator &end) {
    slist<person_t>::iterator it = start;
    while (it!=end) {
        cout << *it << '\n'; ++it;
    }
}

int main(int argc, char *argv[]) {
    // copy command-line check from Quicksort.cpp
    if (argc > 1) {
        cerr << "Usage: ./Sort_slist < file.txt\n";
        return 0;
    }

    slist<person_t> A;

    person_t din;
    while (cin >> din) {
        A.push_back(din);
    }

    A.sort();

    printlist(A.begin(), A.end());
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;

#include "support.h"

const char ETX = 0x3;

void ppm::read(const char *fname) {
    fstream fin;
    fin.open(fname);
    if (fin.fail()) {
        cout << "Error: cannot open " << fname << " for reading!\n"; 
        exit(1);
    }
    string magicid;
    int ncols, nrows;
    int maxvalue;

    fin >> magicid >> ncols >> nrows >> maxvalue;
    
    while (fin.get() != '\n') { /* skip */ }
    
    img.assign(nrows,ncols); 

    fin.read((char *)img.data(),nrows*ncols*3);

    fin.close();
}

void ppm::write(const char *file) {
    ofstream fout;
    fout.open(file);
    fout << "P6\n";
    fout << img.get_Ncols() << ' ' << img.get_Nrows() << '\n';
    fout << "255\n";
    fout.write((char *)img.data(),img.get_Nrows()*img.get_Ncols()*3);
    fout.close();
}

void rnumgen::pdf(const vector<int> &v) {
    F.resize(v.size());
    partial_sum(v.begin(), v.end(), F.begin());
    transform(F.begin(), F.end(), F.begin(), bind2nd(divides<float>(),*(F.end()-1)));
}

int rnumgen::rand() const {
    const float randnorm = RAND_MAX+1.0f;
    const float p = (float)std::rand()/randnorm;
    return upper_bound(F.begin(), F.end(), p) - F.begin();
}

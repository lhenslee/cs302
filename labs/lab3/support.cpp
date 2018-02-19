#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "support.h"

const char ETX = 0x3;

void ppm::read(istream &fin) { 
    string magicid;
    int ncols, nrows;
    int maxvalue;

    fin >> magicid >> ncols >> nrows >> maxvalue;

    cout << magicid << "\n";
    cout << ncols << " " << nrows << "\n";
    cout << maxvalue << "\n";
    while (fin.get() != '\n') { /* skip */ }
    
    img.assign(nrows,ncols); 

    int nrgb = ncols; // pixels per line
    int nrgb_read; // pixels read per line
    int npixels_read = 0; // pixels read in total
    
    unsigned char *rgb_ptr; // data pointer
    unsigned char buf[3*nrgb]; // data buffer
    RGB *rgbp;
    RGB buffer = img.data();
    char text[80]; // text buffer

    while (1) {
        fin.read((char *)buf, 3*nrgb);
        nrgb_read = fin.gcount()/3;
        if (nrgb_read == 0 && fin.eof())
            break;
        sprintf(text, "%07d ", npixels_read);
        //cout << text;
        rgb_ptr = buf;
        rgbp = buffer;
        vector<unsigned char> rgb[3];
        for (int i=0; i<nrgb_read; i++) {
            cout << " ";
            for (int j=0; j<3; j++) {
                sprintf(text, " %03u", *rgb_ptr++);
                //cout << text;
            }
            // store rgb and move 
            rgbp = RGB(rgb);
        }
        cout << "\n";
        npixels_read += nrgb_read;
    }
    cout << img[0] << '\n';
}

void ppm::write(const char *file) { 
}

int main() {
    ppm test;
    fstream fin;
    fin.open("plane.ppm");
    test.read(fin);
    fin.close();
    exit(1);
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "support.cpp"
using namespace std;

#include "support.h"

void set_pixel_list(ppm &img, vector<pixel> &v) {
    // two for loops and a push_back
    int nrows,ncols;
    nrows = img.get_Nrows();
    ncols = img.get_Ncols();
    for (int i=0;i<nrows;i+=2) {
        for (int j=0;j<ncols;j+=2)
            v.push_back(pixel(i,j));
    }
}

void encode(ppm &img,const char*fname) {
    // write this
    vector<pixel> v;
    set_pixel_list(img,v);
    
    string magicid;
    int ncols, nrows, maxvalue;

    char msg[100];
    char c;
    int ct = 0;
    while (cin>>noskipws>>c) { msg[ct]=c;ct++; }
    ct++; msg[ct] = ETX;
    cout << '\n';

    // first attempt to make even pixels work
    int count = 0;
    int flag = 0;
    for (int i=0; i<100; i++) {
        uchar temp = msg[i];
        for (int j=0; j<8; j++) {
            int row = v[count].get_Nrows();
            int col = v[count].get_Ncols();
            RGB p = img[row][col];
            uchar red = p.r();
            uchar green = p.g();
            uchar blue = p.b();
            int lsb = (msg[i]>>j)&0x1;
            switch (count%3) {
                case 0:
                    red &= 0xFE;    
                    red |= lsb;
                    img[row][col].set_r(red);
                    break;
                case 1: 
                    green &= 0xFE;
                    green |= lsb;
                    img[row][col].set_g(green);
                    break;
                case 2: 
                    blue &= 0xFE;
                    blue |= lsb;
                    img[row][col].set_b(blue);
                    break;
            }
            count++;
        }
    }
}

void decode(ppm &img) {
    // write this
    vector<pixel> v;
    set_pixel_list(img, v);
    int count = 0;
    uchar cp[100];
    for (int i=0; i<100; i++) cp[i]=0x0;
    for (int i=0; i<100; i++) {
        for (int j=0; j<8; j++) {
            int row = v[count].get_Nrows();
            int col = v[count].get_Ncols();
            RGB p = img[row][col];
            uchar red = p.r();
            uchar green = p.g();
            uchar blue = p.b();
            int lsb = 0;
            switch(count%3) {
                case 0: 
                    lsb = red&0x1;
                    cp[i] |= lsb<<j;
                    break;
                case 1: 
                    lsb = green&0x1;
                    cp[i] |= lsb<<j;
                    break;
                case 2: 
                    lsb = blue&0x1;
                    cp[i] |= lsb<<j;
                    break;
            }
            count++;
        }
        if (cp[i]==ETX) break;
    }
    cout << cp;
}

int main(int argc, char *argv[]) {
    // parse command line arguments
    // if something not right,
    // print error message and exit
    if (argc<3) {
        cerr << "usage: crypto -encode|decode image.ppm\n";
        exit(1);
    }
    char * fname = argv[2];
    char * mode = argv[1];
    int count = 0;
    while (fname[count]!=0) {
        count++;
    }
    char outfile[count+5];
    for (int i=0; i<count-4; i++) {
        outfile[i] = fname[i];
    }
    char extension[9] = {'_','w','m','s','g','.','p','p','m'};
    int helper = 0;
    for (int i=count-4; i<count+5; i++) {
        outfile[i] = extension[helper]; helper++;
    }

    ppm img;
    img.read(fname);
    if (strcmp(mode,"-encode")==0) { encode(img,fname); img.write(outfile); }
    else if (strcmp(mode,"-decode")==0) decode(img);
    else {
        cerr << "usage:crypto -encode|decode image.ppm\n";
        exit(1);
    }
}

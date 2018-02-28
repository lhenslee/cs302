#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "support.cpp"
using namespace std;

#include "support.h"

void set_pixel_list(ppm &img, vector<pixel> &v, const int & count) {
    // two for loops and a push_back
    rnumgen RNG(count);
    int nrows,ncols;
    nrows = img.get_Nrows();
    ncols = img.get_Ncols();
    for (int i=0;i<nrows;i++) {
        for (int j=0;j<ncols;j++)
            v.push_back(pixel(i,j));
    }
    // get histogram
    vector<int> hist(4096, 0);
    for (int i=0; i<nrows; i++) {
        for (int j=0; j<ncols; j++) {
            int color = img[i][j].color();
            hist[color]++;
        }
    }
    RNG.pdf(hist);

    for(int i=(int)v.size()-1; i>0; --i) {
        int r1 = RNG.rand();
        int r2 = RNG.rand();
        int r24 = (r1<<12) | r2;
        //cout << r12_1 << ' ' << r12_2 << ' ' << r24 << '\n';
        swap(v[i],v[r24%(i+1)]);
    }
}

void encode(ppm &img,const string& key) {
    // write this
    vector<pixel> v;
    int c = 0;
    set_pixel_list(img,v,key.size());

    string magicid;
    int ncols, nrows, maxvalue;

    char msg[100];
    int ct = 0;
    while (cin>>noskipws>>msg[ct]) { ct++; }
    ct++; msg[ct] = ETX;
    ct = 0;
    for (int i=0; msg[i]!=ETX; i++) {
        if (key.size()>0) {
            msg[i]=msg[i]^key[i%key.size()];
            ct++;
        }
    }
    msg[ct] = msg[ct]^key[ct%key.size()];

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

void decode(ppm &img, const string&  key) {
    // write this
    vector<pixel> v;
    set_pixel_list(img, v, key.size());
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
        if (cp[i]==(ETX^key[i%key.size()])) break;
    }
    int c = 0;
    for (int i=0; cp[i]!=(ETX^key[i%key.size()]); i++) {
        cp[i]=cp[i]^key[i%key.size()]; c++;
    }
    cp[c]=ETX;
    cout << cp;
}

int main(int argc, char *argv[]) {
    // parse command line arguments
    // if something not right,
    // print error message and exit
    if (argc<3) {
        cerr << "usage: crypto -encode|decode [-key=\"text\"] image.ppm\n";
        exit(1);
    }
    char * mode = argv[1];
    char * keyin;
    char * fname;
    if (argv[2][0]=='-') {
        keyin = argv[2]; fname = argv[3];
    } else fname = argv[2];
    string f;
    for (int i=0; i<5; i++) f.push_back(keyin[i]);
    if (f!="-key=") {
        cerr << "usage: crypto -encode|decode [-key=\"text\"] image.ppm\n";
        exit(1);
    }
    
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
    
    string key;
    if ((int)keyin[0]!=49) {
        for (int i=5; keyin[i]!=0; i++) {
            key.push_back(keyin[i]);
        }
    } else key.clear();
    
    ppm img;
    img.read(fname);
    if (strcmp(mode,"-encode")==0) { encode(img,key); img.write(outfile); }
    else if (strcmp(mode,"-decode")==0) decode(img,key);
    else {
        cerr << "usage: crypto -encode|decode image.ppm\n";
        exit(1);
    }
}

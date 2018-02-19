#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <vector>
#include <fstream>

typedef unsigned char uchar;
extern const char ETX;

template <typename T>
class matrix {
    public:
        matrix() { }
        matrix(int n_Nrows, int n_Ncols) {
            Nrows = n_Nrows;
            Ncols = n_Ncols;
            buf = new T [Nrows*Ncols];
        }
        void assign(int r, int c)
        { buf = new T(r,c); }
        T *data() const { return buf; }
        ~matrix() {
            delete [] buf;
        }
        int get_Nrows() const { return Nrows; }
        int get_Ncols() const { return Ncols; }
        T * operator[] (int i) { return &buf[i*Ncols]; }
    private:
        int Nrows, Ncols;
        T *buf;
};

struct pixel { 
    public:
        pixel(int r=0, int c=0) 
        { Nrows=r; Ncols=c; }
    private:
        int Nrows, Ncols;
};

struct RGB { 
    public: 
        RGB(uchar r=0, uchar g=0, int b=0)
        { R=r; G=g; B=b; }
    private:
        uchar R,G,B;
};

class ppm {
    public:
        ppm(int r=0, int c=0) 
        { Nrows=r; Ncols=c; img=matrix<RGB>(r,c);}
        void read(std::istream &);
        void write(const char *);
        RGB *operator[](int i) { return img[i]; }
        int get_Nrows() const { return Nrows; }
        int get_Ncols() const { return Ncols; }
    private:
        int Nrows, Ncols;
        matrix<RGB> img;
};

#endif

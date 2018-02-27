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
        void assign(int r, int c) {   
            Nrows=r; Ncols=c;
            buf = new T [Nrows*Ncols]; 
        }
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
        int get_Nrows() { return Nrows; }
        int get_Ncols() { return Ncols; }
    private:
        int Nrows, Ncols;
};

class RGB { 
    public: 
        RGB(uchar r=0, uchar g=0, int b=0) { R=r; G=g; B=b; }
        friend std::ostream& operator<<(std::ostream& os, const RGB& rgb) {
            os << rgb.R << rgb.G << rgb.B;
            return os;
        }
        uchar r() { return R; }
        uchar g() { return G; }
        uchar b() { return B; }
        void set_r(uchar r) { R=r; }
        void set_g(uchar g) { G=g; }
        void set_b(uchar b) { B=b; }  
    private:
        uchar R,G,B;
};

class ppm {
    public:
        ppm(int r=0, int c=0) 
        { img=matrix<RGB>(r,c);}
        void read(const char *);
        void write(const char *);
        RGB *operator[](int i) { return img[i]; }
        int get_Nrows() const { return img.get_Nrows(); }
        int get_Ncols() const { return img.get_Ncols(); }
    private:
        matrix<RGB> img;
};

#endif

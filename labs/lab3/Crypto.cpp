#include <...>
using namespace std;

#include "support.h"

void set_pixel_list(ppm &img, vector<pixel> &v) {
    // two for loops and a push_back
}

void encode(...) {
  // write this
}

void decode(...) {
  // write this
}

int main(int argc, char *argv[]) {
  // parse command line arguments
  // if something not right,
  // print error message and exit

  ppm img;
  img.read(fname);

  if (mode=="encode") { encode(img); img.write(fname); }
  else
  if (mode=="decode") decode(img);
}

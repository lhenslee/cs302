#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    FILE *fin, *fout;

    fin = stdin; //fopen("input.txt", "r");
    fout = stdout; //fopen("output.txt", "w");
    
    char s[80];
    float f;
    
    while (fscanf(fin, "%s %f", s, &f) == 2) {
        fprintf(fout, "%-10s 0x%08x %12.2f\n", s, *(int*)&f, f);
    }

    fclose(fin);
    fclose(fout);
}

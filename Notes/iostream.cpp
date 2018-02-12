#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream fin;
    ofstream fout;

    streambug *sbuf_cin = NULL;
    streambuf *sbuf_cout = NULL;

    streambuf *sbuf_fin = NULL;
    streambuf *sbuf_fout = NULL;

    if (argc == 2 || argc == 3) {
        fin.open(argv[1]);
        sbuf_cin = cin.rdbuf();
        sbuf_fin = fin.rdbuf();
        cin.rdbuf(sbuf_fin);
    }

    if (argc == 3) {
        fout.open(argv[2]);
        sbuf_cout = cout.rdbuf();
        sbuf_fout = fout.rdbuf();
        cout.rdbuf(sbuf_fout);
    }

    string s;
    float f;

    cout.setf(ios::fixed);
    cout.precision(2);

    while (cin >> s >> f) {
        cout << setw(10) << left << s << ' ' 
            << "0x"
            << setw(8) << right 
            << setfill('0')
            << hex << *(int*)&f << ' '
            << setfill(' ')
            << setw(12) << right << f << "\n";
    }

    if (fout.is_open()) {
        fout.close();
        cout.rdbuf(sbuf_cout);
    }

    if (fin.is_open()) {
        fin.close();
        fin.rdbuf(sbuf_cin);
    }

    string text;
    while (1) {
        cout << "loop> ";
        getline(cin, text);
        if (cin.eof())
            break;
    }
}

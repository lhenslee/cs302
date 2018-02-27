#include <iostream>
#include <string>
using namespace std;

int main() {
    char msg[100];
    unsigned char copy[100];
    cin.getline(msg,100);
    for (int i=0; i<100; i++) {
        if ((int)msg[i]==0) break;
        copy[i] = 0x0;
        for (int j=0;j<8;j++) {
            copy[i] |= ((msg[i]>>j)&0x1)<<j;
        }
        cout << (int)copy[i] << ' ' << copy[i] << '\n';
    }
    cout << "Original: " << msg << '\n';
    cout << "Copy: " << copy << '\n';
}

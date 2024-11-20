#include <iostream>
using namespace std;

int countSetBits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

bool checkParity(int num) {
    int setBitsCount = countSetBits(num);
    return setBitsCount % 2 == 0;
}

int main() {
    int num;
    cout << "Enter an integer: ";
    cin >> num;
    bool isEvenParity = checkParity(num);
    if (isEvenParity) {
        cout << "Number of set bits is even. Parity: EVEN\n";
    } else {
        cout << "Number of set bits is odd. Parity: ODD\n";
    }
    return 0;
}
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int dataBits, parityBits = 0;
    cout << "Enter the number of data bits: ";
    cin >> dataBits;

    while (dataBits + parityBits + 1 > pow(2, parityBits)) parityBits++;
    int totalBits = dataBits + parityBits;

    cout << "Number of parity bits: " << parityBits << ", Total bits: " << totalBits << endl;

    int data[dataBits];
    cout << "Enter the Data Bits one by one:\n";
    for (int i = 0; i < dataBits; ++i) cin >> data[i];

    int encodedData[totalBits + 1], dataIndex = 0, power = 0;
    for (int i = 1; i <= totalBits; ++i)
        encodedData[i] = (i == pow(2, power)) ? (++power, 0) : data[dataIndex++];

    cout << "Data bits encoded with parity bits (0): ";
    for (int i = 1; i <= totalBits; ++i) cout << encodedData[i] << " ";
    cout << endl;

    for (int i = 0; i < parityBits; ++i) {
        int position = pow(2, i), parity = 0;
        for (int j = position; j <= totalBits; j += 2 * position)
            for (int k = j; k < j + position && k <= totalBits; ++k)
                parity += encodedData[k];
        encodedData[position] = parity % 2;
    }

    cout << "Hamming codeword bits for even parity are: ";
    for (int i = 1; i <= totalBits; ++i) cout << encodedData[i] << " ";
    cout << endl;

    return 0;
}

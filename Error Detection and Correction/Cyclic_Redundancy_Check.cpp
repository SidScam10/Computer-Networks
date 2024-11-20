#include <iostream>
using namespace std;

string xorfun(string encoded, string crc) {
    int crclen = crc.length();
    for (int i = 0; i <= encoded.length() - crclen; ) {
        for (int j = 0; j < crclen; j++) 
            encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1';
        while (i < encoded.length() && encoded[i] != '1') i++;
    }
    return encoded;
}

int main() {
    string data, crc, encoded;
    cout << "For sender side:\nEnter Data bits: ";
    cin >> data;
    cout << "Enter Generator: ";
    cin >> crc;

    encoded = data + string(crc.length() - 1, '0');
    encoded = xorfun(encoded, crc);

    string checksum = encoded.substr(encoded.length() - crc.length() + 1);
    cout << "Checksum generated is: " << checksum << endl;
    cout << "Message to be Transmitted over network: " << data + checksum << endl;

    cout << "\nFor receiver side:\nEnter the received message: ";
    cin >> encoded;
    encoded = xorfun(encoded, crc);

    cout << (encoded.substr(encoded.length() - crc.length() + 1).find('1') != string::npos 
             ? "Error in communication" : "No Error!") << endl;
    return 0;
}

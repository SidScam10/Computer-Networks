#include <iostream>
using namespace std;

const int ROWS = 4, COLUMNS = 4;

int calculateRowParity(const int row[], int columns) {
    int parity = 0;
    for (int i = 0; i < columns; i++) parity ^= row[i];
    return parity;
}

int calculateColumnParity(const int matrix[][COLUMNS], int rows, int column) {
    int parity = 0;
    for (int i = 0; i < rows; i++) parity ^= matrix[i][column];
    return parity;
}

bool checkOverallParity(const int matrix[][COLUMNS]) {
    int parity = 0;
    for (int i = 0; i < ROWS; i++) parity ^= calculateRowParity(matrix[i], COLUMNS);
    for (int j = 0; j < COLUMNS; j++) parity ^= calculateColumnParity(matrix, ROWS, j);
    return parity == 0;
}

int main() {
    int matrix[ROWS][COLUMNS];
    cout << "Enter elements of the 2D array:\n";
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
            cin >> matrix[i][j];

    cout << "2D Array:\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) cout << matrix[i][j] << " ";
        cout << "\n";
    }

    cout << (checkOverallParity(matrix) ? 
             "Parity check: PASS. Overall parity is correct.\n" : 
             "Parity check: FAIL. Overall parity is incorrect.\n");

    return 0;
}

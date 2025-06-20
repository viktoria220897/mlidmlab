#include <iostream>
#include <Windows.h>
#include <locale.h>

using namespace std;

bool refliss(int** matt, int n) {
    for (int m = 0; m < n; ++m) {
        if (matt[m][m] != 1) {
            return false; 
        }
    }
    return true;
}


bool simmetri(int** matt, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matt[i][j] != matt[j][i]) {
                return false; 
            }
        }
    }
    return true;
}


bool antisimmetri(int** matt, int n) {
    for (int d = 0; d < n; ++d) {
        for (int g = 0; g < n; ++g) {
            if (d != g && matt[d][g] == 1 && matt[g][d] == 1) {
                return false;
            }
        }
    }
    return true; 
}


bool tranzit(int** matt, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matt[i][j] == 1) {
                for (int k = 0; k < n; ++k) {
                    if (matt[j][k] == 1 && matt[i][k] != 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true; 
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    cout << "Какого размера будет матрица?:";
    cin >> n;


    int** matt = new int* [n];
    for (int a = 0; a < n; ++a) {
        matt[a] = new int[n];
    }

    cout << "Матрица:\n";
    for (int b = 0; b < n; ++b) {
        for (int j = 0; j < n; ++j) {
            cin >> matt[b][j];
        }
    }


    bool validn = true;
    for (int l = 0; l < n; l++) {
        for (int p = 0; p < n; p++) {
            if (matt[l][p] != 0 && matt[l][p] != 1) {
                validn = false;
            }
        }
    }

    if (!validn) {
        cout << "Ошибка\n";
        return 0;
    }


    cout << "Рефлексивно:";
    cout << (refliss(matt, n) ? "Да" : "Нет") << endl;

    cout << "Симметрично:";
    cout << (simmetri(matt, n) ? "Да" : "Нет") << endl;

    cout << "Антисимметрично:";
    cout << (antisimmetri(matt, n) ? "Да" : "Нет") << endl;

    cout << "Транзитивно:";
    cout << (tranzit(matt, n) ? "Да" : "Нет") << endl;


    for (int i = 0; i < n; ++i) {
        delete[] matt[i];
    }
    delete[] matt;

    return 0;
}

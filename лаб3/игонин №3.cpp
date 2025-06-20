#include <iostream>
#include<Windows.h>
#include <unordered_map>
using namespace std;


bool funkcia(const int x[], const int y[], int n) {
    std::unordered_map<int, int> mapping;
    for (int i = 0; i < n; ++i) {
        if (mapping.count(x[i])) {
            if (mapping[x[i]] != y[i]) return false;
        }
        else {
            mapping[x[i]] = y[i];
        }
    }
    return true;
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int mnA, mnB, par;

    cout << "Введите множество A: ";
    cin >> mnA;
    cout << "Введите множество B: ";
    cin >> mnB;

    cout << "Введите кол-во пар в отношении: ";
    cin >> par;

  
    cout << "Введите пары (a b) по одной на строке:\n";
    int* a = new int[par];
    int* b = new int[par];

    for (int i = 0; i < par; i++) {
        cin >> a[i] >> b[i];
    }

  
    if (funkcia(a, b, par)) {
        cout << "Отношение является функцией." << endl;
    }
    else {
        cout << "Отношение не является функцией." << endl;
    }

 
    delete[] a;
    delete[] b;

    return 0;
}

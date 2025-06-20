#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

struct Element {
    char number;
    char letter;
    char evenNum1;
    char evenNum2;
};

bool valid(string input) {
    if (input.length() == 4 &&
        (input[0] >= '0' && input[0] <= '9') &&
        (input[1] >= 'a' && input[1] <= 'z') &&
        ((input[2] >= '0' && input[2] <= '9') && (input[2] - '0') % 2 == 0) &&
        ((input[3] >= '0' && input[3] <= '9') && (input[3] - '0') % 2 == 0)) {
        return true;
    }
    return false;
}

void inputArray(vector<Element>& arr, int b) {
    Element elem;
    cout << "(c - цифра, b - буква, i - четная цифра)" << endl;

    for (int i = 0; i < b; ++i) {
        cout << "Элемент " << i << ": ";
        string input;
        cin >> input;

        if (valid(input)) {
            elem.number = input[0];
            elem.letter = input[1];
            elem.evenNum1 = input[2];
            elem.evenNum2 = input[3];
            arr.push_back(elem);
        }
        else {
            cout << "Ошибка ввода" << endl;
            i--;
        }
    }
}

void printArray(const vector<Element>& arr) {
    if (arr.empty()) {
        cout << "Ничего нет(" << endl;
    }
    else {
        for (size_t i = 0; i < arr.size(); ++i) {
            cout << "Элемент №" << i << ": "
                << arr[i].number << arr[i].letter << arr[i].evenNum1 << arr[i].evenNum2 << endl;
        }
    }
}

void removeNonUnique(vector<Element>& mass) {
    vector<Element> uniqueElements;
    for (int i = 0; i < mass.size(); ++i) {
        bool isUnique = true;
        for (int j = 0; j < uniqueElements.size(); ++j) {
            if (mass[i].number == uniqueElements[j].number &&
                mass[i].letter == uniqueElements[j].letter &&
                mass[i].evenNum1 == uniqueElements[j].evenNum1 &&
                mass[i].evenNum2 == uniqueElements[j].evenNum2) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniqueElements.push_back(mass[i]);
        }
    }


    mass.clear();
    for (size_t i = 0; i < uniqueElements.size(); ++i) {
        mass.push_back(uniqueElements[i]);
    }
}

void unionArr(vector<Element>& result, vector<Element>& mass1, vector<Element>& mass2) {
    for (int i = 0; i < mass1.size(); ++i)
        result.push_back(mass1[i]);
    for (int i = 0; i < mass2.size(); ++i)
        result.push_back(mass2[i]);
    removeNonUnique(result);
}

void interArr(vector<Element>&result, vector<Element>&mass1, vector<Element>&mass2) {
     for (int i = 0; i < mass1.size(); ++i) {
         for (int j = 0; j < mass2.size(); ++j) {
              if (mass1[i] == mass2[j]) {
                 result.push_back(mass1[i]);
                  break; 
                }
            }
        }
     removeNonUnique(result);
    }

void differenceA(vector<Element>& result, vector<Element>& mass1, vector<Element>& mass2) {
    for (int i = 0; i < mass1.size(); ++i) {
        bool found = false;
        for (int j = 0; j < mass2.size(); ++j) {
            if (mass1[i] == mass2[j]) {
                found = true;
                break; 
            }
        }
        if (!found) {
            result.push_back(mass1[i]);
        }
    }
    removeNonUnique(result);
}


void symDif(vector<Element>& result, vector<Element>& mass1, vector<Element>& mass2) {
    for (int i = 0; i < mass1.size(); ++i) {
        bool found = false;
        for (int j = 0; j < mass2.size(); ++j) {
            if (mass1[i] == mass2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(mass1[i]);
        }
    }

    for (int i = 0; i < mass2.size(); ++i) {
        bool found = false;
        for (int j = 0; j < mass1.size(); ++j) {
            if (mass2[i] == mass1[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(mass2[i]);
        }
    }
    removeNonUnique(result);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int size_a, size_b;
    vector<Element> a, b;

    cout << "Введите размер множества A: ";
    cin >> size_a;
    inputArray(a, size_a);
    removeNonUnique(a);
    cout << "\nМножество A:\n";
    printArray(a);
    cout << endl;

    cout << "Введите размер множества B: ";
    cin >> size_b;
    inputArray(b, size_b);
    removeNonUnique(b);
    cout << "\nМножество B:\n";
    printArray(b);
    cout << endl;

    vector<Element> unionArr, interArr, complA_B, complB_A, symDif;

    unionA(unionArr, a, b);
    cout << "Объединение A или B:\n";
    printArray(unionArr);
    cout << endl;

    interA(interArr, a, b);
    cout << "Пересечение A и B:\n";
    printArray(interArr);
    cout << endl;

    complA(complA_B, a, b);
    cout << "Дополнение A \\ B:\n";
    printArray(complA_B);
    cout << endl;

    complA(complB_A, b, a);
    cout << "Дополнение B \\ A:\n";
    printArray(complB_A);
    cout << endl;

    symDifA(symDif, a, b);
    cout << "Симметрическая разность либо A, либо B:\n";
    printArray(symDif);
    cout << endl;

    return 0;
}
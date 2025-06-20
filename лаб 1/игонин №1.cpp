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
                << arr[i].number << arr[i].letter<< arr[i].evenNum1 << arr[i].evenNum2 << endl;
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
                mass[i].evenNum1== uniqueElements[j].evenNum1 &&
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

void unionA(vector<Element>& result, const vector<Element>& arr1, const vector<Element>& arr2) {
    result = arr1;
    for (const auto& e2 : arr2) {
        if (std::find_if(result.begin(), result.end(), [&](const Element& e1) {
            return e1.number == e2.number &&
                e1.letter == e2.letter &&
                e1.evenNum1 == e2.evenNum1 &&
                e1.evenNum2 == e2.evenNum2;
            }) == result.end()) {
            result.push_back(e2);
        }
    }
}


void interA(vector<Element>& result, const vector<Element>& arr1, const vector<Element>& arr2) {
    for (const auto& el1 : arr1) {
        for (const auto& el2 : arr2) {
            if (el1.number == el2.number &&
                el1.letter == el2.letter &&
                el1.evenNum1 == el2.evenNum1 &&
                el1.evenNum2 == el2.evenNum2) {
                result.push_back(el1);
                break;
            }
        }
    }
}

void complA(vector<Element>& result, const vector<Element>& arr1, const vector<Element>& arr2) {
    for (const auto& el1 : arr1) {
        bool found = false;
        for (const auto& el2 : arr2) {
            if (el1.number == el2.number &&
                el1.letter == el2.letter &&
                el1.evenNum1 == el2.evenNum1 &&
                el1.evenNum2 == el2.evenNum2) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(el1);
        }
    }
}


void symDifA(vector<Element>& result, const vector<Element>& arr1, const vector<Element>& arr2) {
    for (const auto& elem1 : arr1) {
        if (std::find_if(arr2.begin(), arr2.end(), [&](const Element& elem2) {
            return elem1.number == elem2.number &&
                elem1.letter == elem2.letter &&
                elem1.evenNum1 == elem2.evenNum1 &&
                elem1.evenNum2 == elem2.evenNum2;
            }) == arr2.end()) {
            result.push_back(elem1);
        }
    }

    for (const auto& elem2 : arr2) {
        if (std::find_if(arr1.begin(), arr1.end(), [&](const Element& elem1) {
            return elem2.number == elem1.number &&
                elem2.letter == elem1.letter &&
                elem2.evenNum1 == elem1.evenNum1 &&
                elem2.evenNum2 == elem1.evenNum2;
            }) == arr1.end()) {
            result.push_back(elem2);
        }
    }
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
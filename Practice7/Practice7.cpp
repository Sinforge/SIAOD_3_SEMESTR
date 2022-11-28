// Practice7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "RLE.h"
#include "LZ77.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "");
    cout << compress("abbccaa") << endl;
    cout << "\nLZ77\n";
    for (auto code : LZ77("0100001000000100001")) {
        cout << "(" << get<0>(code) << ", " << get<1>(code) << ", " << get<2>(code)<< ")" << endl;
    }
    cout << "\nLZ78";
    for (auto code : LZ78("пропронепронепрнепрона")) {
        cout << "(" << code.first << ", " << code.second << ")\n";
    }
}

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
    for (auto code : LZ77("0100001000000100001")) {
        cout << "(" << get<0>(code) << ", " << get<1>(code) << ", " << get<2>(code)<< ")" << endl;
    }

}

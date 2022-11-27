// Practice7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "RLE.h"
#include "LZ77.h"
using namespace std;
int main()
{
    cout << compress("abbccaa") << endl;
    cout << LZ77("0100001000000100001", 1);

}

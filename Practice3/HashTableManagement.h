#pragma once
#include "BinaryFileFunctions.h"

using namespace std;

struct ElementOfTable {
    int CarId = 0;
    int FileIndex =  0;
};
struct HashTable {
    int Length;
    vector<vector<ElementOfTable>> Table;
    void CreateTable(int Length) {
        this->Length = Length;
        Table = vector<vector<ElementOfTable>>(Length);
        for (int i = 0; i < Length; i++) {
            Table[i] = vector<ElementOfTable>();
        }
    }
};
void ReHashTable(HashTable& HT);


int GetHash(HashTable HashTable, int Key) {
    return Key % HashTable.Length;
}



int InsertKey(HashTable& HT, int Key, int FileIndex = 0) {
    vector<ElementOfTable> Element = HT.Table[GetHash(HT, Key)];
    for (int i = 0; i < Element.size(); i++) {
        if (Element[i].CarId == Key) {
            cout << "Element with such Car Id exist\n";
            return -1;

        }
    }
    if (Element.size() > 5) {
        ReHashTable(HT);
        return 0;
    }
    ElementOfTable NewElem;
    NewElem.CarId = Key;
    NewElem.FileIndex = FileIndex;
    HT.Table[GetHash(HT, Key)].push_back(NewElem);
    return 0;
}


void ReHashTable(HashTable& HT) {
    int NewHashTableLength = HT.Length * 2;
    HashTable NewTable;
    NewTable.CreateTable(NewHashTableLength);
    for (int i = 0; i < HT.Length; i++) {
        for (int j = 0; j < HT.Table[i].size(); j++) {
            InsertKey(NewTable, HT.Table[i][j].CarId, HT.Table[i][j].FileIndex);
        }
    }
    HT = NewTable;
}




//Возвращает позицию удаленного элемента
int DeleteKey(HashTable& HT, int Key, int LastPosition = 0) {
   
    vector<ElementOfTable> Element = HT.Table[GetHash(HT, Key)];
    for (int i = 0; i < Element.size(); i++) {
        if (Element[i].CarId == Key) {
            HT.Table[GetHash(HT, Key)].erase(HT.Table[GetHash(HT, Key)].begin() + i);
            return i;
        }
    }
    return -1;
    
}

int GetFileIndexById(HashTable & HT, int Id) {
    vector<ElementOfTable> Element = HT.Table[GetHash(HT, Id)];
    for (int i = 0; i < Element.size(); i++) {
        if (Element[i].CarId == Id) {
            return Element[i].FileIndex;
        }
   }
    return -1;
}



void PrintHashTable(HashTable& HT) {
    for (int i = 0; i < HT.Length; i++) {
        cout << "HashTable [" << i << "] : ";
        for (int j = 0; j < HT.Table[i].size(); j++) {
            cout << HT.Table[i][j].CarId << " ";
        }
        cout << endl;
    }
}

void TestHashTable() {
    int ex_num;
    HashTable HashTable;
    int Key;
    int TableLength;
    cout << "Тестирование функций хеш-таблицы введите, что хот: \n0)Выход из программы\n1)Создание хеш-таблицы\n2)Вставка ключа в таблицу\n3)Удаление ключа из таблицы\n4)Вывести таблицу\n";
    cin >> ex_num;
    while (ex_num) {
        switch (ex_num) {
        case 1:
            cout << "Введите размер таблицы\n";
            cin >> TableLength;
            HashTable.CreateTable(TableLength);
            break;
        case 2:
            cout << "Введите ключ для вставки в таблицу\n";
            cin >> Key;
            InsertKey(HashTable, Key);
            break;
        case 3:
            cout << "Введите ключ, который хотите удалить из таблицы\n";
            cin >> Key;
            DeleteKey(HashTable, Key);
            break;
        case 4:
            PrintHashTable(HashTable);
            break;
        default:
            break;
        }
        cout << "Тестирование функций хеш-таблицы введите, что хот: \n0)Выход из программы\n1)Создание хеш-таблицы\n2)Вставка ключа в таблицу\n3)Удаление ключа из таблицы\n4)Вывести таблицу\n";
        cin >> ex_num;
    }
}
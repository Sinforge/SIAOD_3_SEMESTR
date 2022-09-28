#pragma once
#include "BinaryFileFunctions.h"

using namespace std;
struct ElementOfTable {
    int CarId = 0;
    bool IsBusy = false;
    bool DeletedOrNot = false;
    int FileIndex =  0;
    ElementOfTable* Next = NULL;
};
struct HashTable {
    int Length;
    ElementOfTable** Table;
    void CreateTable(int Length) {
        this->Length = Length;
        this->Table = (ElementOfTable**)malloc(Length * sizeof(ElementOfTable*));
        for (int i = 0; i < Length; i++) {
            Table[i] = new ElementOfTable();
        }
    }
};

int GetHash(HashTable HashTable, int Key) {
    return Key % HashTable.Length;
}





int InsertKey(HashTable& HT, int Key, int FileIndex = 0) {
    ElementOfTable  * Element = HT.Table[GetHash(HT, Key)];
    while (true) {
        if (Element->IsBusy && Element->CarId == Key) {//Если имеется такой элемент в хеш-таблице
            return -1;
        }
        if (Element->CarId == Key && Element->DeletedOrNot) { //Если в хеш-таблице есть такой элемент, но он удален
            Element->DeletedOrNot = false;
            return 0;
        }
        if (!Element->IsBusy) { //Если дошли до не занятого элемента
            Element->CarId = Key;
            Element->FileIndex = FileIndex;
            Element->IsBusy = true;
            return 0;
        }
        if (Element->Next == NULL) {
            Element->Next = new ElementOfTable();
        }
        Element = Element->Next;

    }
}

//Возвращает позицию удаленного элемента
int DeleteKey(HashTable& HT, int Key, int LastPosition = 0) {
   
    ElementOfTable* Element = HT.Table[GetHash(HT, Key)];
    ElementOfTable* PreviosElement = NULL;
    int FileIndex;
    while (Element != NULL) {//Пока не прошлись по всему списку
        if (!Element->IsBusy) { //Если дошли до элемента который свободен, то искомого уже не найдем
            return -1;
            break;
        }
        if (Element->CarId == Key) {//Если нашли запись
            if (Element->DeletedOrNot) {//Если она уже удалена
                return -1;
            
            }
            FileIndex = Element->FileIndex;
            Element->FileIndex = LastPosition; //Удаляем запись- добавляем запись вместо последней записи
            Element->DeletedOrNot = true;
            return FileIndex;
            break;
        }
        PreviosElement = Element;
        Element = Element->Next;

    }
}

int GetFileIndexById(HashTable & HT, int Id) {
    ElementOfTable* Element = HT.Table[GetHash(HT, Id)];
    while (Element != NULL) {//Пока не прошлись по всему списку
        if (!Element->IsBusy) {//Если дошли до элемента который свободен, то искомого уже не будет
            cout << "Element with input key not found\n";
            return -1;

        }
        if (Element->CarId == Id && !Element->DeletedOrNot) {//Если нашли элемент с таким же ID и он не удален
            return  Element->FileIndex;
        }
        Element = Element->Next;
    }
    return -1;
}


void PrintElementList(ElementOfTable* Element) {
    while (Element != NULL) {
        if (!Element->IsBusy) {
            cout << "havent values";
            break;
        }
        if (!Element->DeletedOrNot) {
            cout << Element->CarId << ' ';
        }
        Element = Element->Next;
    }
}

void PrintHashTable(HashTable& HT) {
    for (int i = 0; i < HT.Length; i++) {
        cout << "HashTable [" << i << "] : ";
        PrintElementList(HT.Table[i]);
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
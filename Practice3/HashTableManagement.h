#pragma once
#include "BinaryFileFunctions.h"

using namespace std;
struct ElementOfTable {
    int CarId = 0;
    bool IsBusy = false;
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

int GetHash(int Key) {
    return Key % 100;
}





void InsertKey(HashTable& HashTable, int Key) {
    ElementOfTable  * Element = HashTable.Table[GetHash(Key)];
    while (true) {
        if (Element->IsBusy && Element->CarId == Key) {
            cout << "Current element already exist\n";
        }
        if (!Element->IsBusy) {
            Element->CarId = Key;
            Element->IsBusy = true;
            break;
        }
        if (Element->Next == NULL) {
            Element->Next = new ElementOfTable();
        }
        Element = Element->Next;

    }
}

void DeleteKey(HashTable& HashTable, int Key) {
    ElementOfTable* Element = HashTable.Table[GetHash(Key)];
    ElementOfTable* PreviosElement = NULL;
    while (Element != NULL) {
        if (!Element->IsBusy) {
            cout << "Element with input key not found\n";
            break;
        }
        if (Element->CarId == Key) {
            if (PreviosElement == NULL) {
                HashTable.Table[GetHash(Key)] = Element->Next;
                cout << "Element was deleted\n";
                delete(Element);
                break;
            }
            PreviosElement->Next = Element->Next;
            cout << "Element was deleted\n";
            delete(Element);
            break;
        }
        PreviosElement = Element;
        Element = Element->Next;

    }
}


void PrintElementList(ElementOfTable* Element) {
    while (Element != NULL) {
        if (!Element->IsBusy) {
            cout << "havent values";
            break;
        }
        cout << Element->CarId << ' ';
        Element = Element->Next;
    }
}

void PrintHashTable(HashTable& HashTable) {
    for (int i = 0; i < HashTable.Length; i++) {
        cout << "HashTable [" << i << "] : ";
        PrintElementList(HashTable.Table[i]);
        cout << endl;
    }
}
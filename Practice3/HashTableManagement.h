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





int InsertKey(HashTable& HashTable, int Key, int FileIndex = 0) {
    ElementOfTable  * Element = HashTable.Table[GetHash(HashTable, Key)];
    while (true) {
        if (Element->IsBusy && Element->CarId == Key) {//���� ������� ����� ������� � ���-�������
            return -1;
        }
        if (Element->CarId == Key && Element->DeletedOrNot) { //���� � ���-������� ���� ����� �������, �� �� ������
            Element->DeletedOrNot = false;
            return 0;
        }
        if (!Element->IsBusy) { //���� ����� �� �� �������� ��������
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

//���������� ������� ���������� ��������
int DeleteKey(HashTable& HashTable, int Key, int LastPosition = 0) {
   
    ElementOfTable* Element = HashTable.Table[GetHash(HashTable, Key)];
    ElementOfTable* PreviosElement = NULL;
    int FileIndex;
    while (Element != NULL) {//���� �� �������� �� ����� ������
        if (!Element->IsBusy) { //���� ����� �� �������� ������� ��������, �� �������� ��� �� ������
            return -1;
            break;
        }
        if (Element->CarId == Key) {//���� ����� ������
            if (Element->DeletedOrNot) {//���� ��� ��� �������
                return -1;
            
            }
            FileIndex = Element->FileIndex;
            Element->FileIndex = LastPosition; //������� ������- ��������� ������ ������ ��������� ������
            Element->DeletedOrNot = true;
            return FileIndex;
            break;
        }
        PreviosElement = Element;
        Element = Element->Next;

    }
}

int GetFileIndexById(HashTable & HashTable, int Id) {
    ElementOfTable* Element = HashTable.Table[GetHash(HashTable, Id)];
    while (Element != NULL) {//���� �� �������� �� ����� ������
        if (!Element->IsBusy) {//���� ����� �� �������� ������� ��������, �� �������� ��� �� �����
            cout << "Element with input key not found\n";
            return -1;

        }
        if (Element->CarId == Id && !Element->DeletedOrNot) {//���� ����� ������� � ����� �� ID � �� �� ������
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

void PrintHashTable(HashTable& HashTable) {
    for (int i = 0; i < HashTable.Length; i++) {
        cout << "HashTable [" << i << "] : ";
        PrintElementList(HashTable.Table[i]);
        cout << endl;
    }
}
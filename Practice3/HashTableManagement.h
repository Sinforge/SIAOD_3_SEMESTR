#pragma once
#include "BinaryFileFunctions.h"

using namespace std;


//������� ���-�������
struct ElementOfTable {
    int CarId = 0;
    int FileIndex =  0;
};

//���-�������
struct HashTable {
    int Length;
    int CountElements = 0;
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


//��������� ����
int GetHash(HashTable HashTable, int Key) {
    string StringKey = to_string(Key);
    int Hash =0;
    for (int i = 0; i < StringKey.length(); i++) {
        Hash += StringKey[i] - '!';
    }
    return Hash % HashTable.Length;
}


//������� ����� � �������
int InsertKey(HashTable& HT, int Key, int FileIndex = 0) {
    vector<ElementOfTable> Element = HT.Table[GetHash(HT, Key)];
    for (int i = 0; i < Element.size(); i++) {
        if (Element[i].CarId == Key) {
            cout << "Element with such Car Id exist\n";
            return -1;

        }
    }
    double Koef = (double)(HT.CountElements) / (double)(HT.Length);
    if (Koef >= 1.33) {
        ReHashTable(HT);
    }
    ElementOfTable NewElem;
    NewElem.CarId = Key;
    NewElem.FileIndex = FileIndex;
    HT.CountElements++;
    HT.Table[GetHash(HT, Key)].push_back(NewElem);
    
    return 0;
}

//������������� �������
void ReHashTable(HashTable& HT) {
    int NewHashTableLength = HT.Length * 2;
    HashTable NewTable;
    NewTable.CreateTable(NewHashTableLength);
    for (int i = 0; i < HT.Length; i++) {
        for (int j = 0; j < HT.Table[i].size(); j++) {
            InsertKey(NewTable, HT.Table[i][j].CarId, HT.Table[i][j].FileIndex);
        }
    }
    NewTable.CountElements = HT.CountElements;
    HT = NewTable;
    
}




//������� ������� � ���������� ������� ���������� ��������
int DeleteKey(HashTable& HT, int Key, int LastPosition = 0) {
   
    vector<ElementOfTable> Element = HT.Table[GetHash(HT, Key)];
    for (int i = 0; i < Element.size(); i++) {
        if (Element[i].CarId == Key) {
            HT.Table[GetHash(HT, Key)].erase(HT.Table[GetHash(HT, Key)].begin() + i);
            HT.CountElements--;
            cout << "Element successful deleted\n";
            return i;
        }
    }
    cout << "Such element not found\n";
    return -1;
    
}


//�������� ������ ������ � ����� �� �����
int GetFileIndexById(HashTable & HT, int Id) {
    vector<ElementOfTable> Element = HT.Table[GetHash(HT, Id)];
    for (int i = 0; i < Element.size(); i++) {
        if (Element[i].CarId == Id) {
            cout << "Element found on position: " << GetHash(HT, Id) << endl;
            return Element[i].FileIndex;
        }
   }
    cout << "Element not found\n";
    return -1;
}


//����� ����������� ���-�������
void PrintHashTable(HashTable& HT) {
    for (int i = 0; i < HT.Length; i++) {
        cout << "HashTable [" << i << "] : ";
        for (int j = 0; j < HT.Table[i].size(); j++) {
            cout << HT.Table[i][j].CarId << " ";
        }
        cout << endl;
    }
}


//������������ ������� ���-�������
void TestHashTable() {
    int ex_num;
    HashTable HashTable;
    int Key;
    int TableLength;
    cout << "������������ ������� ���-������� �������, ��� ������ ��������������: \n0)����� �� ���������\n1)�������� ���-�������\n2)������� ����� � �������\n3)�������� ����� �� �������\n4)������� �������\n5)����� ���� � �������\n";
    cin >> ex_num;
    while (ex_num) {
        switch (ex_num) {
        case 1:
            cout << "������� ������ �������\n";
            cin >> TableLength;
            HashTable.CreateTable(TableLength);
            break;
        case 2:
            cout << "������� ���� ��� ������� � �������\n";
            cin >> Key;
            InsertKey(HashTable, Key);
            break;
        case 3:
            cout << "������� ����, ������� ������ ������� �� �������\n";
            cin >> Key;
            DeleteKey(HashTable, Key);
            break;
        case 4:
            PrintHashTable(HashTable);
            break;
        case 5:
            cout << "������� ����\n";
            cin >> Key;
            GetFileIndexById(HashTable, Key);
            break;
        default:
            break;
        }
        cout << "������������ ������� ���-������� �������, ��� ������ ��������������: \n0)����� �� ���������\n1)�������� ���-�������\n2)������� ����� � �������\n3)�������� ����� �� �������\n4)������� �������\n5)����� ���� � �������\n";
        cin >> ex_num;
    }
}
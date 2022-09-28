#pragma once
#include "BinaryFileFunctions.h"
#include "HashTableManagement.h"
using namespace std;



void GetRecordAndInsertToHashTable(ifstream &fin, HashTable& HT, int RecordPosition) {
	CarOwner FoundedOwner = GetOwnerInfoByPosition(fin, RecordPosition);
	if (InsertKey(HT, FoundedOwner.CarId, RecordPosition) == -1) {
		cout << "Such record already exist in hash table\n";
	}
	else {
		cout << "Record was successful added\n";
	}
}


void ChangeFileIndex(HashTable& HashTable, int Id, int NewFileIndex) {
	ElementOfTable * Element = HashTable.Table[GetHash(HashTable, Id)];
	while (Element != NULL) {//���� �� �������� �� ����� ������
		if (!Element->IsBusy) {//���� ����� �� �������� ������� ��������, �� �������� ��� �� �����
			cout << "Element with input key not found\n";
		}
		if (Element->CarId == Id && !Element->DeletedOrNot) {//���� ����� ������� � ����� �� ID � �� �� ������
			Element->FileIndex = NewFileIndex;
			break;
		}
		Element = Element->Next;
	}
}

void DeleteRecordFromFileAndTable(fstream& f, HashTable& HashTable, int Key, int RecordCount) {
	
	
	CarOwner LastCarOwnerOnNewPosition = DeleteRecordByFileIndex(f, GetFileIndexById(HashTable, Key)); // ���� ������ ������ � ����� � ��� ������� � �������
																  //�� ������� ������� �������
	
	
	int FileIndex = DeleteKey(HashTable, Key, RecordCount); //������� ������ �� ������� (�������� ������ ���� - ������)
	
	if (FileIndex == -1) {
		cout << "Record not found or already deleted\n";
	}
	else {
		ChangeFileIndex(HashTable, LastCarOwnerOnNewPosition.CarId, FileIndex);
		cout << "Record successful deleted\n";
	}

}

void GetRecordFromHashTable(ifstream& fin, HashTable& HashTable, int Id) {
	int FileIndex = GetFileIndexById(HashTable, Id);
	if (FileIndex == -1) {
		cout << "Record with such id not found or deleted\n";
	}
	return print(GetOwnerInfoByPosition(fin, FileIndex));
}
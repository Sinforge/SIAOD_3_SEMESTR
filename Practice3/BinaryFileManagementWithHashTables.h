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


void DeleteRecordFromFileAndTable(fstream& f, HashTable& HashTable, int Key, int RecordCount) {
	
	
	CarOwner LastCarOwnerOnNewPosition = DeleteRecordByFileIndex(f, GetFileIndexById(HashTable, Key)); // Ищем индекс записи в файле в хеш таблице и удаляем
																  //из файлапо прямому доступу
	
	
	int FileIndex = DeleteKey(HashTable, Key, RecordCount); //Удаляем запись из таблицы (элементу ставим флаг - удален)
	
	if (FileIndex == -1) {
		cout << "Record not found or already deleted\n";
	}
	else {
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
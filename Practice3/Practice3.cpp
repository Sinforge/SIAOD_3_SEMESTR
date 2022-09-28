// Practice3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "BinaryFileFunctions.h"
#include "HashTableManagement.h"
#include "BinaryFileManagementWithHashTables.h"

using namespace std;
int main()
{
	setlocale(LC_ALL, "");
	int ex_num;
	HashTable HashTable;
	int TableLength;
	fstream f;
	ifstream fin;
	int RecordCount = 4;
	ofstream fout;
	CarOwner carOwner;
	string OriginalFileName, NewFileName;
	int Key;
	int PositionInFile;
	cout << "Практическая работа номер 3 \"Внешние структуры данных: текстовый и двоичный файлы.\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Тестирования функций хеш-таблицы\n2)Тестирование функций бинарного файла\n3)Прочитать запись из файла и добавить в хеш-таблицу\n4)Удалить запись из таблицы и файла\n5)Получить запись по ключу\n6)Создать таблицу\n7)Вывести таблицу\n8)Вывести данные бинарного файла\n";
	cin >> ex_num;
	while (ex_num) {
		switch (ex_num) {
			case 1:
				TestHashTable(); // Tested - All good
				break;
			case 2:
				TestBinaryFile(); // Tested - All good
				break;
			case 3:
				cout << "Enter Binary File name and index of record in file\n";
				cin >> OriginalFileName >> PositionInFile;
				fin.open(OriginalFileName, ios::binary | ios::in);
				if (!fin) {
					cout << "file not open or not exist\n";
				}
				GetRecordAndInsertToHashTable(fin, HashTable, PositionInFile);
				fin.close();
				break;
			case 4:
				cout << "Enter Binary File name and Car id to delete\n";
				cin >> OriginalFileName >> Key;
				f.open(OriginalFileName, ios::binary | ios::in | ios::out);
				if (!f) {
					cout << "file not open or not exist\n";
				}
				DeleteRecordFromFileAndTable(f, HashTable, Key, RecordCount);
				f.close();
				break;
			case 5:
				cout << "Enter Binary File name and Car id to find\n";
				cin >> OriginalFileName >> Key;
				fin.open(OriginalFileName, ios::binary | ios::in || ios::out);
				if (!fin) {
					cout << "file not open or not exist\n";
				}
				GetRecordFromHashTable(fin, HashTable, Key);
				fin.close();
				break;
			case 6:
				cout << "Enter length of hash table\n";
				cin >> TableLength;
				HashTable.CreateTable(TableLength);
				break;
			case 7:
				PrintHashTable(HashTable);
				break;
			case 8:
				cout << "Enter Binary FIle name\n";
				cin >> OriginalFileName;
				fin.open(OriginalFileName, ios::binary | ios::in);
				if (!fin) {
					cout << "file not open or not exist\n";
				}
				PrintBinaryFileData(fin);
				fin.close();
				break;
			default:
				return 0;
				break;
			}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Тестирования функций хеш-таблицы\n2)Тестирование функций бинарного файла\n3)Прочитать запись из файла и добавить в хеш-таблицу\n4)Удалить запись из таблицы и файла\n5)Получить запись по ключу\n6)Создать таблицу\n7)Вывести таблицу\n8)Вывести данные бинарного файла\n";
		cin >> ex_num;

		}

}

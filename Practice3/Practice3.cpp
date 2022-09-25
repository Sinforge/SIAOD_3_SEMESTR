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
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание хеш-таблицы\n2)Вставка ключа в таблицу\n3)Удаление ключа из таблицы\n4)Вывести таблицу\n5)Переписать файл из текстового в бинарный\n6)Вставить запись в конец файла\n7)Прочитать запись из файла и записать элемент в таблицу\n8)Удалить запись из таблицы при заданном значении ключа и соответственно из файла.\n9)Вывести данные бинарного файла\n10)Вывести данные записи используя хеш-таблицу\n";
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
			case 5:
				cout << "Enter Original file name and Binary file name\n";
				cin >> OriginalFileName >> NewFileName;
				fin.open(OriginalFileName, ios::in);
				fout.open(NewFileName, ios::out | ios::binary);
				if (!fin || !fout) {
					cout << "file not open or not exist";
				}
				else {
					OverwriteFromTextToBinary(fin, fout);
				}
				fin.close();
				fout.close();
				break;
			case 6:
				cout << "Enter Binary File name\n";
				cin >> OriginalFileName;
				fout.open(NewFileName, ios::binary | ios::app);
				if (!fout) {
					cout << "file not open or not exist\n";
				}
				cout << "Enter CarId, Car Model, OwnerDesctiption and stolen car or not(1 or 0)\n";
				cin >> carOwner.CarId >> carOwner.CarModel >> carOwner.OwnerDescription >> carOwner.IsStolen;
				PushBackRecord(fout, carOwner);
				fout.close();
				break;
			case 7:
				cout << "Enter Binary File name and index of record in file\n";
				cin >> OriginalFileName >> PositionInFile;
				fin.open(OriginalFileName, ios::binary | ios::in);
				if (!fin) {
					cout << "file not open or not exist\n";
				}
				GetRecordAndInsertToHashTable(fin, HashTable, PositionInFile);
				fin.close();
				break;
			case 8:
				cout << "Enter Binary File name and Car id to delete\n";
				cin >> OriginalFileName >> Key;
				f.open(OriginalFileName, ios::binary | ios::in | ios::out);
				if (!f) {
					cout << "file not open or not exist\n";
				}
				DeleteRecordFromFileAndTable(f, HashTable, Key, RecordCount);
				f.close();
				break;
			case 9:
				cout << "Enter Binary File name\n";
				cin >> OriginalFileName;
				fin.open(OriginalFileName, ios::binary | ios::in);
				if (!fin) {
					cout << "file not open or not exist\n";
				}
				PrintBinaryFileData(fin);
				fin.close();
				break;
			case 10:
				cout << "Enter Binary File name and Car id to find\n";
				cin >> OriginalFileName >> Key;
				fin.open(OriginalFileName, ios::binary | ios::in || ios::out);
				if (!fin) {
					cout << "file not open or not exist\n";
				}
				GetRecordFromHashTable(fin, HashTable, Key);
				fin.close();
				break;
			default:
				return 0;
				break;
			}
			cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание хеш-таблицы\n2)Вставка ключа в таблицу\n3)Удаление ключа из таблицы\n4)Вывести таблицу\n5)Переписать файл из текстового в бинарный\n6)Вставить запись в конец файла\n7)Прочитать запись из файла и записать элемент в таблицу\n8)Удалить запись из таблицы при заданном значении ключа и соответственно из файла.\n9)Вывести данные бинарного файла\n10)Вывести данные записи используя хеш-таблицу\n";
			cin >> ex_num;

		}

}

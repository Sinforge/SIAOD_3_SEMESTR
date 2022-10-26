
#include <iostream>
#include "FileManagament.h"
int main()
{
	setlocale(LC_ALL, "");
	int ex_num;
	fstream f;
	ifstream fin;
	ofstream fout;
	CarOwner carOwner;
	string OriginalFileName, NewFileName;
	int Key;
	int PositionInFile;
	cout << "Практическая работа номер 3 \"Применение хеш-таблицы для поиска данных в двоичном файле с записями фиксированной длины\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Тестирования функций хеш-таблицы\n2)Тестирование функций бинарного файла\n3)Прочитать запись из файла и добавить в хеш-таблицу\n4)Удалить запись из таблицы и файла\n5)Получить запись по ключу\n6)Создать таблицу\n7)Вывести таблицу\n8)Вывести данные бинарного файла\n";
	cin >> ex_num;
	while (ex_num) {
		switch (ex_num) {
		case 1:
			cout << "Enter Original file name and Binary file name\n";
			cin >> OriginalFileName >> NewFileName;
			fin.open(OriginalFileName, ios::in);
			fout.open(NewFileName, ios::out | ios::binary);
			if (!fin || !fout) {
				cout << "file not open or not exist";
			}
			else {
				FileManagament::OverwriteFromTextToBinary(fin, fout);
			}
			fin.close();
			fout.close();
			break;
		case 2:
			cout << "Enter Binary file name and Car Id\n";
			cin >> OriginalFileName >> Key;
			fin.open(OriginalFileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file not open or not exist\n";
			}
			else {
				FileManagament::GetOwnerById(fin, Key).print();
			}
			fin.close();
			break;
		case 3:
			cout << "Enter Binary file name and file index\n";
			cin >> OriginalFileName >> PositionInFile;
			fin.open(OriginalFileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file not open or not exist\n";
			}
			else {
				FileManagament::GetOwnerInfoByPosition(fin, PositionInFile).print();
			}
			fin.close();
			break;
		case 4:
			cout << "Enter Binary file name\n";
			cin >> OriginalFileName;
			carOwner = CarOwner();
			cout << "Enter Car Model, Car Owner Desc, Car id\n";
			cin.getline(carOwner.CarModel, 30);
			cin.getline(carOwner.OwnerDescription, 50);
			cin >> carOwner.CarId;
			fout.open(OriginalFileName, ios::out | ios::binary);
			if (!fout) {
				cout << "file not open or not exist\n";
			}	
			else {
				FileManagament::PushBackRecord(fout ,carOwner);
			}
			fout.close();
			break;
		default:
			return 0;
			break;
		}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Тестирования функций хеш-таблицы\n2)Тестирование функций бинарного файла\n3)Прочитать запись из файла и добавить в хеш-таблицу\n4)Удалить запись из таблицы и файла\n5)Получить запись по ключу\n6)Создать таблицу\n7)Вывести таблицу\n8)Вывести данные бинарного файла\n";
		cin >> ex_num;

	}
}


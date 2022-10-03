#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#pragma once
using namespace std;



struct CarOwner {
	int CarId; //номер авто
	char CarModel[30]; // марка автомобиля
	char OwnerDescription[50]; // Сведение о владельце
	bool IsStolen;  // В угоне или нет
};


//Вывод полей структуры
void print(CarOwner carOwner) {
	cout << "\n\nCarId: " << carOwner.CarId << "\n"
		<< carOwner.CarModel << "\n"
		<< carOwner.OwnerDescription << "\n"
		<< "Is stolen? " << carOwner.IsStolen << "\n";
}


//Функция для преобразования текстовых данных из текстового файла в двоичный
void OverwriteFromTextToBinary(ifstream& fin, ofstream& fout) {
	CarOwner carOwner;
	while (!fin.eof()) {
		fin.getline(carOwner.CarModel, 30);
		fin.getline(carOwner.OwnerDescription, 50);
		fin >> carOwner.CarId;
		fin >> carOwner.IsStolen;
		fout.write((char*)&carOwner, sizeof(CarOwner));
		fin.get();
	}

}



//Вывести все записи с бинарного файла
void PrintBinaryFileData(ifstream& fin) {
	CarOwner carOwner;
	while (fin.read((char*)&carOwner, sizeof(CarOwner))) {
		print(carOwner);
	}
}

//Получить запись о владельце по позиции
CarOwner GetOwnerInfoByPosition(ifstream& fin, int Pos) {
	CarOwner carOwner = CarOwner();
	fin.seekg(Pos * sizeof(CarOwner), ios::beg);//Change pointer to record with position pos
	fin.read((char*)&carOwner, sizeof(CarOwner));
	print(carOwner);
	return carOwner;
}


//Удаление записи из файла
void DeleteRecordByKey(fstream& f, int Key) {
	bool RecordFound = false;
	int Position = 0;
	CarOwner carOwner = CarOwner();
	while (f.read((char*)&carOwner, sizeof(CarOwner))) {
		if (carOwner.CarId == Key) {
			RecordFound = true;
			break;
		}
		Position++;

	}
	if (!RecordFound) {
		cout << "Record with input key not found\n";
		return;
	}
	CarOwner LastOwner;

	//Get last record
	f.seekg(4 * sizeof(CarOwner), ios::beg);
	f.read((char*)&LastOwner, sizeof(CarOwner));
	//Put in last record founded record
	f.seekg((-1) * sizeof(CarOwner), ios::cur);
	f.write((char*)&carOwner, sizeof(CarOwner));
	//Put in founded record last record
	f.seekg(Position * sizeof(CarOwner), ios::beg);
	f.write((char*)&LastOwner, sizeof(CarOwner));

}
//Удаление записи из файла по индексу
CarOwner DeleteRecordByFileIndex(fstream& f, int FileIndex) {
	CarOwner LastOwner, carOwner;

	//Get founded record
	f.seekg(FileIndex * sizeof(CarOwner), ios::beg);
	f.read((char*)&carOwner, sizeof(CarOwner));

	//Get last record
	f.seekg(4 * sizeof(CarOwner), ios::beg);
	f.read((char*)&LastOwner, sizeof(CarOwner));
	
	//Put in last record founded record
	f.seekg(4 * sizeof(CarOwner), ios::beg);
	f.write((char*)&carOwner, sizeof(CarOwner));
	//Put in founded record last record
	f.seekg(FileIndex * sizeof(CarOwner), ios::beg);
	f.write((char*)&LastOwner, sizeof(CarOwner));
	return LastOwner;
}

//Добавить запись в конец файла
void PushBackRecord(ofstream& fout, CarOwner carOwner) {
	fout.write((char*)&carOwner, sizeof(CarOwner));
}

//Тестирование функций бинарного файла
void TestBinaryFile() {
	int ex_num;
	fstream f;
	ifstream fin;
	ofstream fout;
	CarOwner carOwner;
	string OriginalFileName, NewFileName;
	int Key;
	int PositionInFile;
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Переписать из текстового в бинарный\n2)Добавить новую запись\n3)Удалить запись\n4)Вывести данные бинарного файла\n5)Вывести запись\n6)Удалить запись по индексу в файле\n";
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
				OverwriteFromTextToBinary(fin, fout);
			}
			fin.close();
			fout.close();
			break;
		case 2:
			cout << "Enter Binary File name\n";
			cin >> OriginalFileName;
			fout.open(OriginalFileName, ios::binary | ios::app);
			if (!fout) {
				cout << "file not open or not exist\n";
			}
			cout << "Enter CarId, Car Model, OwnerDesctiption and stolen car or not(1 or 0)\n";
			cin >> carOwner.CarId;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.getline(carOwner.CarModel, 30);
			cin.getline(carOwner.OwnerDescription, 50);
			cin >> carOwner.IsStolen;
			PushBackRecord(fout, carOwner);
			fout.close();
			break;
		case 3:
			cout << "Enter Binary file name and key\n";
			cin >> OriginalFileName >> Key;
			f.open(OriginalFileName, ios::binary | ios::in | ios::out);
			if (!f) {
				cout << "file not open\n";
			}
			else { DeleteRecordByKey(f, Key); }
			f.close();
			break;
		case 4:
			cout << "Enter Binary File name\n";
			cin >> OriginalFileName;
			fin.open(OriginalFileName, ios::binary | ios::in);
			if (!fin) {
				cout << "file not open or not exist\n";
			}
			PrintBinaryFileData(fin);
			fin.close();
			break;
		case 5:
			cout << "Enter Binary File name and Position in file\n";
			cin >> OriginalFileName >> PositionInFile;
			fin.open(OriginalFileName, ios::binary | ios::in);
			if (!fin) {
				cout << "file not open or not exist\n";
			}
			print(GetOwnerInfoByPosition(fin, PositionInFile));
			fin.close();
			break;
		case 6:
			cout << "Enter Binary File name and Position in file\n";
			cin >> OriginalFileName >> PositionInFile;
			f.open(OriginalFileName, ios::binary | ios::in | ios::out);
			if (!f) {
				cout << "file not open or not exist\n";
			}
			DeleteRecordByFileIndex(f, PositionInFile);
			f.close();
			break;
		default:
			return;
			break;
		}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Переписать из текстового в бинарный\n2)Добавить новую запись\n3)Удалить запись\n4)Вывести данные бинарного файла\n5)Вывести запись\n6)Удалить запись по индексу в файле\n";
		cin >> ex_num;

	}

}
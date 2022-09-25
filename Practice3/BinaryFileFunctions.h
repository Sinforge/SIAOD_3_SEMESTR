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


}

CarOwner DeleteRecordByFileIndex(fstream& f, int FileIndex) {
	CarOwner LastOwner, carOwner;

	//Get founded record
	f.seekg(FileIndex * sizeof(CarOwner), ios::beg);
	f.read((char*)&carOwner, sizeof(CarOwner));

	//Get last record
	f.seekg(3 * sizeof(CarOwner), ios::beg);
	f.read((char*)&LastOwner, sizeof(CarOwner));
	
	//Put in last record founded record
	f.seekg(3 * sizeof(CarOwner), ios::beg);
	f.write((char*)&carOwner, sizeof(CarOwner));
	//Put in founded record last record
	f.seekg(FileIndex * sizeof(CarOwner), ios::beg);
	f.write((char*)&LastOwner, sizeof(CarOwner));
	return LastOwner;
}

void PushBackRecord(ofstream& fout, CarOwner carOwner) {
	fout.write((char*)&carOwner, sizeof(CarOwner));
}

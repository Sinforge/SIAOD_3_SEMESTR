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
	//Вывод полей структуры
	void print() {
		cout << "\n\nCarId: " << CarId << "\n"
			<< CarModel << "\n"
			<< OwnerDescription << "\n";
	}
};





static class FileManagament {
public:
	//Функция для преобразования текстовых данных из текстового файла в двоичный
	static void OverwriteFromTextToBinary(ifstream& fin, ofstream& fout) {
		CarOwner carOwner;
		while (!fin.eof()) {
			fin.getline(carOwner.CarModel, 30);
			fin.getline(carOwner.OwnerDescription, 50);
			fin >> carOwner.CarId;
			fout.write((char*)&carOwner, sizeof(CarOwner));
			fin.get();
		}

	}

	//Получить запись о владельце по позиции
	static CarOwner GetOwnerInfoByPosition(ifstream& fin, int Pos) {
		CarOwner carOwner = CarOwner();
		fin.seekg(Pos * sizeof(CarOwner), ios::beg);//Change pointer to record with position pos
		fin.read((char*)&carOwner, sizeof(CarOwner));
		return carOwner;
	}
	static CarOwner GetOwnerById(ifstream& fin, int id) {
		CarOwner carOwner;
		while (fin.read((char*)&carOwner, sizeof(CarOwner))) {
			if (carOwner.CarId == id) {
				return carOwner;
			}
		}
		return CarOwner();

	}
	//Добавить запись в конец файла
	static void PushBackRecord(ofstream& fout, CarOwner carOwner) {
		fout.write((char*)&carOwner, sizeof(CarOwner));
	}
};

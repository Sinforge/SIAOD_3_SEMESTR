// Practice2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "FileFunctions.h"
#include "BinaryFileFucntions.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "");
	int ex_num;
	fstream f;
	ifstream fin;
	ofstream fout;
	string FileName;
	string NewFileName;
	string OriginalFileName;
	vector<string> stoledcars;
	vector<int> MassiveOfNumbers;
	string Text;
	int Pos;
	cout << "Практическая работа номер 2 \"Внешние структуры данных: текстовый и двоичный файлы.\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке\n2)Вывод содержимого текстового файла\n3)Добавление новой строки в конец файла;\n4)Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение\n5)Определить количество чисел в файле\n6)Переписать данные из одного файла в другой\n7)Переписать данные из текстового файла в бинарный\n8)Переписать данные из бинарного файла в текстовый\n9)Вывести данные бинарного файла\n10)доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле\n11)удаление записи с заданным значением ключа\n12)Список автомобилей, числящихся в угоне\n13)Установить факт угона автомобиля с заданным номером.\n14)Получить все числа из файла\n";
	cin >> ex_num;
	while (ex_num) {
		switch (ex_num) {
		case 1:
			//First
			cout << "Ex.1\n";
			cout << "Enter file name\n";
			cin >> FileName;
			fout.open(FileName, ios::out);
			if (!fout) {
				cout << "file not open";
				fout.close();
			}
			else {
				CreateFile(fout);
			}
			fout.close();
			break;

		case 2:
			//Second
			cout << "Ex.2\n";
			cout << "Enter file name\n";
			cin >> FileName;
			fin.open(FileName, ios::in);
			if (!fin) {
				cout << "file not open or not exist";
			}
			PrintFile(fin);
			fin.close();
			break;

		case 3:
			//Third
			std::cout << "Ex.3\n";
			cout << "Enter filename\n";
			cin >> FileName;
			cout << "Enter text,which u want insert to the end: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, Text);
			fout.open(FileName, ios::app | ios::out);
			if (!fout) {
				cout << "file not open or not exist";
			}
			else { WriteToLastLine(fout, Text); }
			fout.close();
			break;

		case 4:
			//Fouth
			cout << "Ex.4\n";
			cout << "Enter file name and position of number\n";
			cin >> FileName >> Pos;
			fin.open(FileName, ios::in);
			if (!fin) {
				cout << "file not open or not exist";
			}
			else {
				cout << "Number on position(0 - equals not found): " << GetNumberByPos(fin, Pos) << endl;
			}
			fin.close();

			break;

		case 5:
			//Fifth
			cout << "Ex.5\n";
			cout << "Enter file name\n";
			cin >> FileName;
			fin.open(FileName, ios::in);
			if (!fin) {
				cout << "file not open or not exist";
			}
			else {
				cout << "Count numbers = " << GetCountNumbers(fin) << endl;
			}
			fin.close();
			break;
		case 6:
			cout << "Ex.6\n";
			cout << "Enter Original file name and new file name\n";
			cin >> OriginalFileName >> NewFileName;
			fin.open(OriginalFileName, ios::in);
			fout.open(NewFileName, ios::out);
			if (!fin || !fout) {
				cout << "file not open or not exist";

			}
			else {
				FileOverwrite(fin, fout);
			}
			fin.close();
			fout.close();
			break;
		case 7:
			cout << "Ex.7\n";
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
		case 8:
			cout << "Ex.8\n";
			cout << "Enter Binary file name and Text file name\n";
			cin >> OriginalFileName >> NewFileName;
			fin.open(OriginalFileName, ios::in | ios::binary);
			fout.open(NewFileName, ios::out);
			if (!fin || !fout) {
				cout << "file not open or not exist";
			}
			else {
				OverwriteFromBinaryToText(fin, fout);
			}
			fin.close();
			fout.close();
			break;
		case 9:
			cout << "Ex.9\n";
			cout << "Enter Binary file name\n";
			cin >> FileName;
			fin.open(FileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file not open";
			}
			else {
				PrintBinaryFileData(fin);
			}
			fin.close();
			break;
		case 10:
			cout << "Ex.10\n";
			cout << "Enter Binary file name and position\n";
			cin >> FileName >> Pos;
			fin.open(FileName, ios::binary | ios::in);
			if (!fin) {
				cout << "file not open";
			}
			else {
				GetOwnerInfoByPosition(fin, Pos);
			}
			fin.close();
			break;
		case 11:
			cout << "Ex.11\n";
			cout << "Enter Binary file name and key\n";
			cin >> FileName >> Pos;
			f.open(FileName, ios::binary | ios::in | ios::out);
			if (!f) {
				cout << "file not open\n";
			}
			else { DeleteRecord(f, Pos); }
			f.close();
			break;
		case 12:
			cout << "Ex.12\n";
			cout << "Enter Binary fila name\n";
			cin >> FileName;
			fin.open(FileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file is not open";
			}
			else {
				stoledcars = GetStoledCars(fin);
				cout << "Stoled cars(Car id, Car Model): \n";
				for (int i = 0; i < stoledcars.size(); i++) {
					cout << stoledcars.at(i) << endl;
				}
			}
			fin.close();
			break;
		case 13:
			cout << "Ex.13\n";
			cout << "Enter Binary file name and key\n";
			cin >> FileName >> Pos;
			fin.open(FileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file not open\n";
				return 0;
			}
			else {
				if (CarStoledOrNot(fin, Pos)) {
					cout << "Car is stoled\n";
				}
				else {
					cout << "Car is not stoled\n";
				}
			}
			fin.close();
			break;
		case 14:
			cout << "Ex.14\n";
			cout << "Enter filename\n";
			cin >> FileName;
			fin.open(FileName, ios::in);
			MassiveOfNumbers = GetAllNumbersFromFile(fin);
			for (int i = 0; i < MassiveOfNumbers.size(); i++) {
				cout << MassiveOfNumbers.at(i) << " ";
			}
			break;
			
		default:
			return 0;
			break;
		}
		cout << "\n\nВведите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке\n2)Вывод содержимого текстового файла\n3)Добавление новой строки в конец файла;\n4)Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение\n5)Определить количество чисел в файле\n6)Переписать данные из одного файла в другой\n7)Переписать данные из текстового файла в бинарный\n8)Переписать данные из бинарного файла в текстовый\n9)Вывести данные бинарного файла\n10)доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле\n11)удаление записи с заданным значением ключа\n12)Список автомобилей, числящихся в угоне\n13)Установить факт угона автомобиля с заданным номером.\n14)Получить все числа из файла\n";
		cin >> ex_num;
		fout.close();
		fin.close();
		f.close();

	}


}


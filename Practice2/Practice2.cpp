// Practice2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void CreateFile(string FileName);
void PrintFile(string FileName);
void WriteToLastLine(string FileName, string Text);
int GetNumberByPos(string FileName, int Pos);
int GetCountNumbers(string FileName);


int main()
{
	setlocale(LC_ALL, "");
	int ex_num;
	string FileName;
	string Text;
	int Pos;
	cout << "Практическая работа номер 2 \"Внешние структуры данных: текстовый и двоичный файлы.\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке\n2)Вывод содержимого текстового файла\n3)Добавление новой строки в конец файла;\n4)Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение\n5)Определить количество чисел в файле\n\n";
	cin >> ex_num;
	while (ex_num) {
		switch (ex_num) {
		case 1:
			//First
			cout << "Ex.1\n";
			cout << "Enter file name\n";
			cin >> FileName;
			CreateFile(FileName);
			break;

		case 2:
			//Second
			cout << "Ex.2\n";
			cout << "Enter file name\n";
			cin >> FileName;
			PrintFile(FileName);
			break;

		case 3:
			//Third
			std::cout << "Ex.3\n";
			cout << "Enter filename";
			cin >> FileName;
			cout << "Enter text,which u want insert to the end";
			getline(cin, Text);
			WriteToLastLine(FileName, Text);
			break;

		case 4:
			//Fouth
			cout << "Ex.4\n";
			cout << "Enter file name and position of number\n";
			cin >> FileName >> Pos;
			cout << "Number on position(0 - equals not found): " << GetNumberByPos(FileName, Pos) << endl;
			break;

		case 5:
			//Fifth
			cout << "Ex.5\n";
			cout << "Enter file name\n";
			cin >> FileName;
			cout << "Count numbers = " << GetCountNumbers(FileName) << endl;
			break;
		default:
			return 0;
			break;
		}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке\n2)Вывод содержимого текстового файла\n3)Добавление новой строки в конец файла;\n4)Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение\n5)Определить количество чисел в файле\n\n";
		cin >> ex_num;

	}
}


void CreateFile(string FileName) {
	ofstream fout(FileName, ios::out);
	if (!fout) {
		cout << "file not open";
		return;
	}
	fout << 123 << ' ' << 42 << endl;
	fout << 32 << ' ' << 24 << ' ' << 414 << endl;
	fout << 23 << ' ' << 204 << ' ' << 1401 << ' ' << 2041;
	fout.close();
}

void PrintFile(string FileName) {
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		return;
	}
	string line;
	while (!fin.eof()) {
		getline(fin, line);
		cout << line << endl;
	}
	if (!fin.good()) {
		cout << "Errors:\n";
		cout << "Failbit or hardfail: " << fin.bad() ? "Formatting error or Hardware malfunctions\n" : "All good\n";
		cout << "BadBit: " << fin.badbit ? "Hardware malfunctions\n" : "All good\n";
		



	}
	fin.close();

}

void WriteToLastLine(string FileName, string Text) {
	ofstream fout(FileName, ios::app);
	if (!fout) {
		cout << "file not open or not exist";
		return;
	}
	fout << Text;
	fout.close();
}

int GetNumberByPos(string FileName,int Pos) {
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		fin.close();
		return 0;
	}
	int CurrentPos = 0;
	int Number;
	while (!fin.eof()) {
		fin >> Number;
		if (CurrentPos == Pos) {
			return Number;
		}
		CurrentPos++;
	}
	cout << "Number with current position not exist\n";
	return 0;

}

int GetCountNumbers(string FileName) {
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		fin.close();
		return 0;
	}
	int Counter = 0;
	int Number;
	while (!fin.eof()) {
		fin >> Number;
		Counter++;
	}
	fin.close();
	return Counter;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

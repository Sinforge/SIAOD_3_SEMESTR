// Practice2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "FileFunctions.h"
using namespace std;
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
			cout << "Enter filename\n";
			cin >> FileName;
			cout << "Enter text,which u want insert to the end: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
		cout << "\n\nВведите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке\n2)Вывод содержимого текстового файла\n3)Добавление новой строки в конец файла;\n4)Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение\n5)Определить количество чисел в файле\n\n";
		cin >> ex_num;

	}
}

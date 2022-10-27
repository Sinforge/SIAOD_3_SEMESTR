
#include <iostream>
#include "FileManagament.h"
#include "BinaryTree.h"
int main()
{
	setlocale(LC_ALL, "");
	int ex_num;
	fstream f;
	ifstream fin;
	ofstream fout;
	BinaryTree * binTree = NULL;
	CarOwner carOwner;
	string OriginalFileName, NewFileName;
	TreeNode* foundedNode;
	int Key;
	int PositionInFile;
	cout << "Практическая работа номер 5 \"Сбалансированные деревья поиска (СДП) и их применение для поиска данных в файле\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Переписать из текстового файла в бинарный\n2)Найти запись в файле по Id линейным поиском\n3)Найти запись по индексу\n4)Добавить новую запись в файл\n5)Построить бинарное дерево по файлу\n6)Добавить элемент в дерево\n7)Поиск элемента по ключу\n8)Удаление элемента по ключу\n9)Вывести бинарное дерево\n";
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
		case 5:
			cout << "Enter Binart file name to create bin tree\n";
			cin >> OriginalFileName;
			fin.open(OriginalFileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file not open or not exist\n";
			}
			else {
				binTree = new BinaryTree(fin);
			}
			fin.close();
			break;
		case 6:
			cout << "Enter id and file index of new node\n";
			cin >> Key >> PositionInFile;
			binTree->InsertNode(Key, PositionInFile);
			break;
		case 7:
			cout << "Enter id of car\n";
			cin >> Key;
			foundedNode = binTree->FindNodeById(Key);
			cout << foundedNode->getCarId() << ' ' << foundedNode->getFileIndex();
			break;
		case 8:
			cout << "Enter id of car to delete\n";
			cin >> Key;
			binTree->DeleteNodeById(Key);
			break;
		case 9:
			binTree->PrintTree();
			break;
		default:
			return 0;
			break;
		}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Переписать из текстового файла в бинарный\n2)Найти запись в файле по Id линейным поиском\n3)Найти запись по индексу\n4)Добавить новую запись в файл\n5)Построить бинарное дерево по файлу\n6)Добавить элемент в дерево\n7)Поиск элемента по ключу\n8)Удаление элемента по ключу\n9)Вывести бинарное дерево\n\n";
		cin >> ex_num;

	}
}



#include <iostream>
#include "FileManagament.h"
#include "BinaryTree.h"
#include "RandomTree.h"
#include <random>
#include <chrono>
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
	RandomTree::TreeNode* foundNode; 
	chrono::system_clock::time_point start;
	chrono::system_clock::time_point end;
	int Key;
	int PositionInFile;
	RandomTree * randTree = new RandomTree();
	cout << "Практическая работа номер 5 \"Сбалансированные деревья поиска (СДП) и их применение для поиска данных в файле\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Переписать из текстового файла в бинарный\n2)Найти запись в файле по Id линейным поиском\n3)Найти запись по индексу\n4)Добавить новую запись в файл\n5)Построить бинарное дерево по файлу\n6)Добавить элемент в дерево\n7)Поиск элемента по ключу\n8)Удаление элемента по ключу\n9)Вывести бинарное дерево\n10)Создать рандомизированное дерево\n11)Вставить новый элемент в рандомизированное дерево\n12)Найти элемент\n13)Вывести рандомизированное дерево\n14)Удалить элемент из рандомизированного дерева\n15)Создать большой файл для теста\n16)Линайный поиск по файлу теста\n";
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
			cout << "Enter  Car Model, Car Owner Desc,Car id\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.getline(carOwner.CarModel, 30);
			cin.getline(carOwner.OwnerDescription, 50);
			cin >> carOwner.CarId;
			fout.open(OriginalFileName, ios::app | ios::binary);
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
			start = chrono::system_clock::now();
			foundedNode = binTree->FindNodeById(Key);
			end = chrono::system_clock::now();
			cout << "Время выполенния: " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
			cout << foundedNode->getCarId() << ' ' << foundedNode->getFileIndex() << endl;
			break;
		case 8:
			cout << "Enter id of car to delete\n";
			cin >> Key;
			binTree->DeleteNodeById(Key);
			break;
		case 9:
			binTree->PrintTree();
			break;
		case 10:
			cout << "Enter Binart file name to create random tree\n";
			cin >> OriginalFileName;
			fin.open(OriginalFileName, ios::in | ios::binary);
			if (!fin) {
				cout << "file not open or not exist\n";
			}
			else {
				randTree = new RandomTree(fin);
			}
			fin.close();
			break;
		case 11:
			cout << "Enter id and file index of new node\n";
			cin >> Key >> PositionInFile;
			randTree->InsertNode(randTree->TopNode, Key, PositionInFile);
	

			break;
		case 12:
			cout << "Enter id of car\n";
			cin >> Key;
			start = chrono::system_clock::now();
			foundNode = randTree->FindById(randTree->TopNode, Key);
			end = chrono::system_clock::now();
			cout << "Время выполенния: " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
			cout << foundNode->CarId << ' ' << foundNode->FileIndex;
			break;
		case 13:
			randTree->PrintTree();
			break;
		case 14:
			cout << "Enter id of car to delete\n";
			cin >> Key;
			if (randTree->TopNode->CarId == Key) {
				randTree->TopNode = randTree->Delete(randTree->TopNode, Key);
			}
			else {
				randTree->Delete(randTree->TopNode, Key);
			}
			break;
		case 15:
			cout << "Creating test.txt file....\n";
			fout.open("test.txt", ios::app);
			if (!fout) {
				cout << "Error with test.txt\n";
			}
			else {
				for (int i = 0; i < 100000; i++) {
					int randomInt = rand();
					fout << ("Car" + to_string(randomInt));
					fout << "\nInfo.....\n";
					fout << randomInt;
					if (i != 99999) {
						fout << "\n";
					}
				}

			}
			fout.close();
			break;
		case 16:
			cout << "Enter id to linear search\n";
			cin >> Key;
			fin.open("test.bin", ios::binary);
			start = chrono::system_clock::now();
			carOwner = FileManagament::GetOwnerById(fin, Key);
			cout << "Founded id: " << carOwner.CarId;
			end = chrono::system_clock::now();
			cout << "Время выполенния: " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
			fin.close();
			break;
		
		default:
			return 0;
			break;
		}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Переписать из текстового файла в бинарный\n2)Найти запись в файле по Id линейным поиском\n3)Найти запись по индексу\n4)Добавить новую запись в файл\n5)Построить бинарное дерево по файлу\n6)Добавить элемент в дерево\n7)Поиск элемента по ключу\n8)Удаление элемента по ключу\n9)Вывести бинарное дерево\n10)Создать рандомизированное дерево\n11)Вставить новый элемент в рандомизированное дерево\n12)Найти элемент\n13)Вывести рандомизированное дерево\n14)Удалить элемент из рандомизированного дерева\n15)Создать большой файл для теста\n16)Линайный поиск по файлу теста\n";
		cin >> ex_num;

	}
}


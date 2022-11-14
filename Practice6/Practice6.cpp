// Practice6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Graph.h"
int main()
{
	setlocale(LC_ALL, "");
	Graph graph;
	int ex_num;
	int connectionId;
	int connectionId2;
	int countConnections;
	int connectionLength;
	vector<pair<int, int>> connectionsList = vector<pair<int, int>>();

	cout << "Практическая работа номер 6 \"Основные алгоритмы работы с графами.\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создать граф\n2)Добавить узел с одной связью\n3)Создать узел с несколькими связями\n4)Добавить новую связь между узлами\n5)Найти диаметр графа\n6)Получить остовное дерево\n7)Вывести граф\n";
	cin >> ex_num;
	while (ex_num) {
		switch (ex_num) {
		case 1:
			graph = Graph();
			cout << "\nGraph is created\n";
			break;
		case 2:
			cout << "Enter connection Id and connection Length\n";
			cin >> connectionId;
			cin >> connectionLength;
			graph.AddNewNode(make_pair(connectionId, connectionLength));
			cout << "Node is added\n";
			break;
		case 3:
			cout << "Enter how much connections node will be have\n";
			connectionsList = vector<pair<int, int>>();

			cin >> countConnections;
			for (int i = 0; i < countConnections; i++) {
				cout << "Enter connection Id and connection Length\n";
				cin >> connectionId;
				cin >> connectionLength;
				connectionsList.push_back(make_pair(connectionId, connectionLength));
			}
			graph.AddNewNode(connectionsList);
			cout << "Node is added\n";
			break;
		case 4:
			cout << "Enter two nodes id and length\n";
			cin >> connectionId >> connectionId2 >> connectionLength;
			graph.AddConnection(connectionId, make_pair(connectionId2, connectionLength));
			cout << "Connections is added\n";
			break;
		case 5:
			cout << "Diameter equals: " << graph.FindDiameter() << endl;
			break;
		case 6:
			graph.PrimAlgorithm().PrintGraph();
			break;
		case 7:
			graph.PrintGraph();
			break;



		default:
			return 0;
			break;
		}
		cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создать граф\n2)Добавить узел с одной связью\n3)Создать узел с несколькими связями\n4)Добавить новую связь между узлами\n5)Найти диаметр графа\n6)Получить остовное дерево\n7)Вывести граф\n";
		cin >> ex_num;
	}
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

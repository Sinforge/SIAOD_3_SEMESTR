// Practice8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "BackpackTask.h"
#include <string>
using namespace std;
int main()
{
	string itemName;
	int weight;
	int price;
	int capacityBackpack;
	int countItems;

	vector<Item*> items = vector<Item*>();
	cout << "Enter how many items we have\n";
	cin >> countItems;
	for (int i = 0; i < countItems; i++) {
		cout << "Enter Name, Weight and Price of item\n";
		cin >> itemName >> weight >> price;
		items.push_back(new Item(itemName, weight, price));
	}
	cout << "Enter capacity of backpack\n";
	cin >> capacityBackpack;
	cout << "Result:\n";
	vector<Item*> result = SolveBackpackTask(items, capacityBackpack);
	if (!result.empty()) {
		for (auto item : result) {
			item->Print();
		}
	}
	else {
		cout << "\nNone of the items fit in the bag.\n";
	}
}


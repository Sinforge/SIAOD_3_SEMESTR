#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Item {
public:
	string name; // имя
	int weight; //вес
	int price; //цена
	Item(string name, int weight, int price) {
		this->name = name;
		this->weight = weight;
		this->price = price;
	}
	void Print() {
		cout << "Name: " << name << "; Weight: " << weight << "; Price: " << price << endl;
	}
};

struct Backpack {
	vector<Item*> items;
	int totalPrice;
	Backpack(vector<Item*> items, int totalPrice) {
		this->items = items;
		this->totalPrice = totalPrice;
	}
};
vector<Item*> SolveBackpackTask(vector<Item*> items, int capacity) {
	vector<vector<Backpack*>> backpackMas = vector<vector<Backpack*>>(items.size() + 1);
	for (int i = 0; i < items.size()+1; i++) {
		backpackMas[i] = vector<Backpack*>(capacity + 1);
	}


	for(int i =0 ; i < items.size() + 1; i++) {
		for (int j = 0; j < capacity + 1; j++) {
			if (i == 0 || j == 0) {
				backpackMas[i][j] = new Backpack(vector<Item*>(), 0);
			}
			else if (i == 1) {
				backpackMas[i][j] = items[0]->weight <= j
					? new Backpack(vector<Item*>{items[0]}, items[0]->price)  // добавляем первый предмет из рюкзака
					: new Backpack(vector<Item*>(), 0); // создаем пустой рюкзак

			}
			else {
				if (items[i - 1]->weight > j) backpackMas[i][j] = backpackMas[i - 1][j];

				else {
					int newPrice = items[i - 1]->price + backpackMas[i - 1][j - items[i - 1]->weight]->totalPrice;
					if (backpackMas[i - 1][j]->totalPrice > newPrice) {
						backpackMas[i][j] = backpackMas[i - 1][j];
					}
					else {
						vector<Item*> concatVector = vector<Item*>(backpackMas[i-1][j-items[i-1]->weight]->items);
						concatVector.push_back(items[i - 1]);
						backpackMas[i][j] = new Backpack(concatVector, newPrice);
					}

				}
			}
			
		}
	}
	int maxPrice = 0;
	vector<Item*> maxItems;
	for (int i = 1; i < items.size() + 1; i++) {
		if (backpackMas[i][capacity]->totalPrice > maxPrice) {
			maxPrice = backpackMas[i][capacity]->totalPrice;
			maxItems = backpackMas[i][capacity]->items;
		}
	}
	return maxItems;
}


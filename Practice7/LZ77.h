#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

class Dictinary {
private:
	string Data = new char[8];
public:
	void addData(string newData) {
		this->Data = Data.substr(newData.length()) + newData;
	}
};

string LZ77(string input, int option)
{
	vector<tuple<int, int, char>> codes = vector<tuple<int, int, char>>();
	tuple<int, int, char> code;

	string dict = new char[8];
	dict[7] = input[0];

	string buffer = input.substr(0, 5);
	size_t buffetStart = 0;
	vector<int> foundedStart = vector<int>();
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i] == )
	}
	
}
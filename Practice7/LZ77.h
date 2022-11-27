#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

class Dictinary {
private:
	string Data = "________";
public:
	void addData(string newData) {
		this->Data = Data.substr(newData.length()) + newData;
	}
	void addData(char newData) {
		this->Data = Data.substr(1) + newData;
	}
	string getData() {
		return Data;
	}
};

vector<tuple<int, int, char>> LZ77(string input)
{
	vector<tuple<int, int, char>> codes = vector<tuple<int, int, char>>();

	Dictinary dict = Dictinary();
	dict.addData(input[0]);
	codes.push_back(tuple<int, int, char> {0, 0, input[0]});
	string buffer = input.substr(1, 5);
	int bufferEnd = 6;
	while (buffer != "" && !buffer.empty()) {
		vector<int> foundedStart = vector<int>();
		for (int i = 0; i < dict.getData().size(); i++) {
			if (buffer[0] == dict.getData()[i]) {
				foundedStart.push_back(i);
			}
		}
		int maxLengthIndex = -1;
		int maxLength = 0;
		char maxLengthChar;
		int currentLength = 0;
		if (foundedStart.size() != 0) {
			for (auto start : foundedStart) {
				int i = 0;
				for (int j = start; j < dict.getData().size(); j++) {
					if (buffer[i] == dict.getData()[j]) {
						currentLength += 1;
					}
					else {
						if (currentLength >= maxLength) {
							maxLength = currentLength;
							maxLengthIndex = start;
							maxLengthChar = buffer[i];
							break;
						}
						currentLength = 0;
					}
					i++;
				}
				if (currentLength >= maxLength) {
					maxLength = currentLength;
					maxLengthIndex = start;
					maxLengthChar = i<buffer.size() ? buffer[i] : buffer[0];
					break;
				}
			}
			codes.push_back(tuple<int, int, char> {maxLengthIndex, maxLength, maxLengthChar});
			if (bufferEnd <= input.size()) {
				dict.addData(buffer.substr(0, maxLength + 1));
				buffer = buffer.substr(maxLength + 1) + input.substr(bufferEnd, maxLength + 1);
				bufferEnd += maxLength + 1;
			}
			else {
				buffer = "";
			}
			
		}
		else {
			codes.push_back(tuple<int, int, char> {0, 0, buffer[0]});
			dict.addData(buffer[0]);
			buffer = buffer.substr(1) + input.substr(bufferEnd, 1);
			bufferEnd += 1;
		}
	}
	return codes;
	
}
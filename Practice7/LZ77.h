#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
using namespace std;

class Dictionary {
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

	Dictionary dict = Dictionary();
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
							if (currentLength == 5) {
								maxLengthChar = input[bufferEnd];
								bufferEnd++;
							}
							currentLength = 0;
							break;
						}
						currentLength = 0;
					}
					i++;
				}
				if (currentLength != 0) {
					if (currentLength >= maxLength) {
						maxLength = currentLength;
						maxLengthIndex = start;
						maxLengthChar = buffer[i];
						currentLength = 0;
					}
					break;
				}
			}
			codes.push_back(tuple<int, int, char> {maxLengthIndex, maxLength, maxLengthChar});
			if (bufferEnd <= input.size()) {
				if (maxLength == 5) {
					dict.addData(buffer + maxLengthChar);
				}
				else {
					dict.addData(buffer.substr(0, maxLength + 1));
				}
				if (input.size() - bufferEnd < 5) {
					buffer = buffer.substr(maxLength+1 > 5?5:maxLength+1) + input.substr(bufferEnd, input.size() - bufferEnd);
				}
				else {
					buffer = buffer.substr(maxLength + 1) + input.substr(bufferEnd, maxLength + 1);
				}
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
int findString(string str, vector<string> dictionary) {
	int index = -1;
	for (int i = 0; i < dictionary.size(); i++) {
		if (dictionary.at(i) == str) {
			return i + 1;
		}
	}
	return index;
}
vector<pair<int, char>> LZ78(string input) {
	int currentIndex = 1;
	string oneChar = "";
	oneChar += input[0];
	vector<string> dictionary = vector<string>();
	vector<pair<int, char>> codes = vector<pair<int, char>>();
	codes.push_back(pair<int, char> {0, input[0]});
	dictionary.push_back(oneChar);
	string currentStr;
	int dictionaryIndex;
	while (currentIndex < input.size()) {
		int dictionaryIndex = 0;
		currentStr = "";
		currentStr += input[currentIndex];


		while (currentIndex < input.size() && findString(currentStr, dictionary) != -1) {
			dictionaryIndex = findString(currentStr, dictionary);
			currentIndex++;
			currentStr += input[currentIndex];
		}


		codes.push_back(pair<int, char> {dictionaryIndex, currentStr.back()});
		dictionary.push_back(currentStr);
		currentIndex++;
	}
	return codes;
} 
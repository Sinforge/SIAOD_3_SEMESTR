#pragma once
#include <string>
#include <iostream>
using namespace std;

pair<string, float> compress(string str) {
	string result = "";
	int counter = 1;
	for (int i = 1; i < str.length(); i++) {
		if (str[i] == str[i - 1]) {
			counter++;
			continue;
		}
		result += str[i - 1] + to_string(counter);
		counter = 1;
	}
	if (str[str.length() - 1] != str[str.length() - 2]) {
		result = result + str[str.length()-1] + "1";
	}
	else {
		result = result + str[str.length() - 1] + to_string(counter);
	}
	return pair<string, float> {result, (float)str.length() / (float)result.length()};
}
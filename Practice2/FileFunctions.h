#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#pragma once

void CreateFile(string FileName) {
	ofstream fout(FileName, ios::out);
	if (!fout) {
		cout << "file not open";
		return;
	}
		int CountLines = (rand() % 10) + 1;
		for (int i = 0; i < CountLines; i++) {
			int CountNumbers = (rand() % 10) + 1;
			for (int j = 0; j < CountNumbers; j++) {
				fout << rand() % 100 << ' ';
			}
			if (i != CountLines - 1) {
				fout << '\n';
			}
		}
	
	fout.close();

}

void PrintFile(string FileName) {
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		return;
	}
	string line;
	while (!fin.eof()) {
		getline(fin, line);
		cout << line << endl;
	}
	
	fin.close();

}

void WriteToLastLine(string FileName, string Text) {
	ofstream fout(FileName, ios::app);
	if (!fout) {
		cout << "file not open or not exist";
		return;
	}
	fout << "\n" << Text;
	
	fout.close();
}

int GetNumberByPos(string FileName, int Pos) {
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		fin.close();
		return 0;
	}
	int CurrentPos = 0;
	int Number;
	while (!fin.eof()) {
		fin >> Number;
		if (CurrentPos == Pos) {
			return Number;
		}
		CurrentPos++;
	}
	
	cout << "Number with current position not exist\n";
	fin.close();
	return 0;

}

int GetCountNumbers(string FileName) {
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		fin.close();
		return 0;
	}
	int Counter = 0;
	int Number;
	while (!fin.eof()) {
		fin >> Number;
		Counter++;
	}
	
	fin.close();
	return Counter;
}

vector<int> GetAllNumbersFromFile(string FileName) {
	vector<int> MassiveOfNumbers;
	ifstream fin(FileName, ios::in);
	if (!fin) {
		cout << "file not open or not exist";
		return MassiveOfNumbers;
	}
	string line;
	int Iterator = 0;
	int number;
	while (!fin.eof()) {
		fin >> number;
		MassiveOfNumbers.push_back(number);
	}

	fin.close();
	return MassiveOfNumbers;
}

void CreateFileAndWriteNumbers(string FileName, vector<int> &MassiveOfNumbers, int Divider ) {
	ofstream fout(FileName, ios::out);
	if (!fout) {
		cout << "file not open";
		return;
	}
	if (Divider == 0) {
		Divider = 2;
	}
	for (int i = 0; i < MassiveOfNumbers.size(); i++) {
		fout << MassiveOfNumbers.at(i) / Divider << " ";
	}
	fout.close();

}
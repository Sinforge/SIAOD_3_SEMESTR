#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#pragma once

void CreateFile(string FileName) {
	ofstream fout(FileName, ios::out);
	if (!fout) {
		cout << "file not open";
		return;
	}
	int CountLines = (rand()% 10) + 1;
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
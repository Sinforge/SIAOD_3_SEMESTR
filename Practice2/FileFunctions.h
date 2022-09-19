#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#pragma once

//������� ��� �������� ���������� ����� � ���������� ������� � �������
void CreateFile(ofstream& fout) {
	
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
	

}
//����� ����������� ���������� �����
void PrintFile(ifstream & fin) {
	string line;
	while (!fin.eof()) {
		getline(fin, line);
		cout << line << endl;
	}
	

}

//������� ��� ���������� ������ � ����� �����
void WriteToLastLine(ofstream & fout, string Text) {
	fout << "\n" << Text;
}

//������� ��� ������ ����� �� ������� � �����
int GetNumberByPos(ifstream & fin, int Pos) {
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
	return 0;

}

//������� ��� ���������� ���-�� ����� � �����
int GetCountNumbers(ifstream& fin) {
	int Counter = 0;
	int Number;
	while (!fin.eof()) {
		fin >> Number;
		Counter++;
	}
	
	return Counter;
}


//������� ��� ��������� ���� ����� �� �����
vector<int> GetAllNumbersFromFile(ifstream& fin) {
	vector<int> MassiveOfNumbers;
	string line;
	int Iterator = 0;
	int number;
	while (!fin.eof()) {
		fin >> number;
		MassiveOfNumbers.push_back(number);
	}

	return MassiveOfNumbers;
}


//������� ��� ���������� ������ �� ������ ����� � ������
void FileOverwrite(ifstream & fin, ofstream& fout) {
	vector<int> MassiveOfNumbers;
	int MinNumber;
	MassiveOfNumbers = GetAllNumbersFromFile(fin);
	MinNumber = MassiveOfNumbers[0];
	for (int i = 1; i < MassiveOfNumbers.size(); i++)
	{
		MinNumber = min(MinNumber, MassiveOfNumbers.at(i));

	}
	if (MinNumber == 0) {
		MinNumber = 1;
	}
	for (int i = 0; i < MassiveOfNumbers.size(); i++) {
		fout << MassiveOfNumbers.at(i) / MinNumber << " ";
	}
}





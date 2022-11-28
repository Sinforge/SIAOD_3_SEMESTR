#pragma once

#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

pair<vector<pair<int,char>>, vector<pair<int, char>>> GetArrays(vector<pair<int, char>> arrayInput) {
    //sort array in non-increasing
    sort(arrayInput.begin(), arrayInput.end());
    vector<pair<int, char>> array1 = vector<pair<int, char>>();
    vector<pair<int, char>> array2 = vector<pair<int,char>>();
    int borderIndex = -1;
    int sum1 = 0, sum2 = 0;
    if (arrayInput.size() == 2) {
        array1.push_back(arrayInput[0]);
        array2.push_back(arrayInput[1]);
    }
    else {
        for (int i = 1; i < arrayInput.size() - 1; i++) {
            sum1 = 0;
            sum2 = 0;
            for (int j = 0; j < i; j++) {
                sum1 += arrayInput[j].first;
            }
            for (int j = i; j < arrayInput.size(); j++) {
                sum2 += arrayInput[j].first;
            }
            if (sum1 - sum2 > 0 || i == arrayInput.size() - 2) {
                borderIndex = i;
                break;
            }
        }
        //fill left array
        for (int i = 0; i < borderIndex; i++) {
            array1.push_back(arrayInput[i]);
        }
        //fill rigth array
        for (int j = borderIndex; j < arrayInput.size(); j++) {
            array2.push_back(arrayInput[j]);
        }
    }
    return { array1, array2 };


}
static vector<pair<char, string>> result;
void getCodes(vector<pair<int, char>> arrayInput, string nodeCode="") {

    if (arrayInput.size() == 1) {
        result.push_back(pair<char, string> {arrayInput[0].second, nodeCode});
    }
    else if (arrayInput.size() != 0) {
        pair<vector<pair<int, char>>, vector<pair<int, char>>> pair = GetArrays(arrayInput);
        getCodes(pair.first, nodeCode + '0');
        getCodes(pair.second, nodeCode + '1');
    }
}

int findPair(vector<pair<int, char>> pairs, char symbol) {
    for (int i = 0; i < pairs.size(); i++) {
        if (pairs[i].second == symbol) {
            return i;
        }
    }
    return -1;
}
int findPair(vector<pair<char, string>> pairs, char symbol) {
    for (int i = 0; i < pairs.size(); i++) {
        if (pairs[i].first == symbol) {
            return i;
        }
    }
    return -1;
}
string ShenonFanoAlgorithm(string str) {
    vector<pair<int, char>> charsInfo = vector<pair<int, char>>();
    //Determinate all symbols
    for (char c : str) {
        int index = findPair(charsInfo, c);
        if (index == -1) {
            charsInfo.push_back(pair<int, char> {1, c});
        }
        else {
            charsInfo.at(index).first++;
        }
    }
    getCodes(charsInfo);
    string compressedString = "";
    for (int i = 0; i < str.size(); i++) {
        compressedString += result.at(findPair(result, str[i])).second;
    }
    return compressedString;
}


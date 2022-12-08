#pragma once

#include <utility>
#include <vector>
#include <map>
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

struct ShenonFanoNode {
    ShenonFanoNode() {

    }
    vector<pair<int, char>> codes;
    ShenonFanoNode * left, * rigth;

};
void buildShenonFanoTree(ShenonFanoNode * currentNode) {

    if (currentNode->codes.size() == 1) {
        return;
    }

    else{
        pair<vector<pair<int, char>>, vector<pair<int, char>>> pair = GetArrays(currentNode->codes);
        ShenonFanoNode* left = new ShenonFanoNode();
        ShenonFanoNode* right = new ShenonFanoNode();
        left->codes = pair.first;
        right->codes = pair.second;
        currentNode->left = left;
        currentNode->rigth = right;

        buildShenonFanoTree(left);
        buildShenonFanoTree(right);
    }
}

void encode(ShenonFanoNode* currentNode, map<char, string> & codes, string currentCode = "") {
    if (currentNode->codes.size() == 1) {
        codes[currentNode->codes[0].second] = currentCode;
        return;
    }
    else {
        encode(currentNode->left, codes, currentCode + "0");
        encode(currentNode->rigth, codes, currentCode + "1");
    }
}
void printTree(ShenonFanoNode* Tree, int level = 0) {
    if (Tree->codes.size() == 1)
    {
        for (int i = 0; i < level; i++) {
            cout << "\t";
        }
        cout << Tree->codes[0].second << endl;
        return;
    }
    printTree(Tree->rigth, level + 1);
    for (int i = 0; i < level; i++) {
        cout << "\t";
    }
    for (auto ch : Tree->codes) {
        cout << ch.second;
    }
    cout << endl;
    printTree(Tree->left, level + 1);
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
//101010111110101001
void decode(string encodedString,int & currentId, string& decodedString, ShenonFanoNode * currentNode, ShenonFanoNode * Tree) {
    currentId++;
    if (currentId > encodedString.size()) {
        return;
    }
    if (currentNode->codes.size() == 1) {
        decodedString += currentNode->codes[0].second;
        currentId --;
        decode(encodedString, currentId, decodedString, Tree, Tree);
    }
    else {
        char currentChar = encodedString[currentId];
        if (currentChar == '0') {
            decode(encodedString, currentId, decodedString, currentNode->left, Tree);
        }
        else {
            decode(encodedString, currentId, decodedString, currentNode->rigth, Tree);
        }
    }

}
void ShenonFanoAlgorithm(string str) {
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

    //Make tree
    ShenonFanoNode* Tree = new ShenonFanoNode();
    Tree->codes = charsInfo;
    buildShenonFanoTree(Tree);

    //Print tree
    cout << "Prefix tree:" << endl;
    printTree(Tree);
    cout << endl;

    //Gets codes for our characters and print them
    map<char, string> Codes = map<char, string>();
    encode(Tree, Codes);
    cout << "Codes for characters" << endl;
    for (pair<char, string> code: Codes) {
        cout << code.first << " " << code.second << endl;
    }

    //Encode string
    string encodedString = "";
    for (char ch : str) {
        encodedString += Codes[ch];
    }
    cout << "\n" << "Compressed string: " <<  encodedString << endl;


    //Decode string
    string decodedString = "";
    int currentId = -1;
    decode(encodedString, currentId, decodedString, Tree, Tree);
    cout << "\nDecoded string: " << decodedString;

    cout << "\nКоэффициент сжатия: " <<  (float)str.size() * 8.0 / (float)encodedString.size();

}
string ShenonFanoAlgorithmTest(string str) {
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

    //Make tree
    ShenonFanoNode* Tree = new ShenonFanoNode();
    Tree->codes = charsInfo;
    buildShenonFanoTree(Tree);


    //Gets codes for our characters and print them
    map<char, string> Codes = map<char, string>();
    encode(Tree, Codes);

    //Encode string
    string encodedString = "";
    for (char ch : str) {
        encodedString += Codes[ch];
    }
    return encodedString;


}

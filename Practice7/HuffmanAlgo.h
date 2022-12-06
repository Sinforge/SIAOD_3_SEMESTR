#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <map>
using namespace std;

int findPair1(vector<pair<int, char>> pairs, char c) {
    for (int i = 0; i < pairs.size(); i++) {
        if (pairs[i].second == c) {
            return i;
        }
    }
    return -1;
}
struct Node
{
    
    char symbol = '-';
    int frequence;
    Node* left = NULL, * right = NULL;
    bool operator < (const Node& AnotherNode) {
        return (frequence < AnotherNode.frequence);
    }
    Node(char symbol, int frequence) {
        this->frequence = frequence;
        this->symbol = symbol;
    }
    Node() {

    }
};
void printHuffmanTree(Node* node, int level = 0) {
    if (node == NULL) {
        return;
    }
    printHuffmanTree(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        cout << "\t";
    }
    cout << node->symbol << endl;
    printHuffmanTree(node->left, level + 1);
}

Node* buildHuffmanTree(vector<pair<int, char>> charsInfo) {
    sort(charsInfo.begin(), charsInfo.end());
    queue<Node*> queueOfNodes = queue<Node*>();
    for (auto c : charsInfo) {
        queueOfNodes.push(new Node(c.second, c.first));
    }
    Node* mergedNode;
    Node* node1;
    Node* node2;
    while (queueOfNodes.size() != 1) {
        mergedNode = new Node();

        //take node and delete from queue
        node1 = queueOfNodes.front();
        queueOfNodes.pop();

        //take node and delete from queue
        node2 = queueOfNodes.front();
        queueOfNodes.pop();

        //fill merged node
        mergedNode->left = node1;
        mergedNode->right = node2;
        mergedNode->frequence = node1->frequence + node2->frequence;

        //push new node
        queueOfNodes.push(mergedNode);
    }
    return queueOfNodes.front();
}
void encode(Node* node, string currentCode, map<char, string>& huffmanCodes) {
    if (node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        huffmanCodes[node->symbol] = currentCode;

    }
    encode(node->left, currentCode + "0", huffmanCodes);
    encode(node->right, currentCode + "1", huffmanCodes);
}

void decode(string compressedString, Node* huffmanTree, int&currentIndex, string& decodedString) {
    if (huffmanTree == NULL) {
        return;
    }

 
    if (!huffmanTree->left && !huffmanTree->right)
    {
        decodedString += huffmanTree->symbol;
        return;
    }

    currentIndex++;

    if (compressedString[currentIndex] == '0')
        decode(compressedString,huffmanTree->left, currentIndex, decodedString);
    else
        decode(compressedString, huffmanTree->right, currentIndex, decodedString);
}

void  HuffmanCompress(string str) {
    vector<pair<int, char>> charsInfo = vector<pair<int, char>>();
    //Determinate all symbols
    for (char c : str) {
        int index = findPair1(charsInfo, c);
        if (index == -1) {
            charsInfo.push_back(pair<int, char> {1, c});
        }
        else {
            charsInfo.at(index).first++;
        }
    }
    

    //Build HuffmanTree
    Node* huffmanTree = buildHuffmanTree(charsInfo);
    
    
    //Get codes of characters
    map<char, string> codes = map<char, string>();
    encode(huffmanTree, "", codes);


    //Print Huffman Tree
    cout << "Huffman Tre" << endl;
    printHuffmanTree(huffmanTree);

    cout << "\nCodes of Huffman\n";
    for (auto code : codes) {
        cout << code.first << ' ' << code.second << endl;
    }


    //Get encoded string
    cout << "Encoced string: ";
    string compressedString = "";
    for (int i = 0; i < str.size(); i++) {
        compressedString += codes[str[i]];
    }
    cout << compressedString << endl;

    string result = "";
    int index = -1;


    //Decoding
    //need to cast to int, cause size returns size_t type
    cout << "Decoded string: ";
    while (index < (int)compressedString.size() - 2) {
        decode(compressedString, huffmanTree, index, result);
    }
    cout << "\n" << result;


    cout << "Коэффициент сжатия: " << (float)compressedString.size() / ((float)str.size() * 8);

    

}
string  HuffmanCompressTest(string str) {
    vector<pair<int, char>> charsInfo = vector<pair<int, char>>();
    //Determinate all symbols
    for (char c : str) {
        int index = findPair1(charsInfo, c);
        if (index == -1) {
            charsInfo.push_back(pair<int, char> {1, c});
        }
        else {
            charsInfo.at(index).first++;
        }
    }


    //Build HuffmanTree
    Node* huffmanTree = buildHuffmanTree(charsInfo);


    //Get codes of characters
    map<char, string> codes = map<char, string>();
    encode(huffmanTree, "", codes);



    string compressedString = "";
    for (int i = 0; i < str.size(); i++) {
        compressedString += codes[str[i]];
    }

    return compressedString;


}





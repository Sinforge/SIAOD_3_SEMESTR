#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#pragma once
using namespace std;
class TreeNode {
private:
    int CarId = -1;
    int FileIndex = -1;
    int level = 0;

    TreeNode* left, * right;
public:
    TreeNode(int CarId, int FileIndex){
        this->CarId = CarId;
        this->FileIndex = FileIndex;
    }
    void setLeft(TreeNode* left) {
        this->left = left;
    }
    void setRight(TreeNode* right) {
        this->right = right;
    }
    TreeNode* getLeft() {
        return this->left;
    }
    TreeNode* getRight() {
        return this->right;
    }
    int getLevel() {
        return this->level;
    }
    int getFileIndex() {
        return this->FileIndex;
    }
    void setFileIndex(int FileIndex) {
        this->FileIndex = FileIndex;
    }
    void setCarId(int CarId) {
        this->CarId = CarId;
    }
    int getCarId() {
        return this->CarId;
    }
};

struct CarOwner {
    int CarId; //номер авто
    char CarModel[30]; // марка автомобиля
    char OwnerDescription[50]; // Сведение о владельце
    //Вывод полей структуры
    void print() {
        cout << "\n\nCarId: " << CarId << "\n"
            << CarModel << "\n"
            << OwnerDescription << "\n";
    }
};


class BinaryTree {
private:
    TreeNode* TopNode;
    //Рекурсивная функция для вывода всех узлов
    void printNode(TreeNode* currentNode, int level) {
        if (currentNode)
        {
            printNode(currentNode->getRight(), level + 1);
            for (int i = 0; i < level; i++) cout << "-----";
            cout << currentNode->getCarId() << endl;
            printNode(currentNode->getLeft(), level+1);
        }

    }
    void InsertNode(TreeNode* currentNode, int FileIndex, int CarId) {
        if (CarId > currentNode->getCarId()) {
            if (currentNode->getRight() == NULL) {
                currentNode->setRight(new TreeNode(CarId, FileIndex));
            }
            else {
                InsertNode(currentNode->getRight(), FileIndex, CarId);
            }
        }
        else {
            if (currentNode->getLeft() == NULL) {
                currentNode->setLeft(new TreeNode(CarId, FileIndex));
            }
            else {
                InsertNode(currentNode->getLeft(), FileIndex, CarId);
            }
        }
    }

    TreeNode** FindNodeRec(int CarId, TreeNode* currentNode, TreeNode * previosNode) {
        if (currentNode != NULL) {
            if (CarId == currentNode->getCarId()) {
                TreeNode* CurrentAndPreviosNode[2];
                CurrentAndPreviosNode[0] = currentNode;
                CurrentAndPreviosNode[1] = previosNode;
            }
            else if (CarId > currentNode->getCarId()) {
                return FindNodeRec(CarId, currentNode->getRight(), currentNode);
            }
            else {
                return FindNodeRec(CarId, currentNode->getLeft(), currentNode);
               
            }
        }
        else {
            return NULL;
        }
        
    }
public:
    TreeNode* getTopNode() {
        return TopNode;
    }
    BinaryTree(ifstream fin) {
    
        CarOwner carOwner;
        int counter = 0;
        while (fin.read((char*)&carOwner, sizeof(CarOwner))) {
            if (counter == 0) {
                TopNode = new TreeNode(carOwner.CarId, 0);
            }
            else {
                InsertNode(TopNode, counter, carOwner.CarId);
            }
            counter++;
        }
        
    }
    void InsertNode(int CarId, int FileIndex) {
        InsertNode(TopNode, FileIndex, CarId);
    }
    TreeNode* FindNodeById(int CarId) {
        return FindNodeRec(CarId, TopNode, NULL)[0];
    }

    void DeleteNodeById(int CarId) {
        TreeNode** FindedNodes = FindNodeRec(CarId, TopNode, NULL);
        if (FindedNodes[1] != NULL) {
            if (FindedNodes[1]->getLeft() == FindedNodes[0]) {
                FindedNodes[1]->setLeft(FindedNodes[0]->getLeft());
            }
            TreeNode* NewReplaceNode = FindedNodes[0]->getLeft();
            while (NewReplaceNode->getRight() != NULL) {
                NewReplaceNode = NewReplaceNode->getRight();
            }
            NewReplaceNode->setRight(FindedNodes[0]->getRight());
        }
        else {
            TreeNode* LeftSubTree = FindedNodes[0]->getLeft();
            TreeNode* RightSubTree = FindedNodes[0]->getRight();
            this->TopNode = LeftSubTree;
            TreeNode* tempNode = LeftSubTree;
            while (tempNode->getRight() != NULL) {
                tempNode = tempNode->getRight();
            }
            tempNode->setRight(FindedNodes[0]->getRight());

        }
    }
    void PrintTree() {
        printNode(TopNode, 0);
    }
};
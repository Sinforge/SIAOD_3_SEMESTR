#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include "FileManagament.h"
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

class BinaryTree {
private:
    TreeNode* TopNode;
    //����������� ������� ��� ������ ���� �����
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
                return CurrentAndPreviosNode;
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
    BinaryTree(ifstream& fin) {
    
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
        TreeNode** FoundedNodes = FindNodeRec(CarId, TopNode, NULL);
        bool isLeft = false;
       
        if (FoundedNodes != NULL) {
            if (TopNode == FoundedNodes[0]) {
                if (TopNode->getLeft() != NULL && TopNode->getRight() == NULL) {
                    TopNode = TopNode->getLeft();
                }
                else if (TopNode->getLeft() == NULL && TopNode->getRight() != NULL) {
                    TopNode = TopNode->getRight();
                }
                else if (TopNode->getLeft() == NULL && TopNode->getRight() == NULL) {
                    TopNode = NULL;
                }
                else {
                    TreeNode* tempPrevNode = FoundedNodes[1];
                    TreeNode* tempNode = TopNode->getRight();
                    while (tempNode->getLeft() != NULL) {
                        tempPrevNode = tempNode;
                        tempNode = tempNode->getLeft();
                    }
                    tempNode->setLeft(TopNode->getLeft());
                    TopNode = TopNode->getRight();
                }
            }
            else{
                if (FoundedNodes[1]->getLeft() == FoundedNodes[0]) {
                    isLeft = true;
                }
                if (FoundedNodes[0]->getLeft() != NULL && FoundedNodes[0]->getRight() == NULL) {
                    if (isLeft) {
                        FoundedNodes[1]->setLeft(FoundedNodes[0]->getLeft());
                    }
                    else {
                        FoundedNodes[1]->setRight(FoundedNodes[0]->getLeft());
                    }
                }
                else if (FoundedNodes[0]->getLeft() == NULL && FoundedNodes[0]->getRight() != NULL) {
                    if (isLeft) {
                        FoundedNodes[1]->setLeft(FoundedNodes[0]->getRight());
                    }
                    else {
                        FoundedNodes[1]->setRight(FoundedNodes[0]->getRight());
                    }
                }
                else if (FoundedNodes[0]->getLeft() == NULL && FoundedNodes[0]->getRight() == NULL) {
                    if (isLeft) {
                        FoundedNodes[1]->setLeft(NULL);
                    }
                    else {
                        FoundedNodes[1]->setRight(NULL);
                    }
                }
                else {
                    TreeNode* tempPrevNode = FoundedNodes[1];
                    TreeNode* tempNode = FoundedNodes[0];
                    while (tempNode->getLeft() != NULL) {
                        tempPrevNode = tempNode;
                        tempNode = tempNode->getLeft();
                    }
                    tempPrevNode->setLeft(NULL);
                    tempNode->setLeft(FoundedNodes[0]->getLeft());
                    tempNode->setRight(FoundedNodes[0]->getRight());
                    if (isLeft) {
                        FoundedNodes[1]->setLeft(tempNode);
                    }
                    else {
                        FoundedNodes[1]->setRight(tempNode);
                    }
                }
            }
            
        }
    }
    void PrintTree() {
        printNode(TopNode, 0);
    }
};
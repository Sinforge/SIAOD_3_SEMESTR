#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include "FileManagament.h"
#pragma once
class RandomTree {
	class TreeNode {
    public:
        int CarId = -1;
        int FileIndex = -1;
        int countElements =0;
        TreeNode* left, * right;
        TreeNode(int CarId, int FileIndex) {
            this->CarId = CarId;
            this->FileIndex = FileIndex;
        }

        int GetCount() {
            return this ? countElements : 0;
        }
	};
    TreeNode* TopNode;
    TreeNode* RotateRight(TreeNode* currentNode) {
        TreeNode* right = currentNode->right;
        currentNode->right = right->left;
        right->left = currentNode;
        right->countElements = currentNode->countElements;
        currentNode->countElements = 1 + currentNode->left->GetCount() + currentNode->right->GetCount();
        return right;
    }

  
    TreeNode* RotateLeft(TreeNode* currentNode) {
        TreeNode* left = currentNode->left;
        currentNode->left = left->right;
        left->right = currentNode;
        left->countElements = currentNode->countElements;
        currentNode->countElements = 1 + currentNode->left->GetCount() + currentNode->right->GetCount();
        return left;
    }   
public:
    RandomTree(ifstream& fin) {
        CarOwner carOwner;
        int counter = 0;
        while (fin.read((char*)&carOwner, sizeof(CarOwner))) {
            if (counter == 0) {
                TopNode = new TreeNode(carOwner.CarId, 0);
         
            }
            else {
                InsertNode(TopNode, carOwner.CarId);
            }
            counter++;
        }
    }
    TreeNode* InsertNode(TreeNode* currentNode, int CarId) {
        if (rand() % (currentNode->countElements + 1) == 0) {
            return InsertNodeAsRoot(currentNode, CarId);
        }
        if (CarId < currentNode->CarId) {
            currentNode->left = InsertNode(currentNode->left, CarId);
        }
        else {
            currentNode->right = InsertNode(currentNode->right, CarId);
        }
        currentNode->countElements++;
        return currentNode;
    }

    TreeNode* InsertNodeAsRoot(TreeNode* currentNode, int CarId) {
        if (currentNode == NULL) {
            return new TreeNode(CarId, 0);
        }
        if (CarId < currentNode->CarId) {
            currentNode->left = InsertNodeAsRoot(currentNode->left, CarId);
            return RotateLeft(currentNode);
        }
        else {
            currentNode->right = InsertNodeAsRoot(currentNode->right, CarId);
            return RotateRight(currentNode);
        }

    }
};
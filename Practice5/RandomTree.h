#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include "FileManagament.h"
#pragma once
class RandomTree {
public:
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
    RandomTree(){}
    RandomTree(ifstream& fin) {
        CarOwner carOwner;
        int counter = 0;
        while (fin.read((char*)&carOwner, sizeof(CarOwner))) {
            if (counter == 0) {
                TopNode = new TreeNode(carOwner.CarId, 0);
         
            }
            else {
                TopNode = InsertNode(TopNode, carOwner.CarId, counter);
                TopNode->countElements = 1 + TopNode->right->GetCount() + TopNode->left->GetCount();
            }
            counter++;
        }
    }
//Вставить узел
TreeNode* InsertNode(TreeNode* currentNode, int CarId, int FileIndex) {
    if (!currentNode || rand() % (currentNode->countElements + 1) == 0) {
        if (currentNode && currentNode == TopNode) {
            this->TopNode = InsertNodeAsRoot(currentNode, CarId, FileIndex);
            return TopNode;
        }
        else {
            return InsertNodeAsRoot(currentNode, CarId, FileIndex);
        }
    }
    if (CarId < currentNode->CarId) {
        currentNode->left = InsertNode(currentNode->left, CarId, FileIndex);
    }
    else {
        currentNode->right = InsertNode(currentNode->right, CarId, FileIndex);
    }
    currentNode->countElements++;
    return currentNode;
}
//Вставляет вместо текущей вершины
 TreeNode* InsertNodeAsRoot(TreeNode* currentNode, int CarId, int FileIndex) {
     if (currentNode == NULL) {
         return new TreeNode(CarId, FileIndex);
     }
     if (CarId < currentNode->CarId) {
         currentNode->left = InsertNodeAsRoot(currentNode->left, CarId, FileIndex);
         return RotateLeft(currentNode);
     }
     else {
         currentNode->right = InsertNodeAsRoot(currentNode->right, CarId, FileIndex);
         return RotateRight(currentNode);
     }

 }
 //Поиск узла
TreeNode* FindById(TreeNode* currentNode, int CarId) {
    if (CarId < currentNode->CarId) {
        return FindById(currentNode->left, CarId);
    }
    if (CarId > currentNode->CarId) {
        return FindById(currentNode->right, CarId);
    }
    if (CarId == currentNode->CarId) {
        return currentNode;
    }
    return NULL;
}
//Слияние правого и левого поддерва
TreeNode* Merge(TreeNode* left, TreeNode* right)
{
    if (!left) return right;
    if (!right) return left;
    if (rand() % (left->countElements + right->countElements) < left->countElements) {
        left->right = Merge(left->right, right);
        left->countElements = left->right->GetCount() + 1 + left->left->GetCount();
        return left;
    }
    else {
        right->left = Merge(left, right->left);
        right->countElements = 1 + right->left->GetCount() + right->right->GetCount();
        return right;
    }
    return 0;
}

//Удаляет узел из дерева
TreeNode* Delete(TreeNode* currentNode, int CarId)
{
    if (!currentNode) return 0;
    if (CarId < currentNode->CarId) currentNode->left = Delete(currentNode->left, CarId);
    else if (CarId > currentNode->CarId) currentNode->right = Delete(currentNode->right, CarId);
    else {
        TreeNode* NodeForDelete = currentNode;
        currentNode = Merge(currentNode->left, currentNode->right);
        delete NodeForDelete;
        if (!currentNode) return currentNode;
    }
    currentNode->countElements = 1 + currentNode->left->GetCount() + currentNode->right->GetCount();

    return currentNode;
}

void PrintTree() {
    printNode(TopNode, 0);
}
    private:

//Рекурсивная функция для вывода всех узлов
void printNode(TreeNode* currentNode, int level) {
    if (currentNode)
    {
        printNode(currentNode->right, level + 1);
        for (int i = 0; i < level; i++) cout << "-----";
        cout << currentNode->CarId << endl;
        printNode(currentNode->left, level + 1);
    }

}
//Поворот вправо
TreeNode* RotateRight(TreeNode* currentNode) {
    TreeNode* right = currentNode->right;
    currentNode->right = right->left;
    right->left = currentNode;
    right->countElements = currentNode->countElements;
    currentNode->countElements = 1 + currentNode->left->GetCount() + currentNode->right->GetCount();
    return right;
}

//Поворот влево
TreeNode* RotateLeft(TreeNode* currentNode) {
    TreeNode* left = currentNode->left;
    currentNode->left = left->right;
    left->right = currentNode;
    left->countElements = currentNode->countElements;
    currentNode->countElements = 1 + currentNode->left->GetCount() + currentNode->right->GetCount();
    return left;
}
};
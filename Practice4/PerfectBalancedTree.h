#pragma once
#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
private:
    int info = 0;
    int level = 0;
    TreeNode* left, * right;
public:

    TreeNode(int info, int level) {
        this->info = info;
        this->level = level;
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
    int getInfo() {
        return this->info;
    }
    void setInfo(int info) {
        this->info = info;
    }
};

class PerfectBalancedTree {
private:
    int size = 0;
    vector<int> numbers;
    TreeNode* topOfTree = new TreeNode(1, 0);

    //Вставить новый узел рандомными числами
    void insertNewNodeByRandom(int countNodes, TreeNode* currentNode) {
        static int pos = 1;
        if (countNodes == 1) {
            int info;
            info = rand() % 20;
            this->numbers.push_back(info);

            info = numbers.at(pos);
            pos++;

            currentNode->setLeft(new TreeNode(info, currentNode->getLevel() + 1));
        }
        else if (countNodes >= 2) {
            int info1;
            int info2;
            info1 = rand() % 20;
            info2 = rand() % 20;
            numbers.push_back(info1);
            numbers.push_back(info2);

            info1 = numbers.at(pos);
            info2 = numbers.at(pos + 1);
            pos += 2;
            currentNode->setLeft(new TreeNode(info1, currentNode->getLevel() + 1));
            currentNode->setRight(new TreeNode(info2, currentNode->getLevel() + 1));

        }
        if (countNodes > 2) {
            insertNewNodeByRandom((countNodes - 2) - ((countNodes - 2) / 2), currentNode->getLeft());
            insertNewNodeByRandom(((countNodes - 2) / 2), currentNode->getRight());
        }
    }
    ////Вставить новый узел используя массив чисел
    void insertNewNodeByMassive(int countNodes, TreeNode* currentNode) {
        static int pos = 1;
        if (countNodes == 1) {
            int info;
            info = numbers.at(pos);
            pos++;

            currentNode->setLeft(new TreeNode(info, currentNode->getLevel() + 1));
        }
        else if (countNodes >= 2) {
            int info1;
            int info2;
            info1 = numbers.at(pos);
            info2 = numbers.at(pos + 1);
            pos += 2;
            currentNode->setLeft(new TreeNode(info1, currentNode->getLevel() + 1));
            currentNode->setRight(new TreeNode(info2, currentNode->getLevel() + 1));

        }
        if (countNodes > 2) {
            insertNewNodeByMassive((countNodes - 2) - ((countNodes - 2) / 2), currentNode->getLeft());
            insertNewNodeByMassive(((countNodes - 2) / 2), currentNode->getRight());
        }
    }
    //Рекурсивная функция для вывода всех узлов
    void printNode(TreeNode* currentNode) {
        if (currentNode)
        {
            printNode(currentNode->getRight());
            for (int i = 0; i < currentNode->getLevel(); i++) cout << "-----";
            cout << currentNode->getInfo() << endl;
            printNode(currentNode->getLeft());
        }

    }
    //Возвращает количество четных чисел в дереве
    void getCountEvenNumbers(TreeNode* subtree, int& countEvenNumbers) {
        if (!subtree) {
            return;
        }
        if (subtree->getInfo() % 2 == 0) {
            countEvenNumbers++;
        }
        getCountEvenNumbers(subtree->getRight(), countEvenNumbers);
        getCountEvenNumbers(subtree->getLeft(), countEvenNumbers);
    }
public:
    //Вычисляет в каком поддереве больше четных чисел
    void MoreEvenNumbers() {
        TreeNode* left = this->topOfTree->getLeft(),
            * right = this->topOfTree->getRight();
        int countLeft = 0, countRight = 0;
        getCountEvenNumbers(left, countLeft);
        getCountEvenNumbers(right, countRight);
        if (countLeft == countRight) {
            cout << "\nEquals amount\n";
        }
        else if (countLeft > countRight) {
            cout << "\nLeft subtree have more even numbers\n";
        }
        else {
            cout << "\nRight subtree have more even numbers\n";

        }
    }
    //Копирует данное дерево
    PerfectBalancedTree* CopyTree() {
        return new PerfectBalancedTree(this->size, this->numbers);

    }
    //Конструктор с заполнением числами массива
    PerfectBalancedTree(int nodeCount, vector<int> massive) {
        this->numbers = massive;
        this->size = nodeCount;
        this->topOfTree->setInfo(massive[0]);
        insertNewNodeByMassive(nodeCount - 1, this->topOfTree);

    }
    //Конструктор с заполнением рандомными числами
    PerfectBalancedTree(int nodeCount) {
        this->size = nodeCount;
        int num = rand() % 20;
        this->topOfTree->setInfo(num);
        this->numbers.push_back(num);

        insertNewNodeByRandom(nodeCount - 1, this->topOfTree);
    }
    //Вывод дерева
    void printTree() {
        printNode(this->topOfTree);

    }
};

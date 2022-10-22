// Practice4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
private:
    int info = 0;
    int level = 0;
    TreeNode* left, * right;
public:
    TreeNode() {}

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

    void insertNewNode(int countNodes, TreeNode* currentNode) {
        static int pos = 1;
        if (countNodes == 1) {
            int info;
            if (numbers.size() != size-1) {
                info = rand() % 20;
                this->numbers.push_back(info);
            }
            else {
                info = numbers.at(pos);
                pos++;
            }
            currentNode->setLeft(new TreeNode(info, currentNode->getLevel() + 1));
        }
        else if (countNodes >= 2) {
            int info1;
            int info2;
            if (numbers.size() != size - 1)
            {
                info1 = rand() % 20;
                info2 = rand() % 20;
                numbers.push_back(info1);
                numbers.push_back(info2);
            }
            else {
                info1 = numbers.at(pos);
                info2 = numbers.at(pos + 1);
                pos += 2;
            }
            currentNode->setLeft(new TreeNode(info1, currentNode->getLevel()+1));
            currentNode->setRight(new TreeNode(info2, currentNode->getLevel() + 1));

        }
        if (countNodes > 2) {
            insertNewNode((countNodes-2) - ((countNodes-2) / 2), currentNode->getLeft());
            insertNewNode(((countNodes-2) / 2), currentNode->getRight());
        }
    }
    void printNode(TreeNode* currentNode) {
        if (currentNode)
        {
            printNode(currentNode->getRight());
            for (int i = 0; i < currentNode->getLevel(); i++) cout << "-----";
            cout << currentNode->getInfo() << endl;
            printNode(currentNode->getLeft());
        }

    }
    void getCountEvenNumbers(TreeNode* subtree, int & countEvenNumbers) {
        if (!subtree) {
            return;
        }
        if (subtree->getInfo() % 2 == 0) {
            countEvenNumbers++;
        }
        getCountEvenNumbers(subtree->getRight(), countEvenNumbers);
        getCountEvenNumbers(subtree->getLeft(), countEvenNumbers);
    }

    void getAllNumberFromTree(vector<int> & massive, TreeNode* currentNode) {
        if (!currentNode) {
            return;
        }
        massive.push_back(currentNode->getInfo());
        getAllNumberFromTree(massive, currentNode->getRight());
        getAllNumberFromTree(massive, currentNode->getLeft());
    }
public:
    void MoreEvenNumbers() {
        TreeNode* left = this->topOfTree->getLeft(),
            * right = this->topOfTree->getRight();
        int countLeft = 0, countRight = 0;
        getCountEvenNumbers(left, countLeft);
        getCountEvenNumbers(left, countRight);
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
    PerfectBalancedTree* copyTree() {
        return new PerfectBalancedTree(this->size, this->numbers);
   
    }
    PerfectBalancedTree(int nodeCount, vector<int> massive) {
        this->numbers = massive;
        this->size = nodeCount;
        this->topOfTree->setInfo(massive[0]);
        for (int i = 0; i < numbers.size(); i++) {
            cout << numbers.at(i) << " ";
        }
        cout << numbers.size() << " " << size;
        insertNewNode(nodeCount - 1, this->topOfTree);

    }
    PerfectBalancedTree(int nodeCount) {
        this->size = nodeCount;
        int num = rand() % 20;
        this->topOfTree->setInfo(num);
        this->numbers.push_back(num);

        insertNewNode(nodeCount-1, this->topOfTree);
    }


    

    void printTree() {
        printNode(this->topOfTree);

    }
};

int main()
{
    PerfectBalancedTree * tree = new PerfectBalancedTree(10);
    tree->printTree();
    tree->MoreEvenNumbers();
    PerfectBalancedTree* newTree = tree->copyTree();
    newTree->printTree();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

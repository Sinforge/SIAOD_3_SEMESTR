// Practice4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "PerfectBalancedTree.h"
int main()
{

   
    setlocale(LC_ALL, "");
    PerfectBalancedTree* tree = new PerfectBalancedTree(1);
    PerfectBalancedTree* newTree = new PerfectBalancedTree(1);
    int ex_num;
    int size;
    cout << "Практическая работа номер 4 \"Нелинейные структуры данных. Бинарное дерево.\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
    cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание идеального сбалансированного дерева\n2)Вывод дерева\n3)Определить в каком поддереве исходного дерева больше четных чисел\n4)Скопировать дерево\n5)Вывести скопированное дерево\n";
    cin >> ex_num;
    while (ex_num) {
        switch (ex_num) {
        case 1:
            cout << "Input size of tree\n";
            cin >> size;
            tree = new PerfectBalancedTree(size);
            break;
        case 2:
            tree->printTree();
            break;
        case 3:
            tree->MoreEvenNumbers();
            break;
        case 4:
            newTree = tree->CopyTree();
            break;
        case 5:
            newTree->printTree();
            break;
        default:
            return 0;
            break;
        }
        cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Создание идеального сбалансированного дерева\n2)Вывод дерева\n3)Определить в каком поддереве исходного дерева больше четных чисел\n4)Скопировать дерево\n5)Вывести скопированное дерево\n";
        cin >> ex_num;

    }
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

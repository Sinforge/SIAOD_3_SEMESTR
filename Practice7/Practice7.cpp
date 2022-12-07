#include "RLE.h"
#include <fstream>
#include <sstream>
#include "LZ_Algorithms.h"
#include "ShenonFanoAlg.h"
#include "HuffmanAlgo.h"
#include <algorithm>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    //RLE TEST 1
    cout << "Тест 1 (RLE длинная строка из повторяющихся символов)" << endl;
    pair<string, float> test1 = compress("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccceeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
    cout << "Коэффициент сжатия: " << test1.second << endl
        << "Сжатая строка: " << test1.first << endl << endl << endl ;
    
    //RLE TEST 2
    cout << "Тест 2 (RLE длинная строка из неповторяющихся символов)\n";
    pair<string, float> test2 = compress("abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcde");
    cout << "Коэффициент сжатия: " << test2.second << endl
        << "Сжатая строка: " << test2.first << endl << endl << endl;

    //LZ77
    cout << "\nLZ77\n";
    pair<string, float> test3 = LZ77("0100001000000100001");
    cout << "Коэффициент сжатия: " << test3.second << endl
        << "Сжатая строка: " << test3.first << endl << endl << endl;


    //LZ78
    cout << "\nLZ78\n";
    pair<string, float> test4 = LZ78("пропронепронепрнепрона");
    cout << "Коэффициент сжатия: " << test4.second << endl
        << "Сжатая строка: " << test4.first << endl << endl << endl;


    //ShenonFano
    cout << "\nShenonFanoAlgorithm\n";
    ShenonFanoAlgorithm("Кони-кони, кони-кони, Мы сидели на балконе, Чай пили, воду пили, По-турецки говорили.");

    //Huffman
    cout << "\n\n\n";
    HuffmanCompress("ВласовВладиславВитальевич");
    


    //Test Huffman on large file
    cout << "\n\nTest with large file\n";
    ifstream file("Test.txt", ios::in);
    string fileLine = "";
    string allText = "";
    while (file) {
        getline(file, fileLine);
        allText += fileLine;
    }
    string compString = HuffmanCompressTest(allText);
    cout << "\n\nSize of encoded file in bytes: " << (float)compString.size() / 8.0;
    cout << "\n\nSize of original file in bytes: " << allText.size();
    cout << endl << "Коэффициент сжатия: " <<  ((float)allText.size() * 8.0) / (float)compString.size();
}

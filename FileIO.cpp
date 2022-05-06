#include <fstream>
#include <iostream>
#include "FileIO.h"
#include <string>
using namespace std;

void SaveFile(int gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int judge[], int &size){
    ofstream fout {"Save.txt"};
    if (fout.fail()) {
        cout << "Error in file opening!" << endl;
        exit(1);
    }
    fout << gold << " " << number << " " << size << endl;
    for (int i=0; i<20; ++i){
        fout << cards[i] << " " << cardsAI1[i] << " " << cardsAI2[i] << " " << cardsAI3[i] << endl;
    }
    for (int i=0; i<4; ++i){
        fout << judge[i] << endl;
    }
    fout.close();
} 

void ReadFile(int &gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int &number, int judge[], int &size){
    ifstream fin {"Save.txt"};
    if (fin.fail()){
        cout << "Error in file opening!" << endl;
        exit(1);
    }
    fin >> gold >> number >> size;
    for (int i=0; i<20; ++i){
        fin >> cards[i] >> cardsAI1[i] >> cardsAI2[i] >> cardsAI3[i];
    }
    for (int i=0; i<4; ++i){
        fin >> judge[i];
    }
    fin.close();
}
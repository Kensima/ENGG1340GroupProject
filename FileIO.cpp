#include <fstream>
#include <iostream>
#include "FileIO.h"
#include <string>
using namespace std;

void SaveCards(int cards[]){
    ofstream fout {"Save.txt",ios::app};
    for (int i=0; i<sizeof(cards); i++){
        fout << cards[i] << " ";
    }
    fout << endl;
}

void SaveOthers(int a){
    ofstream fout {"Save.txt",ios::app};
    fout << a << endl;
}

void ReadFile(){
    ifstream fin {"Save.txt"};
    int ele,count=0;
    while (fin >> ele){
        if (count < 25){
            switch (count / 5)
            {
            case 0: cards[count%5] = ele;
            case 1: cardsAI1[count%5] = ele;
            case 2: cardsAI2[count%5] = ele;
            case 3: cardsAI3[count%5] = ele;
        }
        else{
            
        }
    }
}
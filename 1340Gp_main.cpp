#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include "FileIO.h"
#include "Store.h"
using namespace std;

#define SPADE   "\xE2\x99\xA0"  // define four different suits
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
const string suits[4] = {SPADE, CLUB, HEART, DIAMOND}; 

// Distribute cards randomly
void SendCard(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int judge[]){   
    srand((unsigned)time(NULL));
    int x = rand()%10;
    srand((unsigned)x);
    for (int i = 0; i < 20; i++){
        if(judge[0] == 1){
            if (cards[i] == -1){
                cards[i] = rand()%35;
                break;
            }
        }
    }
    for (int i = 0; i < 20; i++){
        if(judge[1] == 1){
            if (cardsAI1[i] == -1){
                cardsAI1[i] = rand()%35;
                break;
            }
        }
    }
    for (int i = 0; i < 20; i++){
        if(judge[2] == 1){
            if (cardsAI2[i] == -1){
                cardsAI2[i] = rand()%35;
                break;
            }
        }
    }
    for (int i = 0; i < 20; i++){
        if(judge[3] == 1){
            if (cardsAI3[i] == -1){
                cardsAI3[i] = rand()%35;
                break;
            }
        }
    }
}

// Print out player's card and currency
void PrintCard(int cards[], int number, int gold){ 
    int index = 0;
    cout << "YOUR CARD: ";
    for (index = 0; index < 20; index++){
        if (cards[index] != -1){
            cout << cards[index] % 9 + 1 << suits[cards[index] / 9] << " ";
        }
    }
    cout << setw(15) << " ---Total currency = " << gold << endl;
    cout << endl;
}

// Judge the result of the game at last
bool IfEnd__JudgeGame(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], bool ifend, int number, int SIZE,  int judge[]){
    int total1 = 0, total2 = 0, total3 = 0, total4 = 0; 
    int elimination = 0;
    for (int i = 0; i < 4; i++){
        if (judge[i] == 0){
            elimination += 1;
        }
    }
    if (elimination >= 3){ // if only one player survive then stop the game immediately
        ifend = 0;
        return ifend;
    }
    else{
        elimination = 0;
    }
    for (int p = 0; p <= 20; p++){ // calculate sum of cards for each player and output if eliminated
        if (cards[p] != -1){
            total1 += cards[p] % 9 + 1;
        }
    }
    total1 -= 1;
    if (total1 > 21){
        ifend = 0;
        if (total1 >= 21){
            judge[0] = 0;
            cout << "You are eliminated!!" << endl;
        }
        return ifend;
    }
    if (judge[1] == 1){
        for (int p = 0; p <= 20; p++){
            if (cardsAI1[p] != -1){
                total2 += cardsAI1[p] % 9 + 1;
            }
        }
        total2 -= 1;
        if (total2 > 21){
            elimination += 1;
            cout << "Player2 is eliminated" << endl;
            judge[1] = 0;
        }
    }
    if (judge[2] == 1){
        for (int p = 0; p <= 20; p++){
            if (cardsAI2[p] != -1){
                total3 += cardsAI2[p] % 9 + 1;
            }
        }
        total3 -= 1;
        if (total3 > 21){
            elimination += 1;
            cout << "Player3 is eliminated" << endl;
            judge[2] = 0;
        }
    }
    if (judge[3] == 1){
        for (int p = 0; p <= 20; p++){
            if (cardsAI3[p] != -1)
            {
                total4 += cardsAI3[p] % 9 + 1;
            }
        }
        total4 -= 1;
        if (total4 > 21){
            elimination += 1;
            cout << "Player4 is eliminated" << endl;
            judge[3] = 0;
        }
    }
    if (total2 == 21 || total3 == 21 || total4 == 21){
        ifend = 0;
        return ifend;
    }
    if (elimination >= 3 || judge[0] == 0){ // Judge again whether only one player survive or not
        ifend = 0;
        return ifend;
    }
    else{ //If not then continue
        ifend = 1;
        return ifend;
    }
}

// If the game ends, display all cards of players
void ShowEndCard(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int rank[]){
    int total1 = 0, total2 = 0, total3 = 0, total4 = 0;
    cout << "YOUR FINAL CARD: ";
    for (int index = 0; index < 20; index++){
        if (cards[index] != -1){
            total1 += (cards[index] % 9) + 1;
            cout << cards[index] % 9 + 1 << suits[cards[index] / 9] << " ";  
        }
    }
    rank[0] = total1;
    cout << setw(15) << "POINTS = " << total1 << endl << endl;
    cout << "FINAL CARD OF PLAYER" << 2 << ": ";
    for (int index = 0; index < 20; index++){
        if (cardsAI1[index] != -1){
            total2 += (cardsAI1[index] % 9) + 1;
            cout << cardsAI1[index] % 9 + 1 << suits[cardsAI1[index] / 9] << " ";
        }
    }
    rank[1] = total2;
    cout << setw(15) << "POINTS = " << total2 << endl << endl;
    cout << "FINAL CARD OF PLAYER" << 3 << ": ";
    for (int index = 0; index < 20; index++){
        if (cardsAI2[index] != -1){
            total3 += (cardsAI2[index] % 9) + 1;
            cout << cardsAI2[index] % 9 + 1 << suits[cardsAI2[index] / 9] << " ";
        }
    }
    rank[2] = total3;
    cout << setw(15) << "POINTS = " << total3 << endl << endl;
    cout << "FINAL CARD OF PLAYER" << 4 << ": ";
    for (int index = 0; index < 20; index++){
        if (cardsAI3[index] != -1){
            total4 += (cardsAI3[index] % 9) + 1;
            cout << cardsAI3[index] % 9 + 1 << suits[cardsAI3[index] / 9] << " ";
        }
    }
    rank[3] = total4;
    cout << setw(15) << "POINTS = " << total4 << endl << endl;
}

// Show player's rank after showing cards of every player
void RankCard(int points[], int judge[]){ 
    int NO = 1;
    for (int k = 1; k < 4; k++){
        if ((judge[k] == 1 && judge[0] == 1) || (judge[k] == 0 && judge[0] == 0)){
            if ((points[0] < points[k] && points[k] < 22) || (points[0] > points[k] && points[k] > 21)){
                NO += 1;
            }
        }
        if (judge[0] == 0 && judge[k] == 1)
        {
            NO += 1;
        }
    }
    cout << "You ranked NO." << NO << "!!";
}

// Difficulty setting
// If the game is simple, AIs would not take any actions. If the game is normal, AIs would randomly attack or defense
int Settingdifficulty(int n){  
    if (n == 1){
        cout << "The current difficulty is: SIMPLE" << endl;
    }
    if (n == 2){
        cout << "The current difficulty is: NORMAL" << endl;
    }
    char a;
    cout << "Please choose difficulty(S or N): ";
    cin >> a;
    while (a != 'S' &&  a != 'N'){
        cout << "Invalid selection, please try again: ";
        cin >> a;
    }
    if (a == 'S'){
        cout << "Difficulty set to Simple!" << endl;
        return 1;
    }
    if (a == 'N'){
        cout << "Difficulty set to Normal!" << endl;
        return 2;
    }
}

// Print out every player's movement after each round
void Print(int choice, int target)  
{
    if (choice == 1){
        cout << "Attack---> Player" << target << endl;;
    }
    if (choice == 2){
        cout << "Defense" << endl;
    }
    if (choice == 3){
        cout << "be Neutral" << endl;
    }
}

// If a player is attacked, then he or she would be forced to draw a card
void DrawCards(int cards[]){  
    srand((unsigned)time(NULL));
    int x = rand()%1000000000;
    srand((unsigned)x);
    for (int i = 0; i < 20; i++){
        if (cards[i] == -1){
            cards[i] = rand()%35;
            cout << cards[i] % 9 + 1 << suits[cards[i] / 9] << endl;
            break;
        }
    }

}

// Print out the results of every player's movements
int Operation1__result(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int choice[], int target[], int gold){
    for (int i = 0; i < 4; i++){
        if (choice[i] == 1 && choice[target[i]-1] != 2) { 
            if (target[i] == 1){
                cout << "You receive: ";
                gold -= 50;
                DrawCards(cards);
            }
            if (target[i] == 2){
                cout << "Player2 receive: ";
                DrawCards(cardsAI1);
            }
            if (target[i] == 3){
                cout << "Player3 receive: ";
                DrawCards(cardsAI2);
            }
            if (target[i] == 4){
                cout << "Player4 receive: ";
                DrawCards(cardsAI3);
            }
        }
        if (i == 0 && choice[i] == 1 && choice[target[i]-1] != 2) { // Provide money for the player according to the action
            gold += 100;
        }
        if (i == 0 && choice[i] == 2){
            gold += 50;
        }
        if (i == 0 && choice[i] == 3){
            gold += 150;
        }
    }
    return gold;
}

// This is the main action
int Operation1(int diff, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int SIZE, int gold, int number, int judge[])
{
    gold += 50;
    if (diff > 1) 
    {
        srand((unsigned)time(NULL));
        int x = rand()%10000;
        srand((unsigned)x);
        int choice[4];
        int target[4];
        for (int i = 1; i < 4; i++)
        {
            if (judge[i] == 1)
            {
                choice[i] = 1 + rand()%3;
                if (choice[i] == 1)
                {
                    target[i] = 1 + rand()%4;
                    while (target[i] == i+1 || judge[target[i]-1] == 0)
                    {
                        target[i] = 1 + rand()%4;
                    }
                }
                else
                {
                    target[i] = 0;
                }
            }
            else
            {
                choice[i] = 0;
                target[i] = 0;
            }
        }
        char Your_option;
        cout << "Please choose your action!" << endl << "Attack, Defence or Neutral (INPUT: A,D,N): ";
        cin >> Your_option;
        while (Your_option != 'D' && Your_option != 'A' && Your_option != 'N')
        {
            cout << "Invalid choice!! Please input again: ";
            cin >> Your_option;
        }
        if (Your_option == 'D')
        {
            choice[0] = 2;
            target[0] = 0;
        }
        if (Your_option == 'A')
        {
            choice[0] = 1;
            cout << "Target?: ";
            int tar;
            cin >> tar;
            while (tar < 2 || tar > 4 || judge[tar-1] == 0)
            {
                cout << "Invalid choice (wrong input or eliminated target), please try again: ";
                cin >> tar;
            }
            target[0] = tar;
        }
        if (Your_option == 'N')
        {
            choice[0] = 3;
            target[0] = 0;
        }
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
            {
                cout << "Your choice: ";
                Print(choice[i], target[i]);
            }
            else
            {
                if (judge[i] == 1)
                {
                    cout << "Player" << i+1 << " choose to ";
                    Print(choice[i], target[i]);
                }
            }
        }
        cout << endl;
        gold = Operation1__result (cards, cardsAI1, cardsAI2, cardsAI3, choice, target, gold);
    }
    return gold;
}

// Initialize arrays to avoid calling unassigned digits
void Initialize(int cards[], int Size){
    for (int i=0; i<Size; ++i){ 
        cards[i] = -1;
    }
}

int main(){
    bool read = false; // A label to judge whether the player uses saved files to start the game or not
    int SIZE;  //The maximum number of turns determined by the player
    int *cards = new int[20]; // card lists of four players
    int *cardsAI1 = new int[20];
    int *cardsAI2 = new int[20];
    int *cardsAI3 = new int[20];
    int judge[4] = {1, 1, 1, 1}; // If the player is alive then 1, otherwise 0
    int number = 0, Y_N = 1, finalcount[4]; // number is current turns, Y_N is the flag determining whether the game ends or not, final count is the final rank of four players
    Initialize(cards,20); Initialize(cardsAI1,20); Initialize(cardsAI2,20); Initialize(cardsAI3,20); // initialize all four card lists
    cout << "Welcome to BlackJack2.0" << endl;
    cout << "----------CATALOGUE----------" << endl << "1:DIFFICULTY" << endl << "2:FILE READING" << endl << "3:STARTING NEW GAME" << endl;
    char cat, diff = 2; // cat is the choice of the player, diff is difficulty (Normal in default)
    int gold = 0; // The money held by the player to purchase special cards in Store
    cout << "Your Choice: "; 
    cin >> cat;
    while (cat <= '0' || cat > '3'){ //Exception handling
        cout << "Invalid choice, please try again: ";
        cin >> cat;
    }
    while (cat == '1'){ // Change the difficulty of the game
        diff = Settingdifficulty(diff);
        cout << "----------CATALOGUE----------" << endl << "1:DIFFICULTY" << endl << "2:FILE READING" << endl << "3:STARTING NEW GAME" << endl;
        cout << "Your Choice: ";
        cin >> cat;
    }
    if (cat == '2'){ // Read data from saved files
        ReadFile(gold, cards, cardsAI1, cardsAI2, cardsAI3, number, judge, SIZE);
        cat = '3';
        read = true;
    }
    if (cat == '3'){
        if (diff == 1){ //Display difficulty before game starts
            cout << "Simple Game!! Your opponent will not take any action!!" << endl << endl;
        }
        if (diff == 2){
            cout << "Normal Game!! Your opponent will not use special cards!!" << endl << endl;
        }
        cout << "You can enter the store as game begins (input S)" << endl << endl;
        if (read == false){
            cout << "Please select the maximum number of rounds(3 to 10): ";
            cin >> SIZE; 
            while (SIZE < 3 || SIZE > 10){
                cout << "Invalid choice, please try again: ";
                cin >>SIZE;
            } 
        }
        char key; // Player's Choice
        while (Y_N && number < SIZE){
            cout << "ROUND " << number+1 << ":   " << "-------------------------------+----------------------------" << endl;
            SendCard(cards, cardsAI1, cardsAI2, cardsAI3, number, judge); //Send cards to every player
            PrintCard(cards, number, gold); // Show your card
            gold = Operation1(diff, cards, cardsAI1, cardsAI2, cardsAI3, SIZE, gold, number, judge); // Attack, defend, or neutral
            if (diff != 1){
                PrintCard(cards, number, gold); //Print your card again after each round
            }
            cout << "Continue Or Enter the Store (Y, N or S): ";
            cin >> key; // Y to continue and N to pause
            while (key != 'S' && key != 'Y' && key != 'N'){
                cout << "Invalid input, please try again: ";
                cin >> key;
            }
            while (key == 'S'){ // Enter the store
                gold = Store(gold,cards,cardsAI1,cardsAI2,cardsAI3,number,SIZE);
                cout << "Continue or Not(Y or N) : ";
                cin >> key;
                while (key != 'Y' && key != 'N'){
                    cout << "Invalide input, please try again: ";
                    cin >> key;
                }
            }
            Y_N = IfEnd__JudgeGame(cards, cardsAI1, cardsAI2, cardsAI3, Y_N, number, SIZE, judge); // End game judge
            if (key == 'Y'){ 
                number += 1;
                continue;
            }
            if (key == 'N'){ // Save the game or just break out
                cout << "The Game Is Paused By Player..." << endl;
                cout << "Input S to save, others to break out: ";
                number += 1;
                string pause;
                cin >> pause;
                if (pause == "S"){
                    SaveFile(gold, cards, cardsAI1, cardsAI2, cardsAI3, number, judge, SIZE);
                    cout << "File saved!" << endl;
                }
                cout << "Game Ending...";
                exit(1);  
            }
        }
        cout << endl << "-------------------------+++++GAME OVER+++++---------------------------" << endl << endl;
        ShowEndCard(cards, cardsAI1, cardsAI2, cardsAI3, finalcount); // Display cards after game ends
        RankCard(finalcount, judge); //Display rank of every player
        delete [] cards;
        delete [] cardsAI1;
        delete [] cardsAI2;
        delete [] cardsAI3;
        return 0;
    }
}


#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#define SPADE   "\xE2\x99\xA0"  // define four different suits
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
const string suits[4] = {SPADE, CLUB, HEART, DIAMOND}; 

// Judge the availability of player choice
bool Judge(int cardsAI[]){
    int total=0;
    for (int i=0; i<20; ++i){
        if (cardsAI[i] != -1) total += cardsAI[i] % 9 + 1; 
    }
    if (total > 21) return false;
    else return true;
}

//Display peeped AI cards
void PrintAICard(int cardsAI[], int number, int extra){
    cout << "";
    for (int index = 0; index < 20; index++){
        if (cardsAI[index] != -1) cout << cardsAI[index] % 9 + 1 << suits[cardsAI[index] / 9] << " ";
    }
    cout << endl;
}

// Swap cards between the player and AI
void SwapCard(int cards[], int cardAI[]){
    int cardnum = 0;    
    do{  
        cout << "Please select your card to swap (No.): ";
        cin >> cardnum;
        if (cards[cardnum-1] == -1) cout << "You are selecting a blank card, try again!" << endl;
    }while (cards[cardnum-1] == -1 || cardnum < 1);

    int cardAInum = 0;
    do{
        cout << "Please select AI card to swap (No.): ";
        cin >> cardAInum;
        if (cardAI[cardAInum-1] == -1) cout << "You are selecting a blank card, try again!" << endl;
    }while (cardAI[cardAInum-1] == -1 || cardAInum < 1);

    swap(cards[cardnum-1], cardAI[cardAInum-1]);
    cout << "Swap success!" << endl;
}

// Hand over cards to assigned AI
void HandCard(int cards[], int cardAI[], int size){
    int cardnum = 0;    
    do{  
        cout << "Please select your card to give out (No.): ";
        cin >> cardnum;
        if (cards[cardnum-1] == -1) cout << "You are selecting a blank card, try again!" << endl;
    }while (cards[cardnum-1] == -1 || cardnum < 1);

    for (int i=0; i<20; i++){
        if (cardAI[i] == -1) cardAI[i] = cards[cardnum-1];
    }
    for(int i=0; i<20; i++){
            if(i == cardnum-1){
                for(int j=i; j<19; j++) cards[j] = cards[j+1];
            cout << "Success!" << endl;
            break;
        }
    }
}

void SendCard(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int order[], int number, int extra[], int judge[]){   //发牌程序
    srand((unsigned)time(NULL));
    int x = rand()%10;
    srand((unsigned)x);
    cards[number+extra[0]] =rand()%35;
    if (judge[1] == 1){  //如果已经爆牌就不用发牌了
        cardsAI1[number+extra[1]] = rand()%35;
    }
    if (judge[2] == 1){
        cardsAI2[number+extra[2]] = rand()%35;
    }
    if (judge[3] == 1){
        cardsAI3[number+extra[3]] = rand()%35;
    }
}

int Store(int gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int extra[], int size){
    int card_number, price[4] = {50, 150, 300, 450};
    int choice=0, peep=0;
    bool alive; // check whether the selected AI is alive
    cout << "-----------------------------" << endl;
    cout << "-   Welcome to Card Store   -" << endl;
    cout << "-----------------------------" << endl;
    cout << "CURRENCY = " << gold << endl;
    cout << "Card list: " << endl;
    cout << "1.Peep Card -----------------50$" << endl;
    cout << "2.Exchanging Card -----------150$" << endl;
    cout << "3.Discard Card --------------300$" << endl;
    cout << "4.Handing Over Card ---------450$"  << endl;
    cout << "Enter the card number to purchase(input 0 to Quit)： ";
    cin >> card_number;
    while (card_number < 0 || card_number > 5){
        cout << "Invalid choice, please try again: ";
        cin >> card_number;
    }
    if (card_number == 0){
        cout << "Exit the store..." << endl;
        return gold;
    }
    while (gold - price[card_number-1] < 0){
        cout << "No enough money! Please try other products~: ";
        cin >> card_number;
        if (card_number == 0){
            cout << "Exit the store..." << endl;
            return gold;
        }
    }
    if (card_number > 0 && card_number < 5) {
        if (card_number > 2){
            extra[0] -= 1;
        }
        cout << "Thank you for your purchasing!!" << endl;
        gold -= price[card_number-1];
        switch (card_number) {// perform actions according to user input
            case 1:{ // peep AI cards           
                while (peep < 2 || peep > 4){
                    cout << "Enter the AI player number you want to peep (2 - 4): ";
                    cin >> peep;
                    switch (peep){
                        case 2: alive = Judge(cardsAI1); break;
                        case 3: alive = Judge(cardsAI2); break;
                        case 4: alive = Judge(cardsAI3); break;
                    }
                    if (alive = false){
                        cout << "You are choosing a dead player!" << endl;
                        peep = 0;
                    }
                }
                switch (peep){
                    case 2: PrintAICard(cardsAI1, number, extra[1]); break;
                    case 3: PrintAICard(cardsAI2, number, extra[2]); break;
                    case 4: PrintAICard(cardsAI3, number, extra[3]); break;
                }
                break;
            }
            case 2:{ // Exchange cards
                cout << "Your current card: ";
                PrintAICard(cards, number, extra[0]);
                while (choice < 2 || choice > 4){
                    cout << "Choose the AI player number you want to exchange cards with (2 - 4): ";
                    cin >> choice;
                    switch (choice){
                        case 2: alive = Judge(cardsAI1); break;
                        case 3: alive = Judge(cardsAI2); break;
                        case 4: alive = Judge(cardsAI3); break;
                    }
                    if (alive = false){
                        cout << "You are choosing a dead player!" << endl;
                        choice = 0;
                    }
                }
                switch (choice){
                    case 2: SwapCard(cards, cardsAI1); break;
                    case 3: SwapCard(cards, cardsAI2); break;
                    case 4: SwapCard(cards, cardsAI3); break;
                }
                cout << "Your current card: ";
                PrintAICard(cards, number, extra[0]);
                break;
            }
            case 3:{ // Discard Card
                cout << "Your current card: ";
                PrintAICard(cards, number, extra[0]);
                do{
                    cout << "Choose the card you want to discard (No.): ";
                    cin >> choice;
                    if (cards[choice-1] == -1) cout << "You are choosing a blank card, try again" << endl;
                }while (choice < 1 || cards[choice-1] == -1);
                for(int i=0; i<20; i++){
                    if(i == choice-1){
                        for(int j=i; j<(20-1); j++) cards[j] = cards[j+1];
                        cout << "Discard success" << endl;
                        break;
                    }
                }
                cout << "Your current card: ";
                PrintAICard(cards, number, extra[0]);
                break;
            }
            case 4:{ // Hand over card
                cout << "Your current card: ";
                PrintAICard(cards, number, extra[0]);
                while (choice < 2 || choice > 4 ){
                    cout << "Choose the AI player you want to give card to (2 - 4): ";
                    cin >> choice;
                }
                switch (choice){
                    case 2: HandCard(cards, cardsAI1, 20); break;
                    case 3: HandCard(cards, cardsAI2, 20); break;
                    case 4: HandCard(cards, cardsAI3, 20); break;
                }
                ++extra[choice-1];
                cout << "Your current card: ";
                PrintAICard(cards, number, extra[0]);
                break;
            }
        }
    }
    return gold;
}

void PrintCard(int cards[], int number, int extra, int gold, string cardlist[]){ //显示你自己的牌和金钱
    int index = 0;
    cout << "YOUR CARD: ";
    for (index = 0; index < number+1+extra; index++){
        cout << cards[index] % 9 + 1 << suits[cards[index] / 9] << " ";
    }
    cout << setw(15) << " ---Total currency = " << gold << endl;
    cout << endl;
}

bool IfEnd__JudgeGame(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int order[], bool ifend, int number, int SIZE, int extra[], int judge[]){
    int total1 = 0, total2 = 0, total3 = 0, total4 = 0;  //显示游戏是否结束，以及判断淘汰的玩家
    int elimination = 0;
    for (int i = 0; i < 4; i++){
        if (judge[i] == 0){
            elimination += 1;
        }
    }
    if (elimination >= 3){
        ifend = 0;
        return ifend;
    }
    else{
        elimination = 0;
    }
    for (int p = 0; p <= number+extra[0]; p++){
        total1 += cards[p] % 9 + 1;
    }
    if (total1 >= 21){
        ifend = 0;
        if (total1 > 21){
            judge[0] = 0;
            order[0]= number + 1 + extra[0];
            cout << "You are eliminated!!" << endl;
        }
        return ifend;
    }
    if (judge[1] == 1){
        for (int p = 0; p <= number+extra[1]; p++){
            total2 += cardsAI1[p] % 9 + 1;
        }
        if (total2 > 21){
            elimination += 1;
            order[1] = number + 1 + extra[1];
            cout << "Player2 is eliminated" << endl;
            judge[1] = 0;
        }
    }
    if (judge[2] == 1){
        for (int p = 0; p <= number+extra[2]; p++){
            total3 += cardsAI2[p] % 9 + 1;
        }
        if (total3 > 21){
            elimination += 1;
            order[2] = number + 1 + extra[2];
            cout << "Player3 is eliminated" << endl;
            judge[2] = 0;
        }
    }
    if (judge[3] == 1){
        for (int p = 0; p <= number+extra[3]; p++){
            total4 += cardsAI3[p] % 9 + 1;
        }
        if (total4 > 21){
            elimination += 1;
            order[3] = number + 1 + extra[3];
            cout << "Player4 is eliminated" << endl;
            judge[3] = 0;
        }
    }
    if (total2 == 21 || total3 == 21 || total4 == 21){
        ifend = 0;
        return ifend;
    }
    if (elimination >= 3 || judge[0] == 0){ // 如果其他玩家都被淘汰了那么游戏也会结束
        ifend = 0;
        return ifend;
    }
    else{ //如果你存活且场上至少还剩下两名玩家，则游戏继续
        ifend = 1;
        return ifend;
    }
}

void ShowEndCard(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int order[], int rank[], int number, int extra[]){
    int total1 = 0, total2 = 0, total3 = 0, total4 = 0;
    cout << "YOUR FINAL CARD: ";
    for (int index = 0; index < number + extra[0]; index++){
        total1 += (cards[index] % 9) + 1;
        cout << cards[index] % 9 + 1 << suits[cards[index] / 9] << " ";  //四个for loop记录每个玩家的最终卡牌以及点数总和
    }
    rank[0] = total1;
    cout << setw(15) << "POINTS = " << total1 << endl << endl;
    cout << "FINAL CARD OF PLAYER" << 2 << ": ";
    for (int index = 0; index < number + extra[1]; index++){
        total2 += (cardsAI1[index] % 9) + 1;
        cout << cardsAI1[index] % 9 + 1 << suits[cardsAI1[index] / 9] << " ";
    }
    rank[1] = total2;
    cout << setw(15) << "POINTS = " << total2 << endl << endl;
    cout << "FINAL CARD OF PLAYER" << 3 << ": ";
    for (int index = 0; index < number + extra[2]; index++){
        total3 += (cardsAI2[index] % 9) + 1;
        cout << cardsAI2[index] % 9 + 1 << suits[cardsAI2[index] / 9] << " ";
    }
    rank[2] = total3;
    cout << setw(15) << "POINTS = " << total3 << endl << endl;
    cout << "FINAL CARD OF PLAYER" << 4 << ": ";
    for (int index = 0; index < number + extra[3]; index++){
        total4 += (cardsAI3[index] % 9) + 1;
        cout << cardsAI3[index] % 9 + 1 << suits[cardsAI3[index] / 9] << " ";
    }
    rank[3] = total4;
    cout << setw(15) << "POINTS = " << total4 << endl << endl;
}

void RankCard(int points[], int judge[]){ //显示玩家自己的排名
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

int Settingdifficulty(int n){  //调整难度的界面
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

void Print(int choice, int target)  //操作1的播报，比如自己干嘛了，player2 干嘛了之类的。
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

int DrawCards(int cards[], int number, int extra){  //攻击操作成功后，触发被攻击对象被迫摸一张牌
    srand((unsigned)time(NULL));
    int x = rand()%1000000000;
    srand((unsigned)x);
    cards[number+1+extra] = rand()%35;
    cout << cards[number+1+extra] % 9 + 1 << suits[cards[number+1+extra] / 9] << endl;
    extra += 1;
    return extra;
    
}

int Operation1__result(int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int choice[], int target[], int gold, int number, int extra[]){
    for (int i = 0; i < 4; i++){
        if (choice[i] == 1 && choice[target[i]-1] != 2) {   //操作的判定以及结果
            if (target[i] == 1){
                cout << "You receive: ";
                gold -= 50;
                extra[0] = DrawCards(cards, number, extra[0]);
            }
            if (target[i] == 2){
                cout << "Player2 receive: ";
                extra[1] = DrawCards(cardsAI1, number, extra[1]);
            }
            if (target[i] == 3){
                cout << "Player3 receive: ";
                extra[2] = DrawCards(cardsAI2, number, extra[2]);
            }
            if (target[i] == 4){
                cout << "Player4 receive: ";
                extra[3] = DrawCards(cardsAI3, number, extra[3]);
            }
        }
        if (i == 0 && choice[i] == 1 && choice[target[i]-1] != 2) { 
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

int Operation1(int diff, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int order[], int SIZE, int gold, int number, int extra[], int judge[])
{
    gold += 50;
    if (diff > 1)   //选择进行操作，AI会随机进行操作如果难度是普通和困难。
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
        cout << "Please choose your action!" << endl << "Attack, Defence or Neutral （INPUT: A,D,N): ";
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
            while (tar < 2 || tar > 4 || order[tar-1] != SIZE)
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
        gold = Operation1__result (cards, cardsAI1, cardsAI2, cardsAI3, choice, target, gold, number, extra);
    }
    return gold;
}

// Initialize arrays to avoid calling unassigned digits
void Initialize(int cards[], int Size){
    for (int i=0; i<Size; ++i){
        cards[i] = -1;
    }
}

void SaveFile(int gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int extra[], int judge[], int round[], int &size){
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
        fout << extra[i]  << " " << judge[i] << " " << round[i] << endl;
    }
    fout.close();
} 

void ReadFile(int &gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int &number, int extra[], int judge[], int round[], int &size){
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
        fin >> extra[i]  >> judge[i] >> round[i];
    }
    fin.close();
}

int main(){
    cout << "Welcome to BlackJack2.0" << endl;
    cout << "----------CATALOGUE----------" << endl << "1:DIFFICULTY" << endl << "2:FILE READING" << endl << "3:STARTING NEW GAME" << endl;
    char cat, diff = 2;
    string cardlist[4] = {"Peep Card", "Exchanging Card", "Discard Card", "Handing Over Card"};
    int gold = 0; //玩家所拥有的金钱数量，可通过各种操作获取，可在商店购买道具。
    cout << "Your Choice: "; //目录选择
    cin >> cat;
    bool read = false;
    int SIZE;  //决定回合上限
    int *cards = new int[20]; // 四个玩家，第一个是自己玩的，剩下三个是AI，这里用了动态记忆管理
    int *cardsAI1 = new int[20];
    int *cardsAI2 = new int[20];
    int *cardsAI3 = new int[20];
    int judge[4] = {1, 1, 1, 1};
    int round[4], extra[4] = {0, 0, 0, 0}, number = 0, Y_N = 1, finalcount[4];
    Initialize(cards,20); Initialize(cardsAI1,20); Initialize(cardsAI2,20); Initialize(cardsAI3,20);
    while (cat <= '0' || cat > '3'){ //错误的输入，提示修改
        cout << "Invalid choice, please try again: ";
        cin >> cat;
    }
    while (cat == '1'){ // 修改难度
        diff = Settingdifficulty(diff);
        cout << "----------CATALOGUE----------" << endl << "1:DIFFICULTY" << endl << "2:FILE READING" << endl << "3:STARTING NEW GAME" << endl;
        cout << "Your Choice: ";
        cin >> cat;
    }
    if (cat == '2'){
        ReadFile(gold, cards, cardsAI1, cardsAI2, cardsAI3, number, extra, judge, round, SIZE);
        cat = '3';
        read = true;
    }
    if (cat == '3'){
        if (diff == 1){ //游戏开始之前显示难度
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
            for (int i=0; i<4; ++i) round[i] = SIZE; //number 是回合数。Y_N是判断游戏是否结束，final count是用来计算排名的
        }
        char key;      // round里面每个都是判断对应玩家是否爆牌，如果爆牌的话数字SIZE会被改成它当前死亡的回合+收到的牌
        while (Y_N && number < SIZE){
            cout << "ROUND " << number+1 << ":   " << "-------------------------------+----------------------------" << endl;
            SendCard(cards, cardsAI1, cardsAI2, cardsAI3, round, number, extra, judge); //每一回合的发牌程序
            PrintCard(cards, number, extra[0], gold, cardlist); // 打印自己的卡牌
            gold = Operation1(diff, cards, cardsAI1, cardsAI2, cardsAI3, round, SIZE, gold, number, extra, judge); //特殊操作1，即攻击，防守和中立
            if (diff != 1){
                PrintCard(cards, number, extra[0], gold, cardlist); //再次打印自己的卡牌
            }
            cout << "Continue Or Enter the Store (Y, N or S): ";
            cin >> key; //选择游戏是否继续的按键，输入Y就是继续，输入其他就是暂停；
            while (key != 'S' && key != 'Y' && key != 'N'){
                cout << "Invalide input, please try again: ";
                cin >> key;
            }
            while (key == 'S'){
                gold = Store(gold,cards,cardsAI1,cardsAI2,cardsAI3,number,extra,SIZE);
                cout << "Continue or Not(Y or N) : ";
                cin >> key;
                while (key != 'Y' && key != 'N'){
                    cout << "Invalide input, please try again: ";
                    cin >> key;
                }
            }
            Y_N = IfEnd__JudgeGame(cards, cardsAI1, cardsAI2, cardsAI3, round, Y_N, number, SIZE, extra, judge); //判断出局的人，以及自己是否出局，以及游戏是否结束，如果结束了上面while loop 里面的Y_N会变成false
            if (key == 'Y'){ 
                number += 1;
                continue;
            }
            if (key == 'N'){
                cout << "The Game Is Paused By Player..." << endl;
                cout << "Input S to save, others to break out: ";
                number += 1;
                string pause;
                cin >> pause;
                if (pause == "S"){
                    SaveFile(gold, cards, cardsAI1, cardsAI2, cardsAI3, number, extra, judge, round, SIZE);
                    cout << "File saved!" << endl;
                }
                cout << "Game Ending...";
                exit(1);  //这里是暂停页面，你可以从这里加入方程比如暂停之后重新开始游戏或者暂停之后保存游戏
            }
        }
        cout << endl << "-------------------------+++++GAME OVER+++++---------------------------" << endl << endl;
        ShowEndCard(cards, cardsAI1, cardsAI2, cardsAI3, round, finalcount, number, extra); // 显示最终每位玩家的卡牌。
        RankCard(finalcount, judge); //计算排名（仅自己的排名）
        delete [] cards;
        delete [] cardsAI1;
        delete [] cardsAI2;
        delete [] cardsAI3;
        return 0;
    }
}



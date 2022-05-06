#include <iostream>
#include <string>
#include "Store.h"
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
void PrintAICard(int cardsAI[]){
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
        if (cardAI[i] == -1 && cardAI[i-1] != -1) {
            cardAI[i] = cards[cardnum-1];
            break;
        }
    }
    for(int i=0; i<20; i++){
        if(i == cardnum-1){
            for(int j=i; j<19; j++) {
                if (cards[j] == -1){
                    cards[j] = cards[j+1];
                }
            }
        cout << "Success!" << endl;
        break;
        }
    }
}

int Store(int gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int size){
    int price[4] = {50, 150, 300, 450}; // The price of four special cards
    int card_number, choice=0, peep=0; // Player choices
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
    while (gold - price[card_number-1] < 0){ // Check the availability of the purchase
        cout << "No enough money! Please try other products~: ";
        cin >> card_number;
        if (card_number == 0){
            cout << "Exit the store..." << endl;
            return gold;
        }
    }
    if (card_number > 0 && card_number < 5) {
        cout << "Thank you for your purchasing!!" << endl;
        gold -= price[card_number-1];
        switch (card_number) {// perform actions according to user input
            case 1:{ // peep AI cards           
                while (peep < 2 || peep > 4){
                    cout << "Enter the AI player number you want to peep (2 - 4): ";
                    cin >> peep;
                    switch (peep){ // You should not peep dead player's card, right?
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
                    case 2: PrintAICard(cardsAI1); break;
                    case 3: PrintAICard(cardsAI2); break;
                    case 4: PrintAICard(cardsAI3); break;
                }
                break;
            }
            case 2:{ // Exchange cards
                cout << "Your current card: ";
                PrintAICard(cards);
                while (choice < 2 || choice > 4){
                    cout << "Choose the AI player number you want to exchange cards with (2 - 4): ";
                    cin >> choice;
                    switch (choice){ // You should not exchange cards with a dead player, right?
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
                cout << "Your current card: "; // Show your card after the exchange
                PrintAICard(cards);
                break;
            }
            case 3:{ // Discard Card
                cout << "Your current card: ";
                PrintAICard(cards);
                do{
                    cout << "Choose the card you want to discard (No.): ";
                    cin >> choice;
                    if (cards[choice-1] == -1) cout << "You are choosing a blank card, try again" << endl;
                }while (choice < 1 || cards[choice-1] == -1);
                for(int i=0; i<20; i++){ // Delete the card from card list by assigning cards[j] = cards[j+1]
                    if(i == choice-1){
                        for(int j=i; j<(20-1); j++) cards[j] = cards[j+1];
                        cout << "Discard success" << endl;
                        break;
                    }
                }
                cout << "Your current card: "; 
                PrintAICard(cards);
                break;
            }
            case 4:{ // Hand over card
                cout << "Your current card: ";
                PrintAICard(cards);
                while (choice < 2 || choice > 4 ){
                    cout << "Choose the AI player you want to give card to (2 - 4): ";
                    cin >> choice;
                    switch (choice){ // You should not give card to a dead player, right?
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
                    case 2: HandCard(cards, cardsAI1, 20); break;
                    case 3: HandCard(cards, cardsAI2, 20); break;
                    case 4: HandCard(cards, cardsAI3, 20); break;
                }  
                cout << "Your current card: ";
                PrintAICard(cards);
                break;
            }
        }
    }
    return gold;
}
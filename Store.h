#ifndef STORE_H
#define STORE_H

bool Judge(int cardsAI[]);
void PrintAICard(int cardsAI[]);
void SwapCard(int cards[], int cardAI[]);
void HandCard(int cards[], int cardAI[], int size);
int Store(int gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int size);

#endif
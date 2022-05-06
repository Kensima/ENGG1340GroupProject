#ifndef FILEIO_H
#define FILEIO_H

void SaveFile(int gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int number, int judge[], int &size);
void ReadFile(int &gold, int cards[], int cardsAI1[], int cardsAI2[], int cardsAI3[], int &number, int judge[], int &size);

#endif
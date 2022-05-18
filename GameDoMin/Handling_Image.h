#ifndef HANDLING_IMAGE_H_INCLUDE
#define HANDLING_IMAGE_H_INCLUDE

#include "map.h"
#include "Image.h"
#include "Time_Game_Min.h"

extern int timeGame;
extern int difficulry;
extern int timeMin[4];
extern int flagNumber;

extern Image(imageNumber[11][2]);
extern Image minesweeper;
extern Image house;
extern Image win;
extern Image lose;
extern Image tutorialContent;
extern Image gameDifficulry;
extern Image blank;
extern Image soundOff;
extern Image startGame;
extern Image tutorial;
extern Image easy;
extern Image medium;
extern Image hard;
extern Image veryHard;

bool loadMedia();
void showTotalImage();
void showBomb(const int &x, const int &y, const bool &checkSound, bool &checkHouse, bool &playAgain);
void closeImage();
#endif
#ifndef HANDLING_IMAGE_H_INCLUDE
#define HANDLING_IMAGE_H_INCLUDE

#include "map.h"
#include "Image.h"
#include "Time_Game_Min.h"

extern int timeGame;
extern int difficulry;
extern int timeMin[4];
extern int flagNumber;

bool loadMedia();
void showTotalImage();
void showBomb(const int &x, const int &y, const bool &checkSound);
void closeImage();
#endif
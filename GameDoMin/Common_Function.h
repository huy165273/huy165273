#ifndef COMMON_FUNCTION_H_INCLUDE
#define COMMON_FUNCTION_H_INCLUDE

#include <iostream>
#include <fstream>
#include <cstring>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

static const int SIZE_HEIGHT_MAX = 15;
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 600;

 extern SDL_Window *gWindow ;
 extern SDL_Surface *gScreenSurface ; // bề mặt của cửa sổ
 
 extern SDL_Surface *fontText;
 extern TTF_Font *gFontText ;
 extern Mix_Chunk * gSoundClick[3];
 extern Mix_Chunk * gSoundBomb;
 extern Mix_Chunk *gSoundWin;
 extern Mix_Chunk *gSoundLose;
 using namespace std;
namespace SDLCommonFunction
{
    bool init();
    void close();
    SDL_Surface *loadImage(string path);
    void showImage(SDL_Surface *image, const int &x, const int &y, const int &h, const int &w);
    void showText(int time, const int&x, const int &y);
    bool loadSound();
    void showSound(Mix_Chunk *gSoundl, const bool &checkSound);
}

#endif
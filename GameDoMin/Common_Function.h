#ifndef COMMON_FUNCTION_H_INCLUDE
#define COMMON_FUNCTION_H_INCLUDE

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

static const int SIZE_HEIGHT_MAX = 15;
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 600;

 extern SDL_Window *gWindow ;
 extern SDL_Surface *gScreenSurface ; // bề mặt của cửa sổ
 extern SDL_Surface *(imageNumber[11][2]); 
 extern SDL_Surface *domin ;
 extern SDL_Surface *house ;
 extern SDL_Surface *win ;
 extern SDL_Surface *lose ;
 extern SDL_Surface *huongDan ;
 extern SDL_Surface *gameDifficulry;
 extern SDL_Surface *trong;
 extern SDL_Surface *soundOff;
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
    bool loadMedia();
    void close();
    SDL_Surface *loadImage(string path);
    void showImage(SDL_Surface *image, const int &x, const int &y, const int &h, const int &w);
    void showText(int time, const int&x, const int &y);
}

#endif
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "map.h"
using namespace std;

const int SIZE_WIDTH_MAX = 30;
const int SIZE_HEIGHT_MAX = 15;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int amount_image = 9;
const int image_number_max = 8;

bool init();
bool loadMedia();
void close();
void showImage();
void youLose();
void youWin();
void buttonLeft(bool &check);
void buttonRight();

SDL_Surface *loadImage(string path);
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;           // bề mặt của cửa sổ
SDL_Surface *(imageNumber[image_number_max]); // các ảnh số
SDL_Surface *house = NULL;
SDL_Surface *bom = NULL;
SDL_Surface *co = NULL;
SDL_Surface *hoicham = NULL;
SDL_Surface *win = NULL;
SDL_Surface *lose = NULL;

int mapWidth = 10;
int mapHeight = 10;
int **map = new int *[SIZE_HEIGHT_MAX];
int **showMap = new int *[SIZE_HEIGHT_MAX];
int **tickMap = new int *[SIZE_HEIGHT_MAX];
void playGame();

int main(int arc, char *argv[])
{
    playGame();
    if (!init())
    {
        cout << "Failed to init." << endl;
    }
    else
    {
        if (!loadMedia())
        {
            cout << "Failed to load media." << endl;
        }
        else
        {
            bool quit = false;
            bool check = true;
            SDL_Event e;
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                while (check)
                {
                    while (SDL_PollEvent(&e) != 0)
                    {
                        // User requests quit
                        if (e.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                        else
                        {
                            if (e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                if (e.button.button == SDL_BUTTON_LEFT)
                                {
                                    buttonLeft(check);
                                }
                                if (e.button.button == SDL_BUTTON_RIGHT)
                                {
                                    buttonRight();
                                }
                            }
                        }
                        if (check)
                            showImage();
                        SDL_UpdateWindowSurface(gWindow);
                    }
                    if (quit)
                        break;
                }
            }
        }
    }
    return 0;
}
bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO < 0))
    {
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Do Min", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            if (gScreenSurface == NULL)
            {
                success = false;
            }
        }
    }
    return success;
}
void close()
{
    SDL_FreeSurface(house);
    house = NULL;
    SDL_FreeSurface(bom);
    bom = NULL;
    SDL_FreeSurface(co);
    co = NULL;
    SDL_FreeSurface(hoicham);
    hoicham = NULL;
    for (int i = 0; i < image_number_max; i++)
    {
        SDL_FreeSurface(imageNumber[i]);
        imageNumber[i] = NULL;
    }
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
bool loadMedia()
{
    bool success = true;
    string path;
    ifstream file;
    file.open("file_image.txt");
    if (!file)
    {
        cout << "Failed to open file." << endl;
    }
    else
    {
        file >> path;
        house = loadImage(path);
        file >> path;
        bom = loadImage(path);
        file >> path;
        co = loadImage(path);
        file >> path;
        hoicham = loadImage(path);
        for (int i = 0; i < image_number_max; i++)
        {
            file >> path;
            imageNumber[i] = loadImage(path);
            if (imageNumber[i] == NULL)
            {
                success = false;
                cout << "Failed to load image: " << path << endl;
            }
        }
        file >> path;
        win = loadImage(path);
        file >> path;
        lose = loadImage(path);
    }
    return success;
}
SDL_Surface *loadImage(string path)
{
    SDL_Surface *optimizeSurface = NULL;
    SDL_Surface *loadSurface = SDL_LoadBMP(path.c_str());
    if (loadSurface != NULL)
    {
        optimizeSurface = SDL_ConvertSurface(loadSurface, gScreenSurface->format, 0);
        SDL_FreeSurface(loadSurface);
    }
    else
    {
        cout << "Failed to load surface." << endl;
    }
    return optimizeSurface;
}
void playGame()
{
    int x, y;
    mapInitialization(map, mapWidth, mapHeight);
    showMapInitialization(showMap, mapWidth, mapHeight);
    mapInitialization(tickMap, mapWidth, mapHeight);
    randomBombMap(map, mapWidth, mapHeight, 20);
    numberInMap(map, mapWidth, mapHeight);
}
void showImage()
{
    SDL_Rect stretch;
    stretch.x = 0;
    stretch.y = 0;
    stretch.h = SCREEN_HEIGHT;
    stretch.w = SCREEN_WIDTH;
    SDL_BlitScaled(house, NULL, gScreenSurface, &stretch);
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            stretch.x = 275 + 45 * j;
            stretch.y = 125 + 45 * i;
            stretch.w = 45;
            stretch.h = 45;
            if (map[i][j] >= -1 && map[i][j] <= 6)
            {
                SDL_BlitScaled(imageNumber[showMap[i][j] + 1], NULL, gScreenSurface, &stretch);
            }
            if(tickMap[i][j]==1){
                SDL_BlitScaled(co, NULL, gScreenSurface, &stretch);
            }else{
                if(tickMap[i][j]==2){
                    SDL_BlitScaled(hoicham, NULL, gScreenSurface, &stretch);
                }
            }
        }
    }
}
void youLose()
{
    SDL_Rect stretch;
    stretch.x = 275;
    stretch.y = 300;
    stretch.h = 100;
    stretch.w = 450;
    SDL_BlitScaled(lose, NULL, gScreenSurface, &stretch);
}
void youWin()
{
    SDL_Rect stretch;
    stretch.x = 275;
    stretch.y = 300;
    stretch.h = 100;
    stretch.w = 450;
    SDL_BlitScaled(win, NULL, gScreenSurface, &stretch);
}
void buttonLeft(bool &check)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= 275 && x <= 725 && y >= 125 && y <= 575)
    {
        x = (x - 275) / 45;
        y = (y - 125) / 45;
        if (checkBomb(x, y, map) && checkMap(map, showMap, mapWidth, mapHeight))
        {
            check = false;
        }
        else
        {
            editShowMap(x, y, map, showMap, mapWidth, mapHeight);
        }
        if (checkBomb(x, y, map))
        {
            showImage();
            youLose();
        }
        /*if (checkMap(map, showMap, mapWidth, mapHeight)){
            showImage();
            youWin();
        }*/
    }
}
void buttonRight()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= 275 && x <= 725 && y >= 125 && y <= 575)
    {
        x = (x - 275) / 45;
        y = (y - 125) / 45;
        if(tickMap[y][x]==0 || tickMap[y][x]==1){
            tickMap[y][x]++;
        }
        else{
            tickMap[y][x]=0;
        }
    }
}
// hàm checkmap cần phải xem lại
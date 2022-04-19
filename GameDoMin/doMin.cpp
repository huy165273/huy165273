#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "map.h"
using namespace std;
struct specifications
{
    int xStart;
    int yStart;
    int mapHeight;
    int mapWidth;
    int sizeSquare;
    int numberBomb;
    specifications(int xStart_, int yStart_, int mapHeight_, int mapWidth_, int sizeSquare_, int numberBomb_)
        : xStart(xStart_), yStart(yStart_), mapHeight(mapHeight_), mapWidth(mapWidth_), sizeSquare(sizeSquare_), numberBomb(numberBomb_) {}
    specifications(){};
};

const specifications arraySpecifications[4] = {{275, 125, 10, 10, 45, 20},
                                               {100, 150, 10, 20, 40, 40},
                                               {200, 125, 15, 20, 30, 60},
                                               {50, 125, 15, 30, 30, 100}};
const int SIZE_WIDTH_MAX = 30;
const int SIZE_HEIGHT_MAX = 15;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int amount_image = 9;

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
SDL_Surface *gScreenSurface = NULL; // bề mặt của cửa sổ
SDL_Surface *(imageNumber[11][2]);  // các ảnh số
SDL_Surface *house = NULL;
SDL_Surface *win = NULL;
SDL_Surface *lose = NULL;

specifications gameSpecifications = arraySpecifications[0];
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
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_FreeSurface(imageNumber[i][j]);
            imageNumber[i][j]= NULL;
        }
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
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                file >> path;
                imageNumber[i][j] = loadImage(path);
                if (imageNumber[i][j] == NULL)
                {
                    success = false;
                    cout << "Failed to load image: " << path << endl;
                }
            }
        }
        file >> path;
        win = loadImage(path);
        file >> path;
        lose = loadImage(path);
        file >> path;
        house = loadImage(path);
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
    mapInitialization(map, gameSpecifications.mapWidth, gameSpecifications.mapHeight);
    showMapInitialization(showMap, gameSpecifications.mapWidth, gameSpecifications.mapHeight);
    mapInitialization(tickMap, gameSpecifications.mapWidth, gameSpecifications.mapHeight);
    randomBombMap(map, gameSpecifications.mapWidth, gameSpecifications.mapHeight, gameSpecifications.numberBomb);
    numberInMap(map, gameSpecifications.mapWidth, gameSpecifications.mapHeight);
}
void showImage()
{
    SDL_Rect stretch;
    stretch.x = 0;
    stretch.y = 0;
    stretch.h = SCREEN_HEIGHT;
    stretch.w = SCREEN_WIDTH;
    SDL_BlitScaled(house, NULL, gScreenSurface, &stretch);
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            stretch.x = gameSpecifications.xStart + gameSpecifications.sizeSquare * j;
            stretch.y = gameSpecifications.yStart + gameSpecifications.sizeSquare * i;
            stretch.w = gameSpecifications.sizeSquare;
            stretch.h = gameSpecifications.sizeSquare;
            if (map[i][j] >= -1 && map[i][j] <= 6)
            {
                SDL_BlitScaled(imageNumber[showMap[i][j] + 1][(i+j)%2], NULL, gScreenSurface, &stretch);
            }
            if (tickMap[i][j] == 1)
            {
                SDL_BlitScaled(imageNumber[8][(i+j)%2], NULL, gScreenSurface, &stretch);
            }
            else
            {
                if (tickMap[i][j] == 2)
                {
                    SDL_BlitScaled(imageNumber[9][(i+j)%2], NULL, gScreenSurface, &stretch);
                }
            }
        }
    }
}
void youLose()
{
    SDL_Rect stretch;
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            if (map[i][j] == -1)
            {
                stretch.x = gameSpecifications.xStart + gameSpecifications.sizeSquare * j;
                stretch.y = gameSpecifications.yStart + gameSpecifications.sizeSquare * i;
                stretch.w = gameSpecifications.sizeSquare;
                stretch.h = gameSpecifications.sizeSquare;
                SDL_BlitScaled(imageNumber[10][(i+j)%2], NULL, gScreenSurface, &stretch);
            }
        }
    }
    stretch.x = gameSpecifications.xStart;
    stretch.y = 300;
    stretch.h = 100;
    stretch.w = gameSpecifications.sizeSquare * gameSpecifications.mapWidth;
    SDL_BlitScaled(lose, NULL, gScreenSurface, &stretch);
}
void youWin()
{
    SDL_Rect stretch;
    stretch.x = gameSpecifications.xStart;
    stretch.y = 300;
    stretch.h = 100;
    stretch.w = gameSpecifications.sizeSquare * gameSpecifications.mapWidth;
    SDL_BlitScaled(win, NULL, gScreenSurface, &stretch);
}
void buttonLeft(bool &check)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= gameSpecifications.xStart && x <= gameSpecifications.xStart + gameSpecifications.mapWidth * gameSpecifications.sizeSquare && y >= gameSpecifications.yStart && y <= gameSpecifications.yStart + gameSpecifications.mapHeight * gameSpecifications.sizeSquare)
    {
        x = (x - gameSpecifications.xStart) / gameSpecifications.sizeSquare;
        y = (y - gameSpecifications.yStart) / gameSpecifications.sizeSquare;
        if (checkBomb(x, y, map))
        {
            check = false;
        }
        else
        {
            editShowMap(x, y, map, showMap, gameSpecifications.mapWidth, gameSpecifications.mapHeight);
        }
        if (checkBomb(x, y, map))
        {
            showImage();
            youLose();
        }
        if (checkMap(map, showMap, gameSpecifications.mapWidth, gameSpecifications.mapHeight))
        {
            check = false;
            showImage();
            youWin();
        }
    }
}
void buttonRight()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= gameSpecifications.xStart && x <= gameSpecifications.xStart + gameSpecifications.mapWidth * gameSpecifications.sizeSquare && y >= gameSpecifications.yStart && y <= gameSpecifications.yStart + gameSpecifications.mapHeight * gameSpecifications.sizeSquare)
    {
        x = (x - gameSpecifications.xStart) / gameSpecifications.sizeSquare;
        y = (y - gameSpecifications.yStart) / gameSpecifications.sizeSquare;
        if (tickMap[y][x] == 0 || tickMap[y][x] == 1)
        {
            tickMap[y][x]++;
        }
        else
        {
            tickMap[y][x] = 0;
        }
    }
}
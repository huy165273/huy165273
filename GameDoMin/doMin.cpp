#include "Common_Function.h"
#include "map.h"
using namespace std;

void showTotalImage();
void startGame();
bool page1(bool &checkHouse, bool &checkSound, bool &quit);
bool page2(int &diffculry, bool &checkHouse, const bool &checkSound, bool &quit);
bool page3(bool &quit, const bool &checkSound);
void buttonRight(const bool &checkSound);
void youLose(const int &x, const int &y, const bool &checkSound);
void youWin(const bool &checkSound);
void writeTimeGameMin();
void readTimeGameMin();
void DeleteMap(int **map, int SIZE_HEIGHT_MAX);

int timeGame;
int Time;
int difficulry;
int timeMin[4];
int flagNumber;
specifications gameSpecifications;

int main(int arc, char *argv[])
{
    if (!SDLCommonFunction::init())
    {
        cout << "Failed to init." << endl;
    }
    else
    {
        if (!SDLCommonFunction::loadMedia())
        {
            cout << "Failed to load media." << endl;
        }
        else
        {
            bool checkPage1 = false, checkPage2 = false;
            bool checkHouse = false, quit = false, playAgain = false;
            bool checkSound = true;
            while (!quit)
            {
                if (checkHouse)
                {
                    checkPage1 = false;
                    checkPage2 = false;
                }
                if (!checkPage1 || checkHouse)
                {
                    checkPage1 = page1(checkHouse, checkSound, quit);
                }
                else if (!checkPage2)
                {
                    checkPage2 = page2(difficulry, checkHouse, checkSound, quit);
                }
                else
                {
                    gameSpecifications = arraySpecifications[difficulry];
                    do
                    {
                        startGame();
                        playAgain = false;
                        if (page3(quit, checkSound))
                        {
                            checkHouse = true;
                        }
                        else
                        {
                            playAgain = true;
                        }
                    } while (playAgain);
                }
            }
        }
    }
    DeleteMap(map, SIZE_HEIGHT_MAX);
    DeleteMap(showMap, SIZE_HEIGHT_MAX);
    DeleteMap(tickMap, SIZE_HEIGHT_MAX);
    SDLCommonFunction::close();
    return 0;
}
void showTotalImage()
{
    SDLCommonFunction::showImage(domin, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    SDLCommonFunction::showText(flagNumber, 685, 55);
    SDLCommonFunction::showText(timeGame, 435, 55);
    if (timeMin[difficulry] != 9999)
    {
        SDLCommonFunction::showText(timeMin[difficulry], 565, 55);
    }
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            int x = gameSpecifications.xStart + gameSpecifications.sizeSquare * j;
            int y = gameSpecifications.yStart + gameSpecifications.sizeSquare * i;
            int w = gameSpecifications.sizeSquare;
            int h = gameSpecifications.sizeSquare;
            SDLCommonFunction::showImage(imageNumber[showMap[i][j] + 1][(i + j) % 2], x, y, h, w);
            if (tickMap[i][j] == 1 && showMap[i][j] == -1)
            {
                SDLCommonFunction::showImage(imageNumber[8][(i + j) % 2], x, y, h, w);
            }
            else

                if (tickMap[i][j] == 2 && showMap[i][j] == -1)
            {
                SDLCommonFunction::showImage(imageNumber[9][(i + j) % 2], x, y, h, w);
            }
        }
    }
}
void startGame()
{
    mapInitialization(map);
    showMapInitialization( );
    mapInitialization(tickMap);
    randomBombMap();
    numberInMap();
}
bool page1(bool &checkHouse, bool &checkSound, bool &quit)
{
    checkHouse = false;
    bool pageHouse = true;
    SDL_Event e;
    while (true)
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
                    if (checkSound)
                        Mix_PlayChannel(-1, gSoundClick[0], 0);
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (pageHouse)
                    {
                        if (x >= 800 && x <= 875 && y >= 50 && y <= 125)
                        {
                            checkSound = !checkSound;
                        }
                        if (x >= 300 && x <= 700 && y >= 250 && y <= 350)
                        {
                            return true;
                        }
                        else if (x >= 300 && x <= 700 && y >= 400 && y <= 500)
                        {
                            pageHouse = false;
                        }
                    }
                    else
                    {
                        if (x >= 850 && x <= 925 && y >= 25 && y <= 100)
                        {
                            pageHouse = true;
                        }
                    }
                }
            }
            if (pageHouse)
            {
                SDLCommonFunction::showImage(house, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
                if (!checkSound)
                {
                    SDLCommonFunction::showImage(soundOff, 800, 50, 75, 75);
                }
            }
            else
            {
                SDLCommonFunction::showImage(huongDan, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
            }
            SDL_UpdateWindowSurface(gWindow);
        }
        if (quit)
            break;
    }
}
bool page2(int &difficulry, bool &checkHouse, const bool &checkSound, bool &quit)
{
    SDL_Event e;
    while (true)
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
                    if (checkSound)
                    {
                        Mix_PlayChannel(-1, gSoundClick[0], 0);
                    }
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= 400 && x <= 600 && y >= 275 && y <= 325)
                    {
                        difficulry = 0;
                        return true;
                    }
                    if (x >= 400 && x <= 600 && y >= 350 && y <= 400)
                    {
                        difficulry = 1;
                        return true;
                    }
                    if (x >= 400 && x <= 600 && y >= 425 && y <= 475)
                    {
                        difficulry = 2;
                        return true;
                    }
                    if (x >= 400 && x <= 600 && y >= 500 && y <= 550)
                    {
                        difficulry = 3;
                        return true;
                    }
                    if (x >= 850 && x <= 925 && y >= 25 && y <= 100)
                    {
                        checkHouse = true;
                        return true;
                    }
                }
            }
            SDLCommonFunction::showImage(gameDifficulry, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
            SDL_UpdateWindowSurface(gWindow);
        }
        if (quit)
            break;
    }
}
bool page3(bool &quit, const bool &checkSound)
{
    readTimeGameMin();
    Time = SDL_GetTicks() / 1000;
    int timeGameStart = Time;
    flagNumber = gameSpecifications.numberBomb;
    bool check = true;
    SDL_Event e;
    showTotalImage();
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                // timeGame=SDL_GetTicks()/1000;
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        if (check && x >= gameSpecifications.xStart && x <= gameSpecifications.xStart + gameSpecifications.mapWidth * gameSpecifications.sizeSquare && y >= gameSpecifications.yStart && y <= gameSpecifications.yStart + gameSpecifications.mapHeight * gameSpecifications.sizeSquare)
                        {
                            x = (x - gameSpecifications.xStart) / gameSpecifications.sizeSquare;
                            y = (y - gameSpecifications.yStart) / gameSpecifications.sizeSquare;
                            if (tickMap[y][x] != 1)
                            {
                                if (checkBomb(x, y))
                                {
                                    if (check)
                                    {
                                        youLose(x, y, checkSound);
                                    }
                                    check = false;
                                }
                                else
                                {
                                    if (checkSound)
                                    {
                                        if (map[y][x] > 0)
                                        {
                                            Mix_PlayChannel(-1, gSoundClick[1], 0);
                                        }
                                        else
                                        {
                                            Mix_PlayChannel(-1, gSoundClick[2], 0);
                                        }
                                    }
                                    editShowMap(x, y);
                                }
                                if (checkMap())
                                {
                                    check = false;
                                    showTotalImage();
                                    youWin(checkSound);
                                }
                            }
                        }
                        if (x >= 850 && x <= 925 && y >= 25 && y <= 100)
                        {
                            if (checkSound)
                            {
                                Mix_PlayChannel(-1, gSoundClick[0], 0);
                            }
                            return true;
                        }
                        if (x >= 750 && x <= 825 && y >= 25 && y <= 100)
                        {
                            if (checkSound)
                            {
                                Mix_PlayChannel(-1, gSoundClick[0], 0);
                            }
                            return false;
                        }
                    }
                    if (e.button.button == SDL_BUTTON_RIGHT)
                    {
                        buttonRight(checkSound);
                    }
                    if (check)
                        showTotalImage();
                }
            }
        }
        if (check)
            Time = SDL_GetTicks() / 1000;
        timeGame = Time - timeGameStart;
        SDLCommonFunction::showImage(trong, 430, 50, 50, 50);
        SDLCommonFunction::showText(timeGame, 435, 55);
        SDL_UpdateWindowSurface(gWindow);
        if (quit)
            break;
    }
}
void buttonRight(const bool &checkSound)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= gameSpecifications.xStart && x <= gameSpecifications.xStart + gameSpecifications.mapWidth * gameSpecifications.sizeSquare && y >= gameSpecifications.yStart && y <= gameSpecifications.yStart + gameSpecifications.mapHeight * gameSpecifications.sizeSquare)
    {
        x = (x - gameSpecifications.xStart) / gameSpecifications.sizeSquare;
        y = (y - gameSpecifications.yStart) / gameSpecifications.sizeSquare;
        if (showMap[y][x] == -1)
        {
            if (checkSound)
            {
                Mix_PlayChannel(-1, gSoundClick[0], 0);
            }
            switch (tickMap[y][x])
            {
            case 0:
                if (flagNumber > 0)
                {
                    tickMap[y][x]++;
                    flagNumber--;
                }
                break;
            case 1:
                tickMap[y][x]++;
                flagNumber++;
                break;
            case 2:
                tickMap[y][x] = 0;
                break;
            default:
                break;
            }
        }
    }
}
void youLose(const int &x, const int &y, const bool &checkSound)
{
    SDL_Rect stretch;
    stretch.x = gameSpecifications.xStart + gameSpecifications.sizeSquare * x;
    stretch.y = gameSpecifications.yStart + gameSpecifications.sizeSquare * y;
    stretch.w = gameSpecifications.sizeSquare;
    stretch.h = gameSpecifications.sizeSquare;
    SDL_BlitScaled(imageNumber[10][(x + y) % 2], NULL, gScreenSurface, &stretch);
    if (checkSound)
    {
        Mix_PlayChannel(-1, gSoundBomb, 0);
    }
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(500);
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            if (map[i][j] == -1 && (i != y || j != x))
            {
                stretch.x = gameSpecifications.xStart + gameSpecifications.sizeSquare * j;
                stretch.y = gameSpecifications.yStart + gameSpecifications.sizeSquare * i;
                stretch.w = gameSpecifications.sizeSquare;
                stretch.h = gameSpecifications.sizeSquare;
                SDL_BlitScaled(imageNumber[10][(i + j) % 2], NULL, gScreenSurface, &stretch);
                SDL_UpdateWindowSurface(gWindow);
                if (checkSound)
                {
                    Mix_PlayChannel(-1, gSoundBomb, 0);
                }
                SDL_Delay(500);
            }
        }
    }
    stretch.x = gameSpecifications.xStart;
    stretch.y = 300;
    stretch.h = 100;
    stretch.w = gameSpecifications.sizeSquare * gameSpecifications.mapWidth;
    SDL_BlitScaled(lose, NULL, gScreenSurface, &stretch);
    if (checkSound)
    {
        Mix_PlayChannel(-1, gSoundLose, 0);
    }
}
void youWin(const bool &checkSound)
{
    if (checkSound)
    {
        Mix_PlayChannel(-1, gSoundWin, 0);
    }
    SDL_Rect stretch;
    stretch.x = gameSpecifications.xStart;
    stretch.y = 300;
    stretch.h = 100;
    stretch.w = gameSpecifications.sizeSquare * gameSpecifications.mapWidth;
    SDL_BlitScaled(win, NULL, gScreenSurface, &stretch);
    if (timeMin[difficulry] > timeGame)
    {
        timeMin[difficulry] = timeGame;
    }
    writeTimeGameMin();
}
void readTimeGameMin()
{
    string path;
    ifstream file;
    file.open("time_game_min.txt");
    if (!file)
    {
        cout << "Failed to open file." << endl;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            file >> timeMin[i];
        }
    }
    file.close();
}
void writeTimeGameMin()
{
    string path;
    ofstream file;
    file.open("time_game_min.txt", ios::out | ios::trunc);
    if (!file)
    {
        cout << "Failed to open file." << endl;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            file << timeMin[i] << endl;
        }
    }
    file.close();
}


#include "Common_Function.h"
#include "Handling_Image.h"
using namespace std;

void gameInit();
bool page1(bool &checkHouse, bool &checkSound, bool &quit);
bool page2(int &diffculry, bool &checkHouse, const bool &checkSound, bool &quit);
bool page3(bool &quit, const bool &checkSound);
void buttonRight(const bool &checkSound);
void youLose(const int &x, const int &y, const bool &checkSound);
void youWin(const bool &checkSound);

int timeGame;
int Time;
int difficulry;
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
        if (!loadMedia()&& !SDLCommonFunction::loadSound())
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
                        gameInit();
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
    DeleteMap();
    closeImage();
    SDLCommonFunction::close();
    return 0;
}

void gameInit()
{
    mapInitialization(map);
    showMapInitialization();
    mapInitialization(tickMap);
    randomBombMap();
    numberInMap();
}
bool page1(bool &checkHouse, bool &checkSound, bool &quit)
{
    checkHouse = false;
    bool pageHouse = true;
    SDL_Event e;
    house.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    house.Show();
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
                if (e.type == SDL_MOUSEMOTION)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= 300 && x <= 700 && y >= 250 && y <= 350)// Bắt đầu chơi
                    {

                        startGame.SetRect(300, 250, 400, 100);
                        startGame.Show();
                    }
                    else if (x >= 300 && x <= 700 && y >= 400 && y <= 500)// hướng dẫn
                    {
                        tutorial.SetRect(300, 400, 400, 100);
                        tutorial.Show();
                    }
                    else
                    {
                        house.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                        house.Show();
                    }
                }
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (pageHouse)
                    {
                        if (x >= 760 && x <= 860 && y >= 30 && y <= 120)// tắt bật âm thanh
                        {
                            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                            checkSound = !checkSound;
                        }
                        if (x >= 300 && x <= 700 && y >= 250 && y <= 350)//  bắt đầu chơi
                        {
                            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                            return true;
                        }
                        else if (x >= 300 && x <= 700 && y >= 400 && y <= 500)// hướng dẫn
                        {
                            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                            pageHouse = false;
                        }
                    }
                    else
                    {
                        if (x >= 895 && x <= 965 && y >= 40 && y <= 110) // trở về
                        {
                            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                            pageHouse = true;
                        }
                    }
                }
            }
            if (pageHouse)
            {
                if (!checkSound)
                {
                    soundOff.SetRect(748, 28, 124, 97);
                    soundOff.Show();
                }
            }
            else
            {
                tutorialContent.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                tutorialContent.Show();
            }
            SDL_UpdateWindowSurface(gWindow);
        }
        if (quit)
            break;
    }
}
bool page2(int &difficulry, bool &checkHouse, const bool &checkSound, bool &quit)
{
    gameDifficulry.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gameDifficulry.Show();
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= 400 && x <= 600 && y >= 275 && y <= 325)// độ khó: dễ
                {
                    easy.SetRect(400, 275, 200, 50);
                    easy.Show();
                }
                else if (x >= 400 && x <= 600 && y >= 350 && y <= 400)// độ khó: trung bình
                {
                    medium.SetRect(400, 350, 200, 50);
                    medium.Show();
                }
                else if (x >= 400 && x <= 600 && y >= 425 && y <= 475) // độ khó: khó
                {
                    hard.SetRect(400, 425, 200, 50);
                    hard.Show();
                }
                else if (x >= 400 && x <= 600 && y >= 500 && y <= 550)// độ khó: rất khó
                {
                    veryHard.SetRect(400, 500, 200, 50);
                    veryHard.Show();
                }
                else
                {
                    gameDifficulry.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    gameDifficulry.Show();
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= 400 && x <= 600 && y >= 275 && y <= 325)// độ khó: dễ
                {
                    SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                    difficulry = 0;
                    return true;
                }
                if (x >= 400 && x <= 600 && y >= 350 && y <= 400) // độ khó: trung bình
                {
                    SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                    difficulry = 1;
                    return true;
                }
                if (x >= 400 && x <= 600 && y >= 425 && y <= 475)// độ khó: khó
                {
                    SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                    difficulry = 2;
                    return true;
                }
                if (x >= 400 && x <= 600 && y >= 500 && y <= 550) // độ khó: rất khó
                {
                    SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                    difficulry = 3;
                    return true;
                }
                if (x >= 895 && x <= 965 && y >= 40 && y <= 110) // trở về
                {
                    SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                    checkHouse = true;
                    return true;
                }
            }
        }
        SDL_UpdateWindowSurface(gWindow);
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
                                    youLose(x, y, checkSound);
                                    check = false;
                                }
                                else
                                {
                                    if (showMap[y][x] == -1)
                                    {
                                        if (map[y][x] > 0)
                                        {
                                            SDLCommonFunction::showSound(gSoundClick[1], checkSound);
                                        }
                                        else
                                        {
                                            SDLCommonFunction::showSound(gSoundClick[2], checkSound);
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
                        if (x >= 890 && x <= 965 && y >= 35 && y <= 110) // trở về
                        {
                            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
                            return true;
                        }
                        if (x >= 795 && x <= 870 && y >= 35 && y <= 110) // chơi lại
                        {
                            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
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
        blank.SetRect(468, 50, 50, 50);
        blank.Show();
        SDLCommonFunction::showText(timeGame, 473, 55);
        SDL_UpdateWindowSurface(gWindow);
        SDL_Delay(1);
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
            SDLCommonFunction::showSound(gSoundClick[0], checkSound);
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
    showBomb(x, y, checkSound);
    lose.SetRect(gameSpecifications.xStart, 300, gameSpecifications.sizeSquare * gameSpecifications.mapWidth, 100);
    lose.Show();
    SDLCommonFunction::showSound(gSoundLose, checkSound);
}
void youWin(const bool &checkSound)
{
    SDLCommonFunction::showSound(gSoundWin, checkSound);
    win.SetRect(gameSpecifications.xStart, 300, gameSpecifications.sizeSquare * gameSpecifications.mapWidth, 100);
    win.Show();
    if (timeMin[difficulry] > timeGame)
    {
        timeMin[difficulry] = timeGame;
    }
    writeTimeGameMin();
}

#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "array_manipulation.h"
#include "end_game.h"
using namespace std;

const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 600;
const int FIRST_NUMBER_COORDINATE_X = 25;
const int FIRST_NUMBER_COORDINATE_Y = 150;
const int SUM_SIZE_NUMBER = 400; // kích thước tổng các số
const int amount_image = 19;

const int size_max = 8;
const int size_min = 3;
int **array = new int *[size_max];
int **arrayBefore = new int *[size_max];
int score = 0;
int gameSize;

void randomNumber();

bool init();
bool loadMedia();
void close();

void screenSurface();
void showScore();
void showHighScore();
void chooseGame(SDL_Event &e, bool &play, bool &quit, int &count);
void playGame(SDL_Event &e, bool &quit, int &count, bool &play);
void chooseSize(bool &play, int &count);
void back(const int &x, const int &y);
bool playAgain(const int &x, const int &y);
bool house(const int &x, const int &y);

SDL_Surface *loadImage(string path);
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;           // bề mặt của cửa sổ
SDL_Surface *(gDisplaySurface[amount_image]); // mảng hình ảnh hiển thị

int main(int arc, char *argv[])
{
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
            SDL_Event e;
            bool play = false;
            int count = size_min;
            while (!quit)
            {
                do
                {
                    if (!play)
                    {
                        chooseGame(e, play, quit, count);
                    }
                    else
                    {
                        quit = false;
                        gameSize = count;
                        playGame(e, quit, count, play);
                    }
                } while (!play);
            }
        }
    }
    delete array;
    delete arrayBefore;
    close();
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
        gWindow = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    for (int i = 0; i < amount_image; i++)
    {
        SDL_FreeSurface(gDisplaySurface[i]);
        gDisplaySurface[i] = NULL;
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
        for (int i = 0; i < amount_image; i++)
        {
            file >> path;
            gDisplaySurface[i] = loadImage(path);
            if (gDisplaySurface[i] == NULL)
            {
                success = false;
                cout << "Failed to load image: " << path << endl;
            }
        }
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
void screenSurface()
{
    SDL_Rect stretch;
    SDL_Surface *numberSurface = NULL;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            stretch.x = FIRST_NUMBER_COORDINATE_X + (SUM_SIZE_NUMBER / gameSize) * j;
            stretch.y = FIRST_NUMBER_COORDINATE_Y + (SUM_SIZE_NUMBER / gameSize) * i;
            stretch.w = (SUM_SIZE_NUMBER / gameSize);
            stretch.h = (SUM_SIZE_NUMBER / gameSize);
            switch (array[i][j])
            {
            case 0:
                numberSurface = gDisplaySurface[1];
                break;
            case 2:
                numberSurface = gDisplaySurface[2];
                break;
            case 4:
                numberSurface = gDisplaySurface[3];
                break;
            case 8:
                numberSurface = gDisplaySurface[4];
                break;
            case 16:
                numberSurface = gDisplaySurface[5];
                break;
            case 32:
                numberSurface = gDisplaySurface[6];
                break;
            case 64:
                numberSurface = gDisplaySurface[7];
                break;
            case 128:
                numberSurface = gDisplaySurface[8];
                break;
            case 256:
                numberSurface = gDisplaySurface[9];
                break;
            case 512:
                numberSurface = gDisplaySurface[10];
                break;
            case 1024:
                numberSurface = gDisplaySurface[11];
                break;
            case 2048:
                numberSurface = gDisplaySurface[12];
                break;
            }
            SDL_BlitScaled(numberSurface, NULL, gScreenSurface, &stretch);
            numberSurface = NULL;
        }
    }
}
void chooseSize(bool &play, int &count)
{
    if (!play)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // sang trái
        if (count > size_min)
        {
            if (x >= 100 && x <= 130 && y >= 390 && y <= 420)
                count--;
        }
        // sang phải
        if (count < size_max)
        {
            if (x >= 285 && x <= 305 && y >= 390 && y <= 420)
                count++;
        }
        // bắt đầu
        if (x >= 25 && x <= 425 && y >= 450 && y <= 550)
            play = true;
    }
}
void playGame(SDL_Event &e, bool &quit, int &count, bool &play)
{
    khoiTaoMang(array, arrayBefore, gameSize);
    randomNumber();
    randomNumber();
    do
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                updateArrayBefore(arrayBefore, array, gameSize);
                switch (e.key.keysym.sym)
                {
                case SDLK_UP: // xử lý hàm khi di chuyển lên
                    updateArrayUp(array, gameSize, score);
                    break;
                case SDLK_DOWN: // xử lý hoàm khi di chuyển xuống
                    updateArrayDown(array, gameSize, score);
                    break;
                case SDLK_LEFT: // xử lý hàm khi di chuyển sang trái
                    updateArrayLeft(array, gameSize, score);
                    break;
                case SDLK_RIGHT: // xử lý hàm khi di chuyển sang phải
                    updateArrayRight(array, gameSize, score);
                    break;
                }
                if (!compareArray(arrayBefore, array, gameSize))
                    randomNumber();
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (playAgain(x, y))
                {
                    khoiTaoMang(array, arrayBefore, gameSize);
                    randomNumber();
                    randomNumber();
                }
                if (house(x, y))
                {
                    play = false;
                    count = size_min;
                }
                back(x, y);
            }
        }
        if (!play)
            break;
        SDL_Rect stretch; // kéo căng ra
        stretch.x = 0;
        stretch.y = 0;
        stretch.h = SCREEN_HEIGHT;
        stretch.w = SCREEN_WIDTH;
        SDL_BlitScaled(gDisplaySurface[0], NULL, gScreenSurface, &stretch);
        showHighScore();
        screenSurface();
        showScore();
        SDL_UpdateWindowSurface(gWindow);
    } while ((!gameOver(array, gameSize) || win(array, gameSize)) && play);
}
void chooseGame(SDL_Event &e, bool &play, bool &quit, int &count)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            chooseSize(play, count);
        }
    }
    SDL_Rect stretch; // kéo căng ra
    stretch.x = 0;
    stretch.y = 0;
    stretch.h = SCREEN_HEIGHT;
    stretch.w = SCREEN_WIDTH;
    SDL_BlitScaled(gDisplaySurface[10 + count], NULL, gScreenSurface, &stretch);
    SDL_UpdateWindowSurface(gWindow);
}
void randomNumber()
{
    int count1 = 0, count2 = 0;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
            if (array[i][j] == 0)
                count1++;
    }
    srand(time(nullptr));
    int random = rand() % count1 + 1;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
            if (array[i][j] == 0)
            {
                count2++;
                if (count2 == random)
                {
                    // chọn số cho ô 2 hoặc 4
                    // tạm thời chọn tỉ lệ ra số 4 là 10%
                    int randomNumber = (rand() % 10);
                    if (randomNumber == 0)
                        array[i][j] = 4;
                    else
                        array[i][j] = 2;
                }
            }
    }
}
void back(const int &x, const int &y)
{
    if (x >= 360 && x <= 400 && y >= 100 && y <= 140)
    {
        updateArrayBefore(array, arrayBefore, gameSize);
    }
}
bool playAgain(const int &x, const int &y)
{

    if (x >= 295 && x <= 335 && y >= 100 && y <= 140)
    {
        return true;
    }
    return false;
}
bool house(const int &x, const int &y)
{
    if (x >= 25 && x <= 65 && y >= 100 && y <= 140)
    {
        return true;
    }
    return false;
}
void showScore()
{
}
void showHighScore()
{
}
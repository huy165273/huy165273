#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "array_manipulation.h"
using namespace std;

const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 600;
const int FIRST_NUMBER_COORDINATE_X = 25;
const int FIRST_NUMBER_COORDINATE_Y = 150;
const int SUM_SIZE_NUMBER = 400; // kích thước tổng các số
const int amount_image = 13;

const int size_max = 8;
int **array = new int *[size_max];
int **arrayBefore = new int *[size_max];
int score=0;
int gameSize;
void randomNumber();
bool gameOver();
bool win();
void khoiTaoMang();
int enterGameSize();
void playGame();
int hightScore();


bool init();
bool loadMedia();
void close();
void screenSurface();
void showScore();
void showHighScore();
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
            // playGame();
            gameSize = enterGameSize();
            khoiTaoMang();
            randomNumber();
            randomNumber();
            bool quit = false;
            SDL_Event e;
            do
            {
                while (!quit)
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
                    }

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
                }
            } while (!gameOver() || win());
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

void playGame()
{
    gameSize = enterGameSize();
    khoiTaoMang();
    randomNumber();
    randomNumber();
}
int enterGameSize()
{
    return 8;
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

bool gameOver()
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            if (array[i][j] == 0)
                return false;
        }
    }
    return true;
}
bool win()
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            if (array[i][j] == 2048)
                return true;
        }
    }
    return false;
}
void khoiTaoMang()
{
    for (int i = 0; i < gameSize; i++)
    {
        array[i] = new int[gameSize]();
        arrayBefore[i] = new int[gameSize]();
    }
}
int hightScore(){
    fstream file;
    file.open("diem_cao.txt");
    int higth_score[6];
    for(int i=0;i<6;i++)
    file>>higth_score[i];
    file.close();
    file.open("diem_cao.txt", ios::out | ios::trunc);
    if(score>higth_score[gameSize-3]) higth_score[gameSize-3]=score;
    for(int i=0;i<6;i++)
        file<<higth_score[i]<<endl;
    file.close();
    return higth_score[gameSize-3];
}
void showScore(){

}
void showHighScore(){
    
}

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 600;
const int FIRST_NUMBER_COORDINATE_X = 25;
const int FIRST_NUMBER_COORDINATE_Y = 150;
const int SIZE_NUMBER = 100;
const int amount_image = 13;

const int size_max = 10;
int gameSize;
int array[size_max][size_max];
int arrayBefore[size_max][size_max];
void khoiTaoMang();
int enterGameSize();
void randomNumber();
char enterKey();
bool gameOver();
bool win();
void updateArray(const char &key);
bool compareArray(int (*arrayBefore)[size_max]); // so sánh 2 mảng có giống nhau k
void updateArrayUp();
void updateArrayDown();
void updateArrayRight();
void updateArrayLeft();
void printArray();
void printResult(const char &checkGameOver, const char &checkWin);
void updateArrayBefore(int (*arrayBerfore)[size_max]);
void playGame();

bool init();
bool loadMedia();
void close();
void screenSurface();
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
            playGame();
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
                            updateArrayBefore(arrayBefore);
                            switch (e.key.keysym.sym)
                            {
                            case SDLK_UP: // xử lý hàm khi di chuyển lên
                                updateArrayUp();
                                break;
                            case SDLK_DOWN: // xử lý hoàm khi di chuyển xuống
                                updateArrayDown();
                                break;
                            case SDLK_LEFT: // xử lý hàm khi di chuyển sang trái
                                updateArrayLeft();
                                break;
                            case SDLK_RIGHT: // xử lý hàm khi di chuyển sang phải
                                updateArrayRight();
                                break;
                            }
                            if (!compareArray(arrayBefore))
                                randomNumber();
                        }
                    }

                    SDL_Rect stretch[0]; // kéo căng ra
                    stretch[0].x = 0;
                    stretch[0].y = 0;
                    stretch[0].h = SCREEN_HEIGHT;
                    stretch[0].w = SCREEN_WIDTH;
                    SDL_BlitScaled(gDisplaySurface[0], NULL, gScreenSurface, &stretch[0]);
                    /*for (int i = 1; i <= 3; i++)
                    {
                        for (int j = 1; j <= 4; j++)
                        {
                            stretch[i].x = FIRST_NUMBER_COORDINATE_X + SIZE_NUMBER * (j - 1);
                            stretch[i].y = FIRST_NUMBER_COORDINATE_Y + SIZE_NUMBER * (i - 1);
                            stretch[i].h = SIZE_NUMBER;
                            stretch[i].w = SIZE_NUMBER;
                            SDL_BlitScaled(gDisplaySurface[i], NULL, gScreenSurface, &stretch[i]);
                        }
                    }*/
                    screenSurface();
                    SDL_UpdateWindowSurface(gWindow);
                }
            } while (!gameOver() || win());
        }
    }
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
void screenSurface(){
    SDL_Rect stretch;
    SDL_Surface* numberSurface=NULL;
    for(int i=0;i<gameSize;i++){
        for(int j=0;j<gameSize;j++){
            stretch.x=FIRST_NUMBER_COORDINATE_X+ SIZE_NUMBER*j;
            stretch.y=FIRST_NUMBER_COORDINATE_Y+ SIZE_NUMBER*i;
            stretch.w=SIZE_NUMBER;
            stretch.h=SIZE_NUMBER;
            switch(array[i][j]){
                case 0: 
                    numberSurface=gDisplaySurface[1];
                    break;
                case 2: 
                    numberSurface=gDisplaySurface[2];
                    break;
                case 4: 
                    numberSurface=gDisplaySurface[3];
                    break;
                case 8: 
                    numberSurface=gDisplaySurface[4];
                    break;
                case 16: 
                    numberSurface=gDisplaySurface[5];
                    break;
                case 32: 
                    numberSurface=gDisplaySurface[6];
                    break;
                case 64: 
                    numberSurface=gDisplaySurface[7];
                    break;
                case 128: 
                    numberSurface=gDisplaySurface[8];
                    break;
                case 256: 
                    numberSurface=gDisplaySurface[9];
                    break;
                case 512: 
                    numberSurface=gDisplaySurface[10];
                    break;
                case 1024: 
                    numberSurface=gDisplaySurface[11];
                    break;
                case 2048: 
                    numberSurface=gDisplaySurface[12];
                    break;
            }
            SDL_BlitSurface(numberSurface, NULL, gScreenSurface, &stretch);
        }
    }
}
//
//
//

void playGame()
{
    //bool checkGameOver;
    //bool checkWin;
    gameSize = enterGameSize();
    khoiTaoMang();
    randomNumber();
    randomNumber();
    /*do
    {
        key = enterKey();
        updateArrayBefore(arrayBefore);
        updateArray(key);
        if (!compareArray(arrayBefore))
            randomNumber();
        printArray();
    } while (!gameOver() || win());
    printResult(checkGameOver, checkWin);*/
}
int enterGameSize()
{
    return 4;
}
void randomNumber()
{
    bool check = true;
    int x, y;
    while (check)
    {
        srand(time(nullptr));
        x = rand() % gameSize;
        y = rand() % gameSize;
        if (array[x][y] == 0)
        {
            // chọn số cho ô 2 hoặc 4
            // tạm thời chọn tỉ lệ ra số 4 là 10%
            int randomNumber;
            randomNumber = (rand() % 10);
            if (randomNumber == 0)
                array[x][y] = 4;
            else
                array[x][y] = 2;
            check = false;
        }
    }
}
void khoiTaoMang()
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            array[i][j] = 0;
        }
    }
}
char enterKey()
{
    char key;
    cin >> key;
    return key;
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
void printResult(const char &checkGameOver, const char &checkWin)
{
    if (checkGameOver)
    {
        cout << "You lost!" << endl;
    }
    if (checkWin)
    {
        cout << "Congratulation! You win!" << endl;
    }
}
void printArray()
{
    for (int i = 1; i < 50; i++)
        cout << endl;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            cout << array[i][j] << "  ";
        }
        cout << endl;
    }
}
void updateArray(const char &key)
{
    switch (key)
    {
    case 'w':
        updateArrayUp();
        break;
    case 's':
        updateArrayDown();
        break;
    case 'd':
        updateArrayRight();
        break;
    case 'a':
        updateArrayLeft();
        break;
    }
}
void updateArrayUp()
{
    // cout<<"up"<<endl;
    for (int j = 0; j < gameSize; j++)
    {
        vector<bool> arrayCheck(size_max, true); // xác định xem vị trí đấy có đc cộng k
        bool check = false;                      // check cột hợp lệ chưa
        while (!check)
        {
            for (int i = 0; i <= gameSize - 2; i++)
            {
                if (array[i][j] == 0 && array[i + 1][j] != 0)
                {
                    array[i][j] = array[i + 1][j];
                    array[i + 1][j] = 0;
                }
                if (array[i][j] == array[i + 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i + 1])
                {
                    array[i][j] *= 2;
                    array[i + 1][j] = 0;
                    arrayCheck[i] = false;
                }
            }
            check = true;
            for (int i = 0; i <= gameSize - 2; i++)
            {
                if ((array[i][j] == 0 && array[i + 1][j] != 0) || (array[i][j] == array[i + 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i + 1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
void updateArrayDown()
{
    // cout << "down" << endl;
    for (int j = 0; j < gameSize; j++)
    {
        vector<bool> arrayCheck(size_max, true);
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int i = gameSize - 1; i > 0; i--)
            {
                if (array[i][j] == 0 && array[i - 1][j] != 0)
                {
                    array[i][j] = array[i - 1][j];
                    array[i - 1][j] = 0;
                }
                if (array[i][j] == array[i - 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i - 1])
                {
                    array[i][j] *= 2;
                    array[i - 1][j] = 0;
                    arrayCheck[i] = false;
                }
            }
            check = true;
            for (int i = gameSize - 1; i > 0; i--)
            {
                if ((array[i][j] == 0 && array[i - 1][j] != 0) || (array[i][j] == array[i - 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i - 1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
void updateArrayRight()
{
    // cout << "right" << endl;
    for (int i = 0; i < gameSize; i++)
    {
        vector<bool> arrayCheck(size_max, true);
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int j = gameSize - 1; j > 0; j--)
            {
                if (array[i][j] == 0 && array[i][j - 1] != 0)
                {
                    array[i][j] = array[i][j - 1];
                    array[i][j - 1] = 0;
                }
                if (array[i][j] == array[i][j - 1] && array[i][j] != 0 && arrayCheck[j] && arrayCheck[j - 1])
                {
                    array[i][j] *= 2;
                    array[i][j - 1] = 0;
                    arrayCheck[j] = false;
                }
            }
            check = true;
            for (int j = gameSize - 1; j > 0; j--)
            {
                if ((array[i][j] == 0 && array[i][j - 1] != 0) || (array[i][j] == array[i][j - 1] && array[i][j] != 0 && arrayCheck[j] && arrayCheck[j - 1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
void updateArrayLeft()
{
    // cout << "left" << endl;
    for (int i = 0; i < gameSize; i++)
    {
        vector<bool> arrayCheck(size_max, true);
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int j = 0; j <= gameSize - 2; j++)
            {
                if (array[i][j] == 0 && array[i][j + 1] != 0)
                {
                    array[i][j] = array[i][j + 1];
                    array[i][j + 1] = 0;
                }
                if (array[i][j] == array[i][j + 1] && array[i][j] != 0 && arrayCheck[j] && arrayCheck[j + 1])
                {
                    array[i][j] *= 2;
                    array[i][j + 1] = 0;
                    arrayCheck[j] = false;
                }
            }
            check = true;
            for (int j = 0; j <= gameSize - 2; j++)
            {
                if ((array[i][j] == 0 && array[i][j + 1] != 0) || (array[i][j] == array[i][j + 1] && array[i][j] != 0 && arrayCheck[j] && arrayCheck[j + 1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
bool compareArray(int (*arrayBefore)[size_max])
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            if (arrayBefore[i][j] != array[i][j])
                return false;
        }
    }
    return true;
}
void updateArrayBefore(int (*arrayBerfore)[size_max])
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            arrayBerfore[i][j] = array[i][j];
        }
    }
}

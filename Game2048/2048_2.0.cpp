#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
using namespace std;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 650;
const int FIRST_NUMBER_COORDINATE_X = 25;
const int FIRST_NUMBER_COORDINATE_Y = 150;
const int SIZE_NUMBER = 100;
const int amount_image = 12;
// vị trí xuất hiện của ô đầu tiên y=SCREEN_HEIGHT/3.57 x=SCREEN_WIDTH/16.5
bool init();
bool loadMedia();
void close();
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
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                SDL_Rect stretch[0]; // kéo căng ra
                stretch[0].x = 0;
                stretch[0].y = 0;
                stretch[0].h = SCREEN_HEIGHT;
                stretch[0].w = SCREEN_WIDTH;
                SDL_BlitScaled(gDisplaySurface[0], NULL, gScreenSurface, &stretch[0]);
                for (int i = 1; i < 5; i++)
                {
                    stretch[i].x = FIRST_NUMBER_COORDINATE_X+SIZE_NUMBER*(i-1);
                    stretch[i].y = FIRST_NUMBER_COORDINATE_Y;
                    stretch[i].h = SIZE_NUMBER;
                    stretch[i].w = SIZE_NUMBER;
                    SDL_BlitScaled(gDisplaySurface[i], NULL, gScreenSurface, &stretch[1]);
                }
                SDL_UpdateWindowSurface(gWindow);
            }
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
#include "Handling_Image.h"

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
                if (!imageNumber[i][j].loadImage(path))
                {
                    success = false;
                    cout << "Failed to load image: " << path << endl;
                }
            }
        }
        file >> path;
        if (!win.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!lose.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!domin.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!house.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!huongDan.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!gameDifficulry.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!trong.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!soundOff.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!batdauchoi.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!huongdanx.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!de.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!trungbinh.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!kho.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!ratkho.loadImage(path))
        {
            success = false;
        }
        // if(domin!=NULL) cout<<"huy ";
    }
    return success;
}

void showTotalImage()
{
    domin.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    domin.Show();
    SDLCommonFunction::showText(flagNumber, 685, 55);
    SDLCommonFunction::showText(timeGame, 435, 55);
    showTimeGameMin(difficulry);
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            int x = gameSpecifications.xStart + gameSpecifications.sizeSquare * j;
            int y = gameSpecifications.yStart + gameSpecifications.sizeSquare * i;
            int w = gameSpecifications.sizeSquare;
            int h = gameSpecifications.sizeSquare;
            imageNumber[showMap[i][j] + 1][(i + j) % 2].SetRect(x, y, w, h);
            imageNumber[showMap[i][j] + 1][(i + j) % 2].Show();

            if (tickMap[i][j] == 1 && showMap[i][j] == -1)
            {
                imageNumber[8][(i + j) % 2].SetRect(x, y, w, h);
                imageNumber[8][(i + j) % 2].Show();
            }
            else

                if (tickMap[i][j] == 2 && showMap[i][j] == -1)
            {
                imageNumber[9][(i + j) % 2].SetRect(x, y, w, h);
                imageNumber[9][(i + j) % 2].Show();
            }
        }
    }
}
void showBomb(const int &x, const int &y, const bool &checkSound)
{
    int X = gameSpecifications.xStart + gameSpecifications.sizeSquare * x;
    int Y = gameSpecifications.yStart + gameSpecifications.sizeSquare * y;
    int w = gameSpecifications.sizeSquare;
    int h = gameSpecifications.sizeSquare;
    imageNumber[10][(x + y) % 2].SetRect(X, Y, w, h);
    imageNumber[10][(x + y) % 2].Show();
    if (checkSound)
    {
        Mix_PlayChannel(-1, gSoundBomb, 0);
    }
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(400);
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            if (map[i][j] == -1 && (i != y || j != x))
            {
                X = gameSpecifications.xStart + gameSpecifications.sizeSquare * j;
                Y = gameSpecifications.yStart + gameSpecifications.sizeSquare * i;
                w = gameSpecifications.sizeSquare;
                h = gameSpecifications.sizeSquare;
                imageNumber[10][(i + j) % 2].SetRect(X, Y, w, h);
                imageNumber[10][(i + j) % 2].Show();
                SDL_UpdateWindowSurface(gWindow);
                if (checkSound)
                {
                    Mix_PlayChannel(-1, gSoundBomb, 0);
                }
                SDL_Delay(400);
            }
        }
    }
}
void closeImage()
{
    house.~Image();
    domin.~Image();
    huongDan.~Image();
    gameDifficulry.~Image();
    win.~Image();
    lose.~Image();
    trong.~Image();
    soundOff.~Image();
    batdauchoi.~Image();
    huongdanx.~Image();
    de.~Image();
    trungbinh.~Image();
    kho.~Image();
    ratkho.~Image();
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            imageNumber[i][j].~Image();
        }
    }
}
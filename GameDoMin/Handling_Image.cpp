#include "Handling_Image.h"

Image(imageNumber[11][2]);
Image minesweeper;
Image house;
Image win;
Image lose;
Image tutorialContent; // nội dung hướng dẫn
Image gameDifficulry;
Image blank; // ảnh trống k có gì
Image soundOff;
Image startGame; // bắt đầu chơi
Image tutorial;  // Hướng dẫn
Image easy;
Image medium;
Image hard;
Image veryHard;

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
        if (!minesweeper.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!house.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!tutorialContent.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!gameDifficulry.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!blank.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!soundOff.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!startGame.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!tutorial.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!easy.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!medium.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!hard.loadImage(path))
        {
            success = false;
        }
        file >> path;
        if (!veryHard.loadImage(path))
        {
            success = false;
        }
        // if(domin!=NULL) cout<<"huy ";
    }
    return success;
}

void showTotalImage()
{
    minesweeper.SetRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    minesweeper.Show();
    SDLCommonFunction::showText(flagNumber, 740, 55);
    SDLCommonFunction::showText(timeGame, 470, 55);
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
    minesweeper.~Image();
    tutorialContent.~Image();// nội dung hướng dẫn
    gameDifficulry.~Image();// độ khó
    win.~Image();
    lose.~Image();
    blank.~Image();
    soundOff.~Image();
    startGame.~Image();
    tutorial.~Image();
    easy.~Image();
    medium.~Image();
    hard.~Image();
    veryHard.~Image();
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            imageNumber[i][j].~Image();
        }
    }
}
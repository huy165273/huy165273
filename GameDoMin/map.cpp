#include <cstdlib>
#include <ctime>
#include "map.h"
#include "Common_Function.h"

int **map = new int *[SIZE_HEIGHT_MAX];
int **showMap = new int *[SIZE_HEIGHT_MAX];
int **tickMap = new int *[SIZE_HEIGHT_MAX];

specifications arraySpecifications[4] = {{275, 125, 10, 10, 45, 10},
                                         {100, 150, 10, 20, 40, 30},
                                         {200, 125, 15, 20, 30, 50},
                                         {50, 125, 15, 30, 30, 99}};

void mapInitialization(int **map)
{
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        map[i] = new int[gameSpecifications.mapWidth];
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            map[i][j] = 0;
        }
    }
}
void showMapInitialization()
{
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        showMap[i] = new int[gameSpecifications.mapWidth];
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            showMap[i][j] = -1;
        }
    }
}
void randomBombMap()
{
    int count = 1;
    srand(time(nullptr));
    while (count <= gameSpecifications.numberBomb)
    {
        int x = rand() % gameSpecifications.mapHeight;
        int y = rand() % gameSpecifications.mapWidth;
        if (map[x][y] == 0)
        {
            map[x][y] = -1; // -1 là có bom
            count++;
        }
    }
}
bool checkMap()
{
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
            if (map[i][j] != showMap[i][j])
                return false;
    return true;
}
void numberInMap()
{
    for (int i = 0; i < gameSpecifications.mapHeight; i++)
    {
        for (int j = 0; j < gameSpecifications.mapWidth; j++)
        {
            int count = 0;
            bool check = false;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int t = j - 1; t <= j + 1; t++)
                {
                    if (k == i && t == j)
                    {
                        if (map[k][t] == -1)
                        {
                            count = -1;
                            check = true;
                            break;
                        }
                    }
                    else if (k >= 0 && k < gameSpecifications.mapHeight && t >= 0 && t < gameSpecifications.mapWidth)
                    {
                        if (map[k][t] == -1)
                            count++;
                    }
                }
                if (check)
                    break;
            }
            map[i][j] = count;
        }
    }
}
bool checkBomb(int x, int y)
{
    if (map[y][x] == -1)
        return true;
    return false;
}
void editShowMap(int x, int y)
{
    int X = gameSpecifications.xStart + gameSpecifications.sizeSquare * x;
    int Y = gameSpecifications.yStart + gameSpecifications.sizeSquare * y;
    int w = gameSpecifications.sizeSquare;
    imageNumber[map[y][x] + 1][(x + y) % 2].SetRect(X, Y, w, w);
    imageNumber[map[y][x] + 1][(x + y) % 2].Show();
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(25);
    if (map[y][x] > 0)
        showMap[y][x] = map[y][x];
    else
    {
        showMap[y][x] = 0;
        for (int i = y - 1; i <= y + 1; i++)
            for (int j = x - 1; j <= x + 1; j++)
            {
                if (i >= 0 && i < gameSpecifications.mapHeight && j >= 0 && j < gameSpecifications.mapWidth && (i != y || j != x))
                    if (showMap[i][j] == -1)
                        editShowMap(j, i);
            }
    }
}
void DeleteMap()
{
    for (int i = 0; i < SIZE_HEIGHT_MAX; i++)
    {
        delete[] map[i];
        delete[] showMap[i];
        delete[] tickMap[i];
    }
    delete[] * map;
    delete[] * showMap;
    delete[] * tickMap;
}

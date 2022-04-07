#include <cstdlib>
#include <ctime>
#include "map.h"
void mapInitialization(int **map, const int mapWidth, const int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
    {
        map[i] = new int[mapWidth];
        for (int j = 0; j < mapWidth; j++)
        {
            map[i][j] = 0;
        }
    }
}
void showMapInitialization(int **showMap, const int mapWidth, const int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
    {
        showMap[i] = new int[mapWidth];
        for (int j = 0; j < mapWidth; j++)
        {
            showMap[i][j] = -1;
        }
    }
}
void randomBombMap(int **map, const int mapWidth, const int mapHeight, const int amountBomb)
{
    int count = 1;
    while (count <= amountBomb)
    {
        srand(time(nullptr));
        int x = rand() % mapHeight;
        int y = rand() % mapWidth;
        if (map[x][y] == 0)
        {
            map[x][y] = -1;// -1 là có bom 
            count++;
        }
    }
}
bool checkMap(int **map, int **showMap, const int mapWidth, const int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
        for (int j = 0; j < mapWidth; j++)
            if (map[i][j] != showMap[i][j])
                return false;
    return true;
}
void numberInMap(int **map, int mapWidth, int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
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
                    else if (k >= 0 && k < mapHeight && t >= 0 && t < mapWidth)
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
bool checkBomb(int x, int y, int **map){
    if(map[x][y]==-1) return true;
    return false;
}
void editShowMap(int x, int y, int **map, int **showMap, int mapWidth, int mapHeight)
{
    if(map[x][y]>0) showMap[x][y]=map[x][y];
    else{
        showMap[x][y]=0;
        for(int i=x-1;i<=x+1;i++)
            for(int j=y-1;j<=y+1;j++){
                if(i>=0 && i<mapHeight && j>=0 && j<mapWidth && (i!=x || j!=y)) 
                    if(showMap[i][j]==-1) editShowMap(i, j, map, showMap, mapWidth, mapHeight);
            }
    }
}
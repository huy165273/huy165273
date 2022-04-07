#include <iostream>
#include <cstdlib>
#include <ctime>
#include "map.h"
using namespace std;

const int SIZE_WIDTH_MAX = 30;
const int SIZE_HEIGHT_MAX = 15;

void printMap(int **map, int mapWidth, int mapHeight);

int main()
{
    int x, y;
    int mapWidth = 9;
    int mapHeight = 9;
    int **map = new int *[SIZE_HEIGHT_MAX];
    int **showMap = new int *[SIZE_HEIGHT_MAX];
    mapInitialization(map, mapWidth, mapHeight);
    showMapInitialization(showMap, mapWidth, mapHeight);
    randomBombMap(map, mapWidth, mapHeight, 5);
    numberInMap(map, mapWidth, mapHeight);
    bool check = true;
    printMap(showMap, mapWidth, mapHeight);
    while (check)
    {
        cout << "Enter the coordinates of your choice: ";
        cin >> x >> y;
        if (checkBomb(x, y, map) )
        {
            check = false;
            cout << "You are dead! You lose!" << endl;
            cout << "Bomb map: " << endl;
            printMap(map, mapWidth, mapHeight);
        }
        else
        {
           editShowMap(x, y, map, showMap, mapWidth, mapHeight);
            printMap(showMap, mapWidth, mapHeight);
        }
        if (checkMap(map, showMap, mapWidth, mapHeight))
        {
            check = false;
            cout << "Congratulate! You win!" << endl;
            cout << "Bomb map: " << endl;
            printMap(map, mapWidth, mapHeight);
        }
    }
    return 0;
}
void printMap(int **map, int mapWidth, int mapHeight)
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

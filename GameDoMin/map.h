#ifndef MAP_H_INCLUDE
#define MAP_H_INCLUDE

void mapInitialization(int **map, const int mapWidth, const int mapHeight);
void showMapInitialization(int **showMap, const int mapWidth, const int mapHeight);
void randomBombMap(int **map, const int mapWidth, const int mapHeight, const int amountBomb);
bool checkMap(int **map, int **showMap, const int mapWidth, const int mapHeight);
void numberInMap(int **map, int mapWidth, int mapHeight);
bool checkBomb(int x, int y, int **map);
void editShowMap(int x, int y, int **map, int **showMap, int mapWidth, int mapHeight);

#endif
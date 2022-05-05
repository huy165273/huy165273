#ifndef MAP_H_INCLUDE
#define MAP_H_INCLUDE

extern int **map ;
extern int **showMap ;
extern int **tickMap ;
struct specifications
{
    int xStart;
    int yStart;
    int mapHeight;
    int mapWidth;
    int sizeSquare;
    int numberBomb;
    specifications(int xStart_, int yStart_, int mapHeight_, int mapWidth_, int sizeSquare_, int numberBomb_)
        : xStart(xStart_), yStart(yStart_), mapHeight(mapHeight_), mapWidth(mapWidth_), sizeSquare(sizeSquare_), numberBomb(numberBomb_) {}
    specifications(){};
};

extern specifications arraySpecifications[4];
extern specifications gameSpecifications;
extern int mapWidth;
extern int mapHeight;

void mapInitialization(int **map);
void showMapInitialization( );
void randomBombMap();
bool checkMap();
void numberInMap();
bool checkBomb(int x, int y);
void editShowMap(int x, int y);
void DeleteMap(int **map, int SIZE_HEIGHT_MAX);

#endif
#ifndef ARRAY_MANIPULATION_H_INCLUDE
#define ARRAY_MANIPULATION_H_INCLUDE


void updateArrayUp(int **array, const int gameSize, int &score);
void updateArrayDown(int **array, const int gameSize, int &score);
void updateArrayRight(int **array, const int gameSize, int &score);
void updateArrayLeft(int **array, const int gameSize, int &score); 
void updateArrayBefore(int *(*arrayBefore), int *(*array), const int gameSize);
bool compareArray(int **arrayBefore, int **array, const int gameSize);
void khoiTaoMang(int **array, int **arrayBefore, const int& gameSize);

#endif

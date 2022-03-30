#ifndef ARRAY_MANIPULATION_H_INCLUDE
#define ARRAY_MANIPULATION_H_INCLUDE


void updateArrayUp(int **array, const int gameSize);
void updateArrayDown(int **array, const int gameSize);
void updateArrayRight(int **array, const int gameSize);
void updateArrayLeft(int **array, const int gameSize); 
void updateArrayBefore(int *(*arrayBerfore), int *(*array), const int gameSize);
bool compareArray(int **arrayBefore, int **array, const int gameSize);
#endif

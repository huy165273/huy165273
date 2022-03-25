#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int size_max = 10;
int gameSize;
int array[size_max][size_max];
void khoiTaoMang();
void randomNumber();
char enterKey();
bool gameOver();
bool Win();
void updateArray(const char &key);
void printResult(const char& checkGameOver, const char &checkWin);
int main()
{   char key;
    bool checkGameOver;
    bool checkWin;
    cin >> gameSize;
    khoiTaoMang();
    randomNumber();
    randomNumber();
    do{
        key=enterKey();
        updateArray(key);
    }while(!gameOver() || Win());
    printResult(checkGameOver, checkWin);
}
void randomNumber()
{
    bool check = true;
    int x, y;
    while (check)
    {
        srand(time(nullptr));
        x = rand() % gameSize;
        y = rand() % gameSize;
        if (array[x][y] == 0)
        {
            // chọn số cho ô 2 hoặc 4
            int randomNumber;
            randomNumber = (rand() % 2 + 1) * 2;
            check = false;
        }
    }
    
}
void khoiTaoMang()
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            array[i][j] = 0;
        }
    }
}
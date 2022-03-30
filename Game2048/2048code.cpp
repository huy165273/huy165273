#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "array_manipulation.h"
using namespace std;
const int size_max = 10;
int **array= new int *[size_max];
int gameSize;
void khoiTaoMang( int **beforeArray);
int enterGameSize()
{
    return 4;
}
void randomNumber();
char enterKey();
bool gameOver();
bool win();
void updateArray(const char &key);
void printArray();
void printResult(const char &checkGameOver, const char &checkWin);
int main()
{   
    int **arrayBefore= new int*[size_max];
    char key;
    bool checkGameOver;
    bool checkWin;
    gameSize = enterGameSize();
    khoiTaoMang( arrayBefore);
    cout<<array[0][0];
    printArray();
    randomNumber();
    randomNumber();
    printArray();
    do
    {
        key = enterKey();
        updateArrayBefore(arrayBefore, array, gameSize);
        updateArray(key);
        if (!compareArray(arrayBefore, array, gameSize))
            randomNumber();
        printArray();
    } while (!gameOver() || win());
    printResult(gameOver(), win());
    return 0;
}
void randomNumber()
{
    int count1 = 0, count2 = 0;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
            if (array[i][j] == 0)
                count1++;
    }
    srand(time(nullptr));
    int random = rand() % count1 + 1;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
            if (array[i][j] == 0)
            {
                count2++;
                if (count2 == random)
                {
                    // chọn số cho ô 2 hoặc 4
                    // tạm thời chọn tỉ lệ ra số 4 là 10%
                    int randomNumber = (rand() % 10);
                    if (randomNumber == 0)
                        array[i][j] = 4;
                    else
                        array[i][j] = 2;
                }
            }
    }
}
void khoiTaoMang(int **beforeArray)
{
    for (int i = 0; i < gameSize; i++)
    {
        array[i]= new int [gameSize]();
        beforeArray[i]= new int [gameSize]();
    }
}
char enterKey()
{
    char key;
    cin >> key;
    return key;
}
bool gameOver()
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            if (array[i][j] == 0)
                return false;
        }
    }
    return true;
}
bool win()
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            if (array[i][j] == 2048)
                return true;
        }
    }
    return false;
}
void printResult(const char &checkGameOver, const char &checkWin)
{
    if (checkGameOver)
    {
        cout << "You lost!" << endl;
    }
    if (checkWin)
    {
        cout << "Congratulation! You win!" << endl;
    }
}
void printArray()
{
    for (int i = 1; i < 50; i++)
        cout << endl;
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            cout << array[i][j] << "  ";
        }
        cout << endl;
    }
}
void updateArray(const char &key)
{
    switch (key)
    {
    case 'w':
        updateArrayUp(array, gameSize);
        break;
    case 's':
        updateArrayDown(array, gameSize);
        break;
    case 'd':
        updateArrayRight(array, gameSize);
        break;
    case 'a':
        updateArrayLeft(array, gameSize);
        break;
    }
}

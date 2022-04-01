#include<vector>
#include "array_manipulation.h"
using namespace std;
void updateArrayUp(int **array, const int gameSize, int &score)
{
    for (int j = 0; j < gameSize; j++)
    {   
         vector <bool> arrayCheck (gameSize,true);// xác định xem vị trí đấy có đc cộng k
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int i = 0; i <= gameSize - 2; i++)
            {
                if (array[i][j] == 0 && array[i + 1][j] != 0)
                {
                    array[i][j] = array[i + 1][j];
                    array[i + 1][j] = 0;
                }
                if (array[i][j] == array[i + 1][j] && array[i][j] != 0&& arrayCheck[i] && arrayCheck[i + 1])
                {
                    array[i][j] *= 2;
                    score+=array[i][j];
                    array[i + 1][j] = 0;
                    arrayCheck[i]=false;
                }
            }
            check = true;
            for (int i = 0; i <= gameSize - 2; i++)
            {
                if ((array[i][j] == 0 && array[i + 1][j] != 0) || (array[i][j] == array[i + 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i + 1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}

void updateArrayDown(int **array, const int gameSize, int &score)
{
    // cout << "down" << endl;
    for (int j = 0; j < gameSize; j++)
    {   
        vector <bool> arrayCheck(gameSize,true);
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int i = gameSize - 1; i > 0; i--)
            {
                if (array[i][j] == 0 && array[i - 1][j] != 0)
                {
                    array[i][j] = array[i - 1][j];
                    array[i - 1][j] = 0;
                }
                if (array[i][j] == array[i - 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i-1] )
                {
                    array[i][j] *= 2;
                    score+=array[i][j];
                    array[i - 1][j] = 0;
                    arrayCheck[i]=false;
                }
            }
            check = true;
            for (int i = gameSize - 1; i > 0; i--)
            {
                if ((array[i][j] == 0 && array[i - 1][j] != 0) || (array[i][j] == array[i - 1][j] && array[i][j] != 0 && arrayCheck[i] && arrayCheck[i-1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
void updateArrayRight(int **array, const int gameSize, int &score)
{
    //cout << "right" << endl;
    for (int i = 0; i < gameSize; i++)
    { 
        vector <bool> arrayCheck(gameSize,true);
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int j = gameSize - 1; j > 0; j--)
            {
                if (array[i][j] == 0 && array[i][j-1] != 0)
                {
                    array[i][j] = array[i][j-1];
                    array[i][j - 1] = 0;
                }
                if (array[i][j] == array[i][j - 1] && array[i][j] != 0 &&arrayCheck[j] && arrayCheck[j-1])
                {
                    array[i][j] *= 2;
                    score+=array[i][j];
                    array[i][j - 1] = 0;
                    arrayCheck[j]=false;
                }
            }
            check = true;
            for (int j = gameSize - 1; j > 0; j--)
            {
                if ((array[i][j] == 0 && array[i][j - 1] != 0) || (array[i][j] == array[i][j - 1] && array[i][j] != 0 &&arrayCheck[j] && arrayCheck[j-1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }

}
void updateArrayLeft(int **array, const int gameSize, int &score)
{
    //cout << "left" << endl;
    for (int i = 0; i < gameSize; i++)
    {
        vector <bool> arrayCheck(gameSize,true);
        bool check = false; // check cột hợp lệ chưa
        while (!check)
        {
            for (int j = 0; j <= gameSize - 2; j++)
            {
                if (array[i][j] == 0 && array[i][j+1] != 0)
                {
                    array[i][j] = array[i][j+1];
                    array[i][j+1] = 0;
                }
                if (array[i][j] == array[i][j+1] && array[i][j] != 0 && arrayCheck[j] &&arrayCheck[j+1])
                {
                    array[i][j] *= 2;
                    score+=array[i][j];
                    array[i][j+1] = 0;
                    arrayCheck[j]=false;
                }
            }
            check = true;
            for (int j = 0; j <= gameSize - 2; j++)
            {
                if ((array[i][j] == 0 && array[i][j+1] != 0) || (array[i][j] == array[i][j+1] && array[i][j] != 0 && arrayCheck[j] &&arrayCheck[j+1]))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
bool compareArray(int **arrayBefore, int ** array, int gameSize)
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            if (arrayBefore[i][j] != array[i][j])
                return false;
        }
    }
    return true;
}
void updateArrayBefore(int **arrayBefore, int ** array, const int gameSize)
{
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            arrayBefore[i][j] = array[i][j];
        }
    }
}
void khoiTaoMang(int **array, int **arrayBefore, const int& gameSize)
{
    for (int i = 0; i < gameSize; i++)
    {
        array[i] = new int[gameSize]();
        arrayBefore[i] = new int[gameSize]();
    }
}
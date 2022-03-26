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
bool win();
void updateArray(const char &key);
bool compareArray(int (* arrayBefore)[size_max]);// so sánh 2 mảng có giống nhau k
void updateArrayUp();
void updateArrayDown();
void updateArrayRight();
void updateArrayLeft();
void printArray();
void printResult(const char &checkGameOver, const char &checkWin);
void updateArrayBefore(int (*arrayBerfore)[size_max]);
int main()
{   
    char key;
    bool checkGameOver;
    bool checkWin;
    int arrayBefore[size_max][size_max];
    cin >> gameSize;
    khoiTaoMang();
    randomNumber();
    randomNumber();
    printArray();
    do
    {
        key = enterKey();
        updateArrayBefore(arrayBefore);
        updateArray(key);
        if (!compareArray(arrayBefore))
            randomNumber();
        printArray();
    } while (!gameOver() || win());
    printResult(checkGameOver, checkWin);
    return 0;
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
            // tạm thời chọn tỉ lệ ra số 4 là 10%
            int randomNumber;
            randomNumber = (rand() % 10);
            if(randomNumber==0) array[x][y]=4;
            else array[x][y]=2;
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
        updateArrayUp();
        break;
    case 's':
        updateArrayDown();
        break;
    case 'd':
        updateArrayRight();
        break;
    case 'a':
        updateArrayLeft();
        break;
    }
}
void updateArrayUp()
{
    // cout<<"up"<<endl;
    for (int j = 0; j < gameSize; j++)
    {
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
                if (array[i][j] == array[i + 1][j] && array[i][j] != 0)
                {
                    array[i][j] *= 2;
                    array[i + 1][j] = 0;
                }
            }
            check = true;
            for (int i = 0; i <= gameSize - 2; i++)
            {
                if ((array[i][j] == 0 && array[i + 1][j] != 0) || (array[i][j] == array[i + 1][j] && array[i][j] != 0))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
void updateArrayDown()
{
    // cout << "down" << endl;
    for (int j = 0; j < gameSize; j++)
    {
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
                if (array[i][j] == array[i - 1][j] && array[i][j] != 0)
                {
                    array[i][j] *= 2;
                    array[i - 1][j] = 0;
                }
            }
            check = true;
            for (int i = gameSize - 1; i > 0; i--)
            {
                if ((array[i][j] == 0 && array[i - 1][j] != 0) || (array[i][j] == array[i - 1][j] && array[i][j] != 0))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
void updateArrayRight()
{
    //cout << "right" << endl;
    for (int i = 0; i < gameSize; i++)
    {
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
                if (array[i][j] == array[i][j - 1] && array[i][j] != 0)
                {
                    array[i][j] *= 2;
                    array[i][j - 1] = 0;
                }
            }
            check = true;
            for (int j = gameSize - 1; j > 0; j--)
            {
                if ((array[i][j] == 0 && array[i][j - 1] != 0) || (array[i][j] == array[i][j - 1] && array[i][j] != 0))
                {
                    check = false;
                    break;
                }
            }
        }
    }

}
void updateArrayLeft()
{
    //cout << "left" << endl;
    for (int i = 0; i < gameSize; i++)
    {
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
                if (array[i][j] == array[i][j+1] && array[i][j] != 0)
                {
                    array[i][j] *= 2;
                    array[i][j+1] = 0;
                }
            }
            check = true;
            for (int j = 0; j <= gameSize - 2; j++)
            {
                if ((array[i][j] == 0 && array[i][j+1] != 0) || (array[i][j] == array[i][j+1] && array[i][j] != 0))
                {
                    check = false;
                    break;
                }
            }
        }
    }
}
bool compareArray(int (* arrayBefore)[size_max]){
    for(int i=0;i<gameSize;i++){
        for(int j=0;j<gameSize;j++){
            if(arrayBefore[i][j]!=array[i][j])
            return false;
        }
    }
    return true;
}
void updateArrayBefore(int (*arrayBerfore)[size_max]){
    for(int i=0;i<gameSize;i++){
        for(int j=0;j<gameSize;j++){
            arrayBerfore[i][j]=array[i][j];
        }
    }
}


// 
// cộng nhiều lần (sửa thành cộng 1 lần)-- Chưa giải quyết được
// khi mảng không di chuyển vẫn tạo số ms(sửa thành không tạo số ms) -- Đã giải quyết
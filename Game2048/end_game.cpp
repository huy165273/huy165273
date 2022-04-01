#include <fstream>
using namespace std;
bool gameOver(int **array, const int &gameSize)
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
bool win(int **array, const int &gameSize)
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
int hightScore(const int &score, int const& gameSize)
{
    fstream file;
    file.open("diem_cao.txt");
    int higth_score[6];
    for (int i = 0; i < 6; i++)
        file >> higth_score[i];
    file.close();
    file.open("diem_cao.txt", ios::out | ios::trunc);
    if (score > higth_score[gameSize - 3])
        higth_score[gameSize - 3] = score;
    for (int i = 0; i < 6; i++)
        file << higth_score[i] << endl;
    file.close();
    return higth_score[gameSize - 3];
}
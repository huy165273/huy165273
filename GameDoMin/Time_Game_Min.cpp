#include "Time_Game_Min.h"

int timeMin[4];

void readTimeGameMin()
{
    string path;
    ifstream file;
    file.open("time_game_min.txt");
    if (!file)
    {
        cout << "Failed to open file." << endl;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            file >> timeMin[i];
        }
    }
    file.close();
}
void writeTimeGameMin()
{
    string path;
    ofstream file;
    file.open("time_game_min.txt", ios::out | ios::trunc);
    if (!file)
    {
        cout << "Failed to open file." << endl;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            file << timeMin[i] << endl;
        }
    }
    file.close();
}
void showTimeGameMin(const int &difficulry){
    if (timeMin[difficulry] != 9999)
    {
        SDLCommonFunction::showText(timeMin[difficulry], 565, 55);
    }
}

#include <iostream>
#include <fstream>
using namespace std;
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
            file << timeMin[i]<<endl;
        }
    }
    file.close();
}
int main()
{
    readTimeGameMin();
    timeMin[0]=10;
    timeMin[1]=88;
    timeMin[2]=8;
    timeMin[3]=8888;
    writeTimeGameMin();
    return 0;
}
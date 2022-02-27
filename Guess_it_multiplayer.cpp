#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void playGuess();
int generateRandomNumber(int min = 1, int max = 200);
int getPlayerGuess(int player);
void printAnswer(int player,int guess, int secretNumber);

int main() {
	string again;
	do {
		playGuess();
		cout << "Play again (Yes/No): ";
		cin >> again;
	} while (again == "Yes");
	return 0;
}
void playGuess() {
	int nPlayer = 2;
	srand(time(nullptr));
	int secretNumber = generateRandomNumber();
	int guess[10];
	guess[0] = 0;
	bool isgameover = true;
	do {
		for (int player = 1; player <= nPlayer; player++) {
			guess[player] = getPlayerGuess(player);
		}
		for (int player = 1; player <= nPlayer; player++)
		printAnswer(player,guess[player], secretNumber);
		for (int player = 1; player <= nPlayer; player++)
			if (guess[player] == secretNumber) {
				cout << "Congratulation! Player " << player << " win."<<endl;
				isgameover = false;
			}	
	} while (isgameover);
}
int generateRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}
int getPlayerGuess(int player) {
	int guess;
	cout << "Player "<<player<<", please enter your guess : ";
	cin >> guess;
	return guess;
}
void printAnswer(int player, int guess, int secretNumber) {
	 
	if (guess > secretNumber) {
		cout << "Player " << player << ": Your number is too big." << endl;
	}
	else
		if (guess < secretNumber)
			cout << "Player " << player << ": Your number is too small." << endl;
		else cout << "Player " << player << ": Congratulation! You win."<<endl;
}


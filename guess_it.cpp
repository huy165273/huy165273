#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void playGuess();
int generateRandomNumber(int min=1, int max=100);
int getPlayerGuess();
void printAnswer(int guess, int secretNumber);
void gameResult(int count);
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
	srand(time(nullptr));
	int secretNumber = generateRandomNumber();
	int guess;
	int count = 0;
	do {
		guess = getPlayerGuess();
		printAnswer(guess, secretNumber);
		count++;
	} while (guess != secretNumber);
	gameResult(count);
}
int generateRandomNumber(int min,int max) {
	return min + rand() % (max - min + 1);
}
int getPlayerGuess() {
	int guess;
	cout << "Enter your guess: ";
	cin >> guess;
	return guess;
}
void printAnswer(int guess, int secretNumber) {
	if (guess == secretNumber) {
		cout << "Congratulation! You win." << endl;
	}
	else if (guess > secretNumber) {
		cout << "Your number is too big." << endl;
	}
	else {
		cout << "Your number is too small." << endl;
	}
}
void gameResult(int count) {
	cout << "Number of guesses: " << count << endl;
	cout << "Player score: ";
	if (count < 10) cout << 100 - 10 * count<<endl;
	else cout << "0"<<endl;
}
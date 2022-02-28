#include<iostream>
#include<string>
using namespace std;
void writeNumbers(int n) {
	switch (n) {
	case 1: cout << "one"; break;
	case 2: cout << "two"; break;
	case 3: cout << "three"; break;
	case 4: cout << "four"; break;
	case 5: cout << "five"; break;
	case 6: cout << "six"; break;
	case 7: cout << "seven"; break;
	case 8: cout << "eight"; break;
	case 9: cout << "nine"; break;
	case 10: cout << "ten"; break;
	case 11: cout << "eleven"; break;
	case 12: cout << "twelve"; break;
	case 13: cout << "thirteen"; break;
	case 14: cout << "fourteen"; break;
	case 15: cout << "fifteen"; break;
	case 16: cout << "sixteen"; break;
	case 17: cout << "seventeen"; break;
	case 18: cout << "eighteen"; break;
	case 19: cout << "nineteen"; break;
	case 20: cout << "twenty"; break;
	case 30: cout << "thirty"; break;
	case 40: cout << "forty"; break;
	case 50: cout << "fifty"; break;
	case 60: cout << "sixty"; break;
	case 70: cout << "seventy"; break;
	case 80: cout << "eighty"; break;
	case 90: cout << "ninety"; break;
	}
}
void writeNumbersHundred(int n) {
	int tram = n / 100;
	if (tram > 0) {
		writeNumbers(tram);
		cout<< " hundred ";
	}
	n = n % 100;
	int chuc = n / 10;
	if (chuc > 0) {
		if (chuc == 1)  writeNumbers(n);
		else {
			writeNumbers(chuc * 10);
			cout << "-";
			writeNumbers(n % 10);
		}
	}
	else writeNumbers(n);

}
int main() {
	int n;
	cin >> n;
	if (n == 0) cout << "zero";
	else {
		if (n < 0) {
			cout << "negative ";
			n = -n;
		}
		int trieu = n / 1000000;
		if (trieu > 0) {
			writeNumbersHundred(trieu);
			cout<< " million ";
		}
		n = n % 1000000;
		int nghin = n / 1000;
		if (nghin > 0) {
			writeNumbersHundred(nghin); 
			cout << " thousand ";
		}
		 n = n % 1000;
		if (n > 0)  writeNumbersHundred(n);
	}
	return  0;
}

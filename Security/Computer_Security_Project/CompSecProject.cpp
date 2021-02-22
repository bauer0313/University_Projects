//************************************************************** 
// Computer Security Project Assignment 
// Name:	 Thomas Bauer 
// Class:	 CMPS 4663 - Computer Security
// Date:	 06/28/2019 
// Filename: CompSecProject.cpp
//*************************************************************** 

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

// chooses a new PIN after max attempts have been reached
string choosePin(string &);
// acts as attacker trying exhaustive search of PIN
string bruteForce(int&, bool);

int main() {
	int iterations = 0;
	int round = 1;
	srand(time(NULL));

	ofstream outEx("compsec_data.csv");
	// handles if file doesn't open
	if (outEx.fail()) {
		cerr << "Error Opening File" << endl;
		exit(1);
	}	
	
	outEx << "Computer Security Project Output" << endl;
	while (iterations < 40) {
		int changes = 0;								// number of times the ATM changes the PIN
		int attempt = 0;								// number of attempts by attacker
		float percentage = 0.0;							// percentage to 10000 attempts
		int attemptNumber = 0;							// keeps track of attempts for ATM to change PIN
		string StrPin = "";								// 4-digit PIN
		string input;									// PIN input attempt
		bool correct = false;							// Is inputted PIN correct


		// run while the PIN entered is not correct
		while (!correct) {
			attemptNumber++;							// increment number of attempts for ATM
			input = bruteForce(attempt, correct);		// bruteForce function acts as input
			if (input == StrPin) {
				correct = true;
				break;
			}

			// if statement to track change at 50 attempts
			if (iterations < 20) {
				if (attemptNumber == 50) {
					choosePin(StrPin);					// if max number of attempts has been made,
					attemptNumber = 0;					//    change the PIN;  also reset attemptNumber
					changes++;							// increment number of changes
					if (changes == 200)
						break;
				}
			}

			// if statement to track change at 25 attempts
			if (iterations > 19) {
				if (attemptNumber == 25) {
					choosePin(StrPin);					// if max number of attempts has been made,
					attemptNumber = 0;					//    change the PIN;  also reset attemptNumber
					changes++;							// increment number of changes
					if (changes == 400)
						break;
				}
			}
		}


		// formatting for Windows Excel Spreadsheet to analyze the data
		if (iterations == 0) {
			outEx << "Changes = Attempts / 50" << endl;
			outEx << "Round, Changes, Attempts, Pin, Pass/Fail, Percentage" << endl;
		}
		if (iterations == 20) {
			round = 1;
			outEx << ",,,,Pass,Fail" << endl;
			outEx << ",,,,=(SUM((E4:E23))/20),=(100 - (E25*100))/100" << endl;
			// for loop adds empty lines for formatting to put one set on each page
			for (int i = 0; i < 22; i++) {
				outEx << "\n";
			}
			outEx << "Changes = Attempts / 25" << endl;
			outEx << "Round, Changes, Attempts, Pin, Pass/Fail, Percentage" << endl;
		}
		percentage = ((float)attempt / 10000) * 100;
		if (correct == 1)
			outEx << round << "," << changes << "," << attempt << "," << StrPin << "," << correct << "," << percentage << "%" << endl;
		else
			outEx << round << "," << changes << "," << attempt << ",          - ," << correct << "," << percentage << "%" << endl;
		round++;
		iterations++;
	}
	outEx << ",,,,Pass,Fail" << endl;
	outEx << ",,,,=(SUM((E50:E69))/20),=(100 - (E71*100))/100";
	outEx.close();
    return 0;
}

// use rand() function to find a random number between 0 and
// 9999 inclusive and if else statements concatenate zeros in order
// to make the PIN a full 4 digits and it returns the 4-digit string
// to the main program to be used
string choosePin(string &StrPin) {
	int pin = 0;
	StrPin = "";
	pin = rand() % 10000;
	if (pin < 10) StrPin = "000" + to_string(pin);
	else if 
		(pin < 100 && pin > 9) StrPin = "00" + to_string(pin);
	else if 
		(pin < 1000 && pin > 99) StrPin = "0" + to_string(pin);
	else 
		StrPin += to_string(pin);	
	return StrPin;
}

// bruteForce() function inputs attempt via reference in order to keep 
// track of the number of attempts it has made without having to be inside
// the main program itself. The function runs from 0 to 9999 to attempt PIN
// numbers and concatenates zeros much like the choosePin function, and it 
// returns a string to be attempted as input for the program
string bruteForce(int &attempt, bool success) {	
	string tryPin = "";
	if (attempt == 10000) exit;
	if (attempt < 10) tryPin = "000" + to_string(attempt);
	else if
		(attempt < 100 && attempt > 9) tryPin = "00" + to_string(attempt);
	else if
		(attempt < 1000 && attempt > 99) tryPin = "0" + to_string(attempt);
	else
		tryPin += to_string(attempt);
	attempt++;
	return tryPin;
}
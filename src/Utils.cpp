/*
 * Utils.cpp
 *
 *  Created on: Mar 27, 2021
 *      Author: Colin
 */
#include <iostream>
#include <cctype>
#include "Utils.h"

using namespace std;



char GetCharacter(const char* prompt, const char* error) {
	const int IGNORE_CHARS = 256;
	char input;
	bool failure;

	do {
		failure = false;

		cout << prompt;
		cin >> input;

		if(cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		} else {
			cin.ignore(IGNORE_CHARS, '\n');

			if(isalpha(input)) {
				input = tolower(input);
			} else {
				cout << error << endl;
				failure = true;
			}
		}


	}while(failure);

	return input;
}


char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase) {
	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do {
		failure = false;

		cout << prompt;
		cin >> input;

		if(cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		} else {
			cin.ignore(IGNORE_CHARS, '\n');
			if(isalpha(input)) {
				if(charCase == CC_UPPER_CASE) {
					input = toupper(input);
				} else if(charCase == CC_LOWER_CASE) {
					input = tolower(input);
				}
				for(int i = 0; i < validInputLength; i++) {
					if(input == validInput[i]) {
						return input;
					}
				}
			}
			cout << error << endl;
			failure = true;
		}
	}while(failure);

	return input;
}



void ClearScreen() {

	system("cls");

}

void WaitForKeyPress() {
	system("pause");
}


int GetInteger(const char* prompt, const char* error, const int validInput[], int validInputLength) {
	const int IGNORE_CHARS = 256;
	int input;
	bool failure;

	do{

		failure = false;
		cout << prompt;
		cin >> input;

		if(cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		} else {
			for(int i = 0; i < validInputLength; i++) {
				if(input == validInput[i]) {
					return input;
				}
			}
			cout << error << endl;
			failure = true;
		}

	}while(failure);
	return -1;
}

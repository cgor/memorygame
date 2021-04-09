/*
 * Utils.h
 *
 *  Created on: Mar 27, 2021
 *      Author: Colin
 */

#ifndef UTILS_H_
#define UTILS_H_





#endif /* UTILS_H_ */

enum CharacterCaseType {
	CC_UPPER_CASE = 0,
	CC_LOWER_CASE,
	CC_EITHER
};

char GetCharacter(const char* prompt, const char* error);
char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase);
void ClearScreen();
void WaitForKeyPress();
int GetInteger(const char* prompt, const char* error, const int validInput[], int validInputLength);

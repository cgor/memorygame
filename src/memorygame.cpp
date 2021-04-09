//============================================================================
// Name        : memorygame.cpp
// Author      : Colin Gordon
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================


/***************************************************************************
 *
 * ART CREDITS:
 *
 * -Shanaka Dias
 * -Razza
 * -Joan Stark
 * -Linda Ball
 * -Veronica Karlsson
 * -Stef00
 *
 * and other anonymous submissions to the ASCII Art Archive (www.asciiart.eu)
 *
 ***************************************************************************/

#include <iostream>

#include "Utils.h"
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;





enum {
	NUM_ROWS = 4,
	NUM_COLS = 5,
	NUM_CARDS = NUM_ROWS * NUM_COLS,
	CARD_HEIGHT = 10,
	CARD_WIDTH = 16
};

enum CardType {
	CT_NONE = 0,
	CT_A,
	CT_B,
	CT_C,
	CT_D,
	CT_E,
	CT_F,
	CT_G,
	CT_H,
	CT_I,
	CT_J
};

struct CardSpace {
	CardType cardType;
	bool isRevealed;
	bool isMatched;
};

struct PlayerPosition {
	int row;
	int col;
};

struct Player {
	PlayerPosition position;
	int turns;
	CardSpace cardBoard[NUM_ROWS][NUM_COLS];
};

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_W = 119;
const int KEY_A = 97;
const int KEY_S = 115;
const int KEY_D = 100;
const int KEY_Q = 113;
const int KEY_ESC = 27;
const int KEY_ENTER = 13;
//const int MOVE_KEYS[8] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_A, KEY_S, KEY_D};

const char* INPUT_ERROR_STRING = "Input Error! Please try again.";
const char* DEFAULT_ROW_SEPARATOR = "                  ";
const char* PLAYER_ROW_SEPARATOR = " ----        ---- ";
const char* CARD_BLANK = "                ";
const char* CARD_BACK[CARD_HEIGHT] = {"****************",
									  "****************",
									  "****************",
									  "****************",
									  "****************",
									  "****************",
									  "****************",
									  "****************",
									  "****************",
									  "****************"};
const char* CARD_X[CARD_HEIGHT] =  {"                ",
									"                ",
									"     ,          ",
									"    / \\__       ",
									"   (    @\\___   ",
									"   /         O  ",
									"  /   (_____/   ",
									" /_____/   U    ",
									"                ",
									"                ",};
const char* CARD_Y[CARD_HEIGHT] =  {"                ",
									"                ",
									"            .'' ",
									"  ._.-.___.' (`\\",
									" //(        ( `'",
									"'/ )\\ ).__. )   ",
									"' <' `\\ ._/'\\   ",
									"   `   \\     \\  ",
									"                ",
									"                ",};
const char* CARD_A[CARD_HEIGHT] =  {"                ",
									"                ",
									"                ",
									"         ,      ",
									"       __)\\_    ",
									" (\\_.-'    a`-. ",
									" (/~~````(/~^^` ",
									"                ",
									"                ",
									"                ",};
const char* CARD_B[CARD_HEIGHT] =  {"                ",
									"                ",
									"                ",
									"          O  o  ",
									"     _\\_   o    ",
									"  \\\\/  o\\ .     ",
									"  //\\___=       ",
									"     ''         ",
									"                ",
									"                ",};
const char* CARD_C[CARD_HEIGHT] =  {"                ",
									"    _    _      ",
									"   /=\\\"\"/=\\     ",
									"  (=(0_0 |=)__  ",
									"   \\_\\ _/_/   ) ",
									"    /_/   _  /\\ ",
									"    |/ |\\ || |  ",
									"       ~ ~  ~   ",
									"                ",
									"                ",};
const char* CARD_D[CARD_HEIGHT] =  {"                ",
									"                ",
									"     , _ ,      ",
									"    ( o o )     ",
									"   /'` ' `'\\    ",
									"   |'''''''|    ",
									"   |\\\\'''//|    ",
									"      \"\"\"       ",
									"                ",
									"                ",};
const char* CARD_E[CARD_HEIGHT] =  {"                ",
									"                ",
									"        __      ",
									"      .' o)=-   ",
									"     /.-.'      ",
									"    //  |\\      ",
									"    ||  |'      ",
									"    ,(_/_       ",
									"                ",
									"                ",};
const char* CARD_F[CARD_HEIGHT] =  {"                ",
									"                ",
									"                ",
									"           (\\-. ",
									"          / _`> ",
									"  _)     / _)=  ",
									" (      / _/    ",
									"  `-.__(___)_   ",
									"                ",
									"                ",};
const char* CARD_G[CARD_HEIGHT] =  {"                ",
									"                ",
									"    __ \\/ __    ",
									"   /o \\{}/ o\\   ",
									"   \\   ()   /   ",
									"    `> /\\ <`    ",
									"    (o/\\/\\o)    ",
									"     )    (     ",
									"                ",
									"                ",};
const char* CARD_H[CARD_HEIGHT] =  {"                ",
									"                ",
									"     \\\\         ",
									"      \\\\_       ",
									"      ( _\\      ",
									"      / \\__     ",
									"     / _/`\"`    ",
									"    {\\  )_      ",
									"      `\"\"\"`     ",
									"                ",};
const char* CARD_I[CARD_HEIGHT] =  {"                ",
									"                ",
									"     _  _       ",
									"    | )/ )      ",
									" \\\\ |//,' __    ",
									" (\")(_)-\"()))=- ",
									"    (\\\\         ",
									"                ",
									"                ",
									"                ",};
const char* CARD_J[CARD_HEIGHT] =  {"                ",
									"      (         ",
									"     `-`-.      ",
									"     '( @ >     ",
									"      _) (      ",
									"     /    )     ",
									"    /_,'  /     ",
									"      \\  /      ",
									"   ===m\"\"m===   ",
									"                ",};
const char PLAYER_COL_SEPARATOR[CARD_HEIGHT] = {'|',
												'|',
												'|',
												' ',
												' ',
												' ',
												' ',
												'|',
												'|',
												'|'};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool PlayAgain();
void PlayGame(Player &player);
void InitializePlayer(Player &player);
void ClearBoard(Player &player);
void ClearBoard(Player &player);
void SetupBoard(Player &player);
void ShuffleDeck(CardType cardDeck[]);
void DealCards(Player &player, CardType cardDeck[]);
void RenderBoard(Player &player);
void DrawRowSeparator(Player &player, const int r);
void DrawColSeparator(Player &player, const int r, const int c, const int i);
void DrawRow(Player &player, const int r);
void DrawCard(Player &player, const int r, const int c, const int i);
void UpdatePlayerPosition(Player &player, int input);
void FlipCard(Player &player, PlayerPosition &firstCard, int *count);
void CheckForMatch(Player &player, PlayerPosition &firstCard);
void FlipAllDown(Player &player);
bool IsGameOver(Player &player, bool quit);
void DisplayResult(Player &player, bool quit);


int main() {
	HWND console = GetConsoleWindow();
	RECT consoleRect;
	GetWindowRect(console, &consoleRect);

	COORD bufferSize = {18 * NUM_COLS + 2, 12 * NUM_ROWS + 4};
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	MoveWindow(console, consoleRect.left, consoleRect.top, 144 * NUM_COLS + 60, 144 * NUM_ROWS + 86, false);

	srand((unsigned int) time(NULL));
	Player player;


	do{

		PlayGame(player);

	}while(PlayAgain());

	return 0;
}

void PlayGame(Player &player) {
	InitializePlayer(player);
	SetupBoard(player);

	int input;
	int count = 0;
	bool quit = false;
	PlayerPosition firstCard;

	do {



		RenderBoard(player);
		cout << "Use the arrow keys or WASD to move, ENTER to select, ESC or Q to quit." << endl;

		input = getch(); //get Player's move


		UpdatePlayerPosition(player, input);


		if(input == KEY_ENTER) {
			FlipCard(player, firstCard, &count);
			//cout << firstCard.row << " " << firstCard.col << endl;
			//cout << count << endl;
		}

		if(input == KEY_ESC || input == KEY_Q) {
			quit = true;
		}

		if(count > 1) {
			RenderBoard(player);
			WaitForKeyPress();
			CheckForMatch(player, firstCard);
			FlipAllDown(player);
			count = 0;
			player.turns++;
		}

	}while(!IsGameOver(player, quit));

	DisplayResult(player, quit);

}

void DisplayResult(Player &player, bool quit) {
	if(!quit) {
		for(int r = 0; r < NUM_ROWS; r++) {
			for(int c = 0; c < NUM_COLS; c++) {

				player.cardBoard[r][c].isRevealed = true;
				player.cardBoard[r][c].isMatched = false;
			}
		}
		player.position.row = -1;
		player.position.col = -1;
		RenderBoard(player);
		cout << "You found all the matches in " << player.turns << " turns!" << endl;
	}

}

bool IsGameOver(Player &player, bool quit) {
	if(quit) {
		return quit;
	}

	for(int r = 0; r < NUM_ROWS; r++) {
		for(int c = 0; c < NUM_COLS; c++) {
			if(!player.cardBoard[r][c].isMatched) {
				return false;
			}
		}
	}

	return true;
}

bool PlayAgain() {
	char input;

	const char validInputs[2] = {'y', 'n'};

	input = GetCharacter("Would you like to play again? (y/n): ", INPUT_ERROR_STRING, validInputs, 2, CC_LOWER_CASE);

	return input == 'y';
}

void FlipCard(Player &player, PlayerPosition &firstCard, int *count) {

	if(!player.cardBoard[player.position.row][player.position.col].isRevealed && !player.cardBoard[player.position.row][player.position.col].isMatched) {
		player.cardBoard[player.position.row][player.position.col].isRevealed = true;
		*count = *count + 1;
		if(*count < 2) {
			firstCard.row = player.position.row;
			firstCard.col = player.position.col;
		}
	}

}

void CheckForMatch(Player &player, PlayerPosition &firstCard) {
	if(player.cardBoard[firstCard.row][firstCard.col].cardType == player.cardBoard[player.position.row][player.position.col].cardType) {
		player.cardBoard[firstCard.row][firstCard.col].isMatched = true;
		player.cardBoard[player.position.row][player.position.col].isMatched = true;
	}
}

void FlipAllDown(Player &player) {
	for(int r = 0; r < NUM_ROWS; r++) {
		for(int c = 0; c < NUM_COLS; c++) {

			player.cardBoard[r][c].isRevealed = false;

		}
	}
}

void UpdatePlayerPosition(Player &player, int input) {
	if((input == KEY_UP || input == KEY_W) && player.position.row > 0) {
		player.position.row--;
	} else if((input == KEY_DOWN || input == KEY_S) && player.position.row < NUM_ROWS - 1) {
		player.position.row++;
	} else if((input == KEY_LEFT || input == KEY_A) && player.position.col > 0) {
		player.position.col--;
	} else if((input == KEY_RIGHT || input == KEY_D) && player.position.col < NUM_COLS - 1) {
		player.position.col++;
	}
}

void SetupBoard(Player &player) {
	ClearBoard(player);
	CardType cardDeck[NUM_CARDS] = {CT_A, CT_A, CT_B, CT_B, CT_C, CT_C, CT_D, CT_D, CT_E, CT_E, CT_F, CT_F, CT_G, CT_G, CT_H, CT_H, CT_I, CT_I, CT_J, CT_J};

	// randomize deck
	ShuffleDeck(cardDeck);

	// Output Shuffled deck order
	/*
	for(int i = 0; i < NUM_CARDS; i++) {
		cout << cardDeck[i] << endl;
	}
	*/

	DealCards(player, cardDeck);

}

void ShuffleDeck(CardType cardDeck[]) {
	for(int i = 0; i < NUM_CARDS; i++) {
		int j = rand() % NUM_CARDS;
		CardType temp = cardDeck[i];
		cardDeck[i] = cardDeck[j];
		cardDeck[j] = temp;
	}
}

void DealCards(Player &player, CardType cardDeck[]) {

	for(int r = 0; r < NUM_ROWS; r++) {
		for(int c = 0; c < NUM_COLS; c++) {
			player.cardBoard[r][c].cardType = cardDeck[r * NUM_COLS + c];
		}
	}

}

void ClearBoard(Player &player) {
	for(int r = 0; r < NUM_ROWS; r++) {
		for(int c = 0; c < NUM_COLS; c++) {
			player.cardBoard[r][c].cardType = CT_NONE;
			player.cardBoard[r][c].isRevealed = false;
			player.cardBoard[r][c].isMatched = false;

		}
	}
}

void InitializePlayer(Player &player) {
	player.turns = 0;
	player.position.row = rand() % NUM_ROWS;
	player.position.col = rand() % NUM_COLS;
}



void DrawRowSeparator(Player &player, const int r) {
	cout << " ";
	for(int c = 0; c < NUM_COLS; c++) {
		if(player.position.row == r) {
			if(player.position.col == c) {
				cout << PLAYER_ROW_SEPARATOR;
			} else {
				cout << DEFAULT_ROW_SEPARATOR;
			}
		} else {
			cout << DEFAULT_ROW_SEPARATOR;
		}
	}
	cout << endl;
}

void DrawColSeparator(Player &player, const int r, const int c, const int i) {

	if(player.position.col == c && player.position.row == r) {
		cout << PLAYER_COL_SEPARATOR[i];
	} else {
		cout << " ";
	}

}

void DrawCard(Player &player, const int r, const int c, const int i) {

	if(player.cardBoard[r][c].isMatched) {
		cout << CARD_BLANK;
	} else if(!player.cardBoard[r][c].isRevealed) {
		cout << CARD_BACK[i];
	} else {
		switch(player.cardBoard[r][c].cardType) {
		case CT_A:
			cout << CARD_A[i];
		break;
		case CT_B:
			cout << CARD_B[i];
		break;
		case CT_C:
			cout << CARD_C[i];
		break;
		case CT_D:
			cout << CARD_D[i];
		break;
		case CT_E:
			cout << CARD_E[i];
		break;
		case CT_F:
			cout << CARD_F[i];
		break;
		case CT_G:
			cout << CARD_G[i];
		break;
		case CT_H:
			cout << CARD_H[i];
		break;
		case CT_I:
			cout << CARD_I[i];
		break;
		case CT_J:
			cout << CARD_J[i];
		break;
		default:
			cout << CARD_BLANK;
		};
	}
}

void DrawRow(Player &player, const int r) {
	for(int i = 0; i < CARD_HEIGHT; i++) {
		cout << " ";
		for(int c = 0; c < NUM_COLS; c++) {


			DrawColSeparator(player, r, c, i);
			DrawCard(player, r, c, i);
			DrawColSeparator(player, r, c, i);

		}
		cout << endl;
	}
}

void RenderBoard(Player &player) {

	ClearScreen();
	//cout << endl;
	for(int r = 0; r < NUM_ROWS; r++) {

		DrawRowSeparator(player, r);
		DrawRow(player, r);
		DrawRowSeparator(player, r);

	}



}

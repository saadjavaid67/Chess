#include<iostream>
#include<string>
#include<conio.h>
using namespace std;


class Board{
protected:
	char chessboard[8][8], pickedPiece = ' ';
	int cursorX = 0, cursorY = 0, input;
public:
	Board(){
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				if (j == 1){
					chessboard[i][j] = 'p';
				}
				else if (j == 6){
					chessboard[i][j] = 'P';
				}
				else if (j == 0){
					if (i == 0 || i == 7)
						chessboard[i][j] = 'r';
					if (i == 1 || i == 6)
						chessboard[i][j] = 'h';
					if (i == 2 || i == 5)
						chessboard[i][j] = 'b';
					if (i == 3)
						chessboard[i][j] = 'k';
					if (i == 4)
						chessboard[i][j] = 'q';
				}
				else if (j == 7){
					if (i == 0 || i == 7)
						chessboard[i][j] = 'R';
					if (i == 1 || i == 6)
						chessboard[i][j] = 'H';
					if (i == 2 || i == 5)
						chessboard[i][j] = 'B';
					if (i == 3)
						chessboard[i][j] = 'Q';
					if (i == 4)
						chessboard[i][j] = 'K';
				}
				else {
					chessboard[i][j] = ' ';
				}
			}
		}
		/*	chessboard[8][8] = {
		{ 'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R' },
		{ 'h', 'p', ' ', ' ', ' ', ' ', 'P', 'H' },
		{ 'b', 'p', ' ', ' ', ' ', ' ', 'P', 'B' },
		{ 'q', 'p', ' ', ' ', ' ', ' ', 'P', 'Q' },
		{ 'k', 'p', ' ', ' ', ' ', ' ', 'P', 'K' },
		{ 'b', 'p', ' ', ' ', ' ', ' ', 'P', 'B' },
		{ 'h', 'p', ' ', ' ', ' ', ' ', 'P', 'H' },
		{ 'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R' },
		};*/
	}
	void drawChessboard() const
	{
		for (int i = 0; i < 8; i++){
			cout << "+---+---+---+---+---+---+---+---+" << endl << "|";
			for (int j = 0; j < 8; j++){
				if (j == cursorX && i == cursorY){
					cout << "[" << chessboard[i][j] << "]|";
				}
				else{
					cout << " " << chessboard[i][j] << " |";
				}
			}
			cout << endl;
		}
		cout << "+---+---+---+---+---+---+---+---+" << endl;
	}

	void pickDrop(){
		if (pickedPiece == ' '){
			pickedPiece = chessboard[cursorY][cursorX];
			chessboard[cursorY][cursorX] = ' ';
		}
		else if (chessboard[cursorY][cursorX] == ' '){
			chessboard[cursorY][cursorX] = pickedPiece;
			pickedPiece = ' ';
		}
	}

	void draw(){
		do{
			system("cls");
			drawChessboard();
			input = _getch();
			switch (input){
			case 72:
				if (cursorY == 0){
					cursorY = 7;
				}
				else{
					cursorY--;
				}
				break;
			case 80:
				if (cursorY == 7){
					cursorY = 0;
				}
				else{
					cursorY++;
				}
				break;
			case 77:
				if (cursorX == 7){
					cursorX = 0;
				}
				else{
					cursorX++;
				}
				break;
			case 75:
				if (cursorX == 0){
					cursorX = 7;
				}
				else{
					cursorX--;
				}
				break;
			case 32:
				pickDrop();
				break;
			}
		} while (input != 'q');
	}
};


class Piece :public Board{
protected:
	int positionX, positionY;
public:
	virtual bool move(int) = 0;
	virtual char getSymbol() = 0;
};

class Pawn :public Piece{
	char symbol = 'p';
public:
	char getSymbol(){
		return symbol;
	}
	bool move(int n){
		if (n > 0 && chessboard[positionY][positionX] == 'p'){
			if (positionX == 1){
				for (int i = positionX + 1; i <= n; i++){
					if (chessboard[positionY][i] != ' ')
						return 0;
				}
			}
		}
		else if (positionX != 1){
			if (chessboard[positionY][positionX + 1] == ' '){
				chessboard[positionY][positionX + 1] = 'p';
				chessboard[positionY][positionX] = ' ';
			}
		}
	}
};

class Rook :public Piece{
	char symbol = 'r';
public:
	char getSymbol(){
		return symbol;
	}
	bool move(int n){
		return 0;
	}
};
class King :public Piece{
	char symbol = 'k';
public:
	char getSymbol(){
		return symbol;
	}
	bool move(int n){
		return 0;
	}
};
class Queen :public Piece{
	char symbol = 'q';
public:
	char getSymbol(){
		return symbol;
	}
	bool move(int n){
		return 0;
	}
};
class Horse :public Piece{
	char symbol = 'h';
public:
	char getSymbol(){
		return symbol;
	}
	bool move(int n){
		return 0;
	}
};
class Bishop :public Piece{
	char symbol = 'b';
public:
	char getSymbol(){
		return symbol;
	}
	bool move(int n){
		return 0;
	}
};



int main(){
	Board b;
	b.draw();
}
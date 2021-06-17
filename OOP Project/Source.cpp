#include<iostream>
#include<string>
#include<conio.h>
using namespace std;



class Piece{
protected:
	int positionX, positionY;
public:
	virtual bool isValid(int[2], int[2]) = 0;
	virtual char getSymbol() = 0;

};

class Pawn :public Piece{
	char symbol = 'p';
	int player;
	bool kill = false;
public:
	Pawn(int a){
		player = a;
		if (a == 1){
			symbol = 'p';
		}
		else if (a == 2){
			symbol = 'P';
		}
	}
	char getSymbol(){
		return symbol;
	}
	bool isValid(int from[2], int to[2]){
		return 1;
	}
};

class Rook :public Piece{
	char symbol = 'r';
	int player;
public:
	Rook(int a){
		player = a;
		if (a == 1){
			symbol = 'r';
		}
		else if (a == 2){
			symbol = 'R';
		}
	}
	char getSymbol(){
		return symbol;
	}
 bool isValid(int from[2], int to[2]){
		return 0;
	}
};
class Blank :public Piece{
	char symbol = ' ';
public:
	Blank(int a){

	}
	char getSymbol(){
		return symbol;
	}
 bool isValid(int from[2], int to[2]){
		return 0;
	}
};
class King :public Piece{
	char symbol = 'k';
	int player;
public:
	King(int a){
		player = a;
		if (a == 1){
			symbol = 'k';
		}
		else if (a == 2){
			symbol = 'K';
		}
	}
	char getSymbol(){
		return symbol;
	}
 bool isValid(int from[2], int to[2]){
		return 0;
	}
};
class Queen :public Piece{
	char symbol = 'q';
	int player;
public:
	Queen(int a){
		player = a;
		if (a == 1){
			symbol = 'q';
		}
		else if (a == 2){
			symbol = 'Q';
		}
	}
	char getSymbol(){
		return symbol;
	}
 bool isValid(int from[2], int to[2]){
		return 0;
	}
};
class Horse :public Piece{
	char symbol = 'h';
	int player;
public:
	Horse(int a){
		player = a;
		if (a == 1){
			symbol = 'h';
		}
		else if (a == 2){
			symbol = 'H';
		}
	}
	char getSymbol(){
		return symbol;
	}
 bool isValid(int from[2], int to[2]){
		return 0;
	}
};
class Bishop :public Piece{
	char symbol = 'b';
	int player;
public:
	Bishop(int a){
		player = a;
		if (a == 1){
			symbol = 'b';
		}
		else if (a == 2){
			symbol = 'B';
		}
	}
	char getSymbol(){
		return symbol;
	}
 bool isValid(int from[2], int to[2]){
		return 0;
	}
};

class Board{
protected:
	Piece *chessboard[8][8];
	Piece *pickedPiece = new Blank(1);
	int cursorX = 0, cursorY = 0, input;
public:
	Board(){
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				if (j == 1){
					chessboard[i][j] = new Pawn(1);
				}
				else if (j == 6){
					chessboard[i][j] = new Pawn(2);
				}
				else if (j == 0){
					if (i == 0 || i == 7)
						chessboard[i][j] = new Rook(1);
					if (i == 1 || i == 6)
						chessboard[i][j] = new Horse(1);
					if (i == 2 || i == 5)
						chessboard[i][j] = new Bishop(1);
					if (i == 3)
						chessboard[i][j] = new King(1);
					if (i == 4)
						chessboard[i][j] = new Queen(1);
				}
				else if (j == 7){
					if (i == 0 || i == 7)
						chessboard[i][j] = new Rook(2);
					if (i == 1 || i == 6)
						chessboard[i][j] = new Horse(2);
					if (i == 2 || i == 5)
						chessboard[i][j] = new Bishop(2);
					if (i == 3)
						chessboard[i][j] = new Queen(2);
					if (i == 4)
						chessboard[i][j] = new King(2);
				}
				else {
					chessboard[i][j] = new Blank(1);
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
					cout << "[" << chessboard[i][j]->getSymbol() << "]|";
				}
				else{
					cout << " " << chessboard[i][j]->getSymbol() << " |";
				}
			}
			cout << endl;
		}
		cout << "+---+---+---+---+---+---+---+---+" << endl;
	}

	void pickDrop(){
		static int to[2];static int from[2];
		if (pickedPiece->getSymbol() == ' '){
			from[0] = cursorX;
			from[1] = cursorY;
			pickedPiece = chessboard[cursorY][cursorX];
			chessboard[cursorY][cursorX] = new Blank(1);
		}else if (chessboard[cursorY][cursorX]->getSymbol() == ' '){
			cout << from[0];
			to[0] = cursorX;
			to[1] = cursorY;
			if (pickedPiece->isValid(from, to))
				chessboard[cursorY][cursorX] = pickedPiece;
			else{
				chessboard[from[1]][from[0]] = pickedPiece;
			}
			pickedPiece = new Blank(1);
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



int main(){
	Board b;
	b.draw();
}

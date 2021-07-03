#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<conio.h>
#include<cmath>
#include<chrono>
#include<ctime>
using namespace std;
using namespace chrono;


#include "Header.h"



string spaceToDash(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isspace(s[i]) && i != s.length() - 1)
            s[i] = '_';
        if (s[i] == '\n')
            s.erase(i, 1);

    }
    return s;
}
string getTime()
{
    auto timenow = system_clock::to_time_t(system_clock::now());
    return  spaceToDash(ctime(&timenow));
}
void activityLog(string s) {
    ofstream file;
    file.open("activity.log", ios::app);
    file << "[" << getTime() << "]: " << s << endl;
    file.close();
}


bool Player::getTurn()
{
    return turn;
}
void Player::addKilled(char _killed)
{
    killed += _killed;
}
void Player::addKilled(string _killed)
{
    killed += _killed;
}
string Player::getKilled()
{
    return killed;
}
void Player::setTurn(bool _turn)
{
    turn = _turn;
}
void Player::setPlayer(int p)
{
    player = p;
}
int Player::getPlayer()
{
    return player;
}
void Player::addPoints(int s)
{
    points += s;
}
int Player::getPoints()
{
    return points;
}
Player::Player() {
    points = 0;
    setPlayer(2);
    setTurn(false);

};
Player::Player(int a)
{
    points = 0;
    if (a == 1)
    {
        setTurn(true);
    }
    else
    {
        setTurn(false);
    }
    if (a == 1 || a == 2)
        setPlayer(a);
}


Computer::Computer() {
    setPlayer(2);
}
void Computer::move() {

}


bool Piece::kill(int x[2], int y[2], Piece* chessboard[8][8])
{
    if (isValid(x, y, chessboard))
    {
        return 1;
    }
    return 0;
}
int Piece::getPlayer()
{
    return player;
}


void predictMoves(Player p, Piece* chessboard[8][8], bool check = false)
{
    int from[2];
    int to[2];

    int king1[2] = {-1};
    int king2[2] = {-1};
    if (check) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (chessboard[i][j]->getSymbol() == 'k') {
                    king1[0] = j;
                    king1[1] = i;
                }
                if (chessboard[i][j]->getSymbol() == 'K') {
                    king2[0] = j;
                    king2[1] = i;
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            from[0] = j;
            from[1] = i;
            if (chessboard[i][j]->getPlayer() == p.getPlayer()) {
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        to[0] = l;
                        to[1] = k;
                        if (check) {
                            if (chessboard[i][j]->isValid(from, to, chessboard) && chessboard[to[1]][to[0]]->getSymbol() == ' ') {
                                if (king1[0] == l && king1[1] == k|| king2[0] == l && king2[1] == k) {
                                    cout << "check" << endl;
                                    cout << chessboard[i][j]->getSymbol() << "(" << i + 1 << (char)(j + 97) << ") can move to " << k + 1 << (char)(l + 97) << endl;
                                }
                            }
                            else if (chessboard[i][j]->kill(from, to, chessboard) && chessboard[to[1]][to[0]]->getSymbol() != ' ' && chessboard[to[1]][to[0]]->getPlayer() != p.getPlayer()) {
                                if (king1[0] == l && king1[1] == k || king2[0] == l && king2[1] == k) {
                                    cout << "check" << endl;
                                    cout << chessboard[i][j]->getSymbol() << "(" << i + 1 << (char)(j + 97) << ") can move to " << k + 1 << (char)(l + 97) << endl;
                                }
                            }
                        }
                        if (!check) {
                            if (chessboard[from[1]][from[0]]->isValid(from, to, chessboard) && chessboard[to[1]][to[0]]->getSymbol() == ' ') {
                                cout << chessboard[i][j]->getSymbol() << "(" << i + 1 << (char)(j + 97) << ") can move to " << k + 1 << (char)(l + 97) << endl;

                            }
                            else if (chessboard[i][j]->kill(from, to, chessboard) && chessboard[to[1]][to[0]]->getSymbol() != ' ' && chessboard[to[1]][to[0]]->getPlayer() != p.getPlayer()) {
                                cout << chessboard[i][j]->getSymbol() << "(" << i + 1 << (char)(j + 97) << ") can mov e to " << k + 1 << (char)(l + 97) << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    if (!check)
        system("pause");

    //return 0;
}

/*    chessboard[8][8] = {
{ 'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R' },
{ 'h', 'p', ' ', ' ', ' ', ' ', 'P', 'H' },
{ 'b', 'p', ' ', ' ', ' ', ' ', 'P', 'B' },
{ 'q', 'p', ' ', ' ', ' ', ' ', 'P', 'Q' },
{ 'k', 'p', ' ', ' ', ' ', ' ', 'P', 'K' },
{ 'b', 'p', ' ', ' ', ' ', ' ', 'P', 'B' },
{ 'h', 'p', ' ', ' ', ' ', ' ', 'P', 'H' },
{ 'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R' },
};
*/

Pawn::Pawn(int a)
{
    value = 1;
    player = a;
    if (a == 1)
    {
        symbol = 'p';
    }
    else if (a == 2)
    {
        symbol = 'P';
    }
}
bool Pawn::kill(int x[2], int y[2], Piece* chessboard[8][8])
{
    if (symbol == 'P' && (x[0] == (y[0] + 1)) && (x[1] == (y[1] - 1) || x[1] == (y[1] + 1)))
    {
        return 1;
    }
    else if (symbol == 'p' && (x[0] == (y[0] - 1)) && (x[1] == (y[1] - 1) || x[1] == (y[1] + 1)))
    {
        return 1;
    }
    return 0;
}
char Pawn::getSymbol()
{
    return symbol;
}
bool Pawn::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    if (symbol == 'p')         //Movement for p
    {

        if ((to[0] == (from[0] + 1)) && (to[1] == from[1]))
            return 1;
        else if ((to[0] == (from[0] + 2)) && (to[1] == from[1]) && (from[0] == 1))
        {
            if (chessboard[from[1]][from[0] + 1]->getSymbol() != ' ')  return 0;
            return 1;
        }
        return 0;
    }
    else        //Movement for P
    {
        if ((to[0] == (from[0] - 1)) && (to[1] == from[1]))
            return 1;
        else if ((to[0] == (from[0] - 2)) && (to[1] == from[1]) && (from[0] == 6))    //If first move then Two spaces movement possible
        {
            if (chessboard[from[1]][from[0] - 1]->getSymbol() != ' ')
            {
                return 0;
            }
            return 1;

        }
        return 0;
    }
    return 0;
}

Rook::Rook(int a)
{
    value = 2;
    player = a;
    if (a == 1)
    {
        symbol = 'r';
    }
    else if (a == 2)
    {
        symbol = 'R';
    }
}
char Rook::getSymbol()
{
    return symbol;
}
bool Rook::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    if (from[0] == to[0])
    {
        if (from[1] < to[1])
        {
            for (int i = from[1] + 1; i < to[1]; i++)
            {
                if (chessboard[i][from[0]]->getSymbol() != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }

        else
        {

            for (int i = from[1] - 1; i > to[1]; i--) {
                if (chessboard[i][from[0]]->getSymbol() != ' ') {
                    return 0;
                }
            }
            return 1;
        }
    }


    else if (from[1] == to[1])
    {
        if (symbol == 'r')
        {
            for (int i = from[0] + 1; i < to[0]; i++)
            {
                if (chessboard[from[1]][i]->getSymbol() != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }
        else if (symbol == 'R')
        {
            for (int i = from[0] - 1; i > to[0]; i--)
            {
                if (chessboard[from[1]][i]->getSymbol() != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }
    }

    return 0;
}

Blank::Blank(int a)
{
    symbol = ' ';
}
char Blank::getSymbol() {
    return symbol;
}
bool Blank::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    return 0;
}

King::King(int a)
{
    value = 6;
    player = a;
    if (a == 1)
    {
        symbol = 'k';
    }
    else if (a == 2)
    {
        symbol = 'K';
    }
}
char King::getSymbol()
{
    return symbol;
}
bool King::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    if ((from[1] == to[1]) && ((to[0] == (from[0] + 1)) || (to[0] == (from[0] - 1))))  //King can move one space forward or one space backward in the same row
    {
        return 1;
    }
    else if ((from[0] == to[0]) && ((to[1] == (from[1] + 1)) || (to[1] == (from[1] - 1))))   //King can move one space up or one space down in the same column
    {
        return 1;
    }
    else if (((to[0] == (from[0] - 1)) && (to[1] == (from[1] - 1))) || ((to[0] == (from[0] + 1)) && (to[1] == (from[1] + 1))))   //King movement "\"
    {
        return 1;
    }

    else if (((to[0] == (from[0] - 1)) && (to[1] == (from[1] + 1))) || ((to[0] == (from[0] + 1)) && (to[1] == (from[1] - 1))))  //King movement "/"
    {
        return 1;
    }
    return 0;
}

Queen::Queen(int a)
{
    value = 5;
    player = a;
    if (a == 1)
    {
        symbol = 'q';
    }
    else if (a == 2)
    {
        symbol = 'Q';
    }
}
char Queen::getSymbol()
{
    return symbol;
}
bool Queen::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    int i, j;

    if (from[0] == to[0])
    {
        if (from[1] < to[1])
        {
            for (int i = from[1] + 1; i < to[1]; i++) {
                if (chessboard[i][from[0]]->getSymbol() != ' ') {
                    return 0;
                }
            }
            return 1;
        }

        else
        {

            for (int i = from[1] - 1; i > to[1]; i--) {
                if (chessboard[i][from[0]]->getSymbol() != ' ') {
                    return 0;
                }
            }
            return 1;
        }
    }


    else if (from[1] == to[1])
    {
        if (symbol == 'q')
        {
            for (int i = from[0] + 1; i < to[0]; i++) {
                if (chessboard[from[1]][i]->getSymbol() != ' ') {
                    return 0;
                }
            }
            return 1;
        }
        else if (symbol == 'Q')
        {
            for (int i = from[0] - 1; i > to[0]; i--)
            {
                if (chessboard[from[1]][i]->getSymbol() != ' ')
                {
                    return 0;
                }
            }
            return 1;
        }
    }


    else if (to[1] - from[1] == to[0] - from[0])
    {
        if (from[0] < to[0])
        {
            for (i = from[0] + 1, j = from[1] + 1; i < to[0] && j < to[1]; ++i, ++j)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
                else;
            }
            return 1;
        }
        else if (from[0] > to[0])
        {
            for (i = from[0] - 1, j = from[1] - 1; i > to[0] && j > to[1]; i--, j--)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
        return 0;
    }

    else if (from[1] - to[1] == to[0] - from[0])
    {
        if (from[0] > to[0])
        {
            for (i = from[0] - 1, j = from[1] + 1; i > to[0] && j < to[1]; i--, j++)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
        else if (from[0] < to[0])
        {
            for (i = from[0] + 1, j = from[1] - 1; i < to[0] && j > to[1]; i++, j--)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
    }

    return 0;

}

Horse::Horse(int a)
{
    value = 4;
    player = a;
    if (a == 1)
    {
        symbol = 'h';
    }
    else if (a == 2)
    {
        symbol = 'H';
    }
}
char Horse::getSymbol()
{
    return symbol;
}
bool Horse::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    if ((to[0] == (from[0] - 1)) && (to[1] == (from[1] - 2)))  return 1;
    else if ((to[0] == (from[0] - 2)) && (to[1] == (from[1] - 1)))  return 1;

    else if ((to[0] == (from[0] - 2)) && (to[1] == (from[1] + 1)))  return 1;
    else if ((to[0] == (from[0] - 1)) && (to[1] == (from[1] + 2)))  return 1;

    else if ((to[0] == (from[0] + 1)) && (to[1] == (from[1] - 2)))  return 1;
    else if ((to[0] == (from[0] + 2)) && (to[1] == (from[1] - 1)))  return 1;

    else if ((to[0] == (from[0] + 2)) && (to[1] == (from[1] + 1)))  return 1;
    else if ((to[0] == (from[0] + 1)) && (to[1] == (from[1] + 2)))  return 1;

    return 0;
}

Bishop::Bishop(int a)
{
    value = 3;
    player = a;
    if (a == 1)
    {
        symbol = 'b';
    }
    else if (a == 2)
    {
        symbol = 'B';
    }
}
char Bishop::getSymbol()
{
    return symbol;
}
bool Bishop::isValid(int from[2], int to[2], Piece* chessboard[8][8])
{
    int i, j;
    if (to[1] - from[1] == to[0] - from[0])
    {
        if (from[0] < to[0])
        {
            for (i = from[0] + 1, j = from[1] + 1; i < to[0] && j < to[1]; i++, j++)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
        else if (from[0] > to[0])
        {
            for (i = from[0] - 1, j = from[1] - 1; i > to[0] && j > to[1]; i--, j--)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
        return 0;
    }

    else if (from[1] - to[1] == to[0] - from[0])
    {
        if (from[0] > to[0])
        {
            for (i = from[0] - 1, j = from[1] + 1; i > to[0] && j < to[1]; i--, j++)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
        else if (from[0] < to[0])
        {
            for (i = from[0] + 1, j = from[1] - 1; i < to[0] && j > to[1]; i++, j--)
            {
                if (chessboard[j][i]->getSymbol() != ' ')
                    return 0;
            }
            return 1;
        }
    }
    return 0;
}


int showMenu(string list[], int SIZE)
{
    int cursor = 0, choice;
    do
    {
        system("cls");
        cout << "=========   | |     | |  ========   ========  ========\n";
        cout << "| |         | |     | |  | |        | |       | |     \n";
        cout << "| |         |  =====  |  ========   ========  ========\n";
        cout << "| |         | |     | |  | |             | |       | |\n";
        cout << "=========   | |     | |  ========   ========  ========\n";

        cout << "\n\n\n";
        for (int i = 0; i < SIZE; i++)
        {
            cout << setw(16) << setfill(' ') << right;
            if (cursor == i)
                cout << "[" << list[i] << "]" << endl;
            else
                cout << " " << list[i] << endl;
        }
        choice = _getch();
        switch (choice)
        {

        case 80:
            if (cursor == SIZE - 1)
                cursor = 0;
            else
                cursor++;
            break;
        case 72:
            if (cursor == 0)
                cursor = SIZE - 1;
            else
                cursor--;
            break;
        case 13:
            return cursor;
            break;
        }
    } while (choice != 13);
}


Board::Board(string _user)
{
    user = _user;
    p2 = new Computer;
    ifstream file("SaveData\\" + user + ".txt");
    if (!file) {
        cout << "Saved Data not found!" << endl;
        system("pause");
        exit(0);
    }
    else {
        string c;
        int k = 0;
        getline(file, c);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (c[k] == ' ') {
                    chessboard[i][j] = new Blank(1);
                }
                else if (c[k] == 'p') {
                    chessboard[i][j] = new Pawn(p1.getPlayer());
                }
                else if (c[k] == 'P') {
                    chessboard[i][j] = new Pawn(p2->getPlayer());
                }
                else if (c[k] == 'r') {
                    chessboard[i][j] = new Rook(p1.getPlayer());
                }
                else if (c[k] == 'R') {
                    chessboard[i][j] = new Rook(p2->getPlayer());
                }
                else if (c[k] == 'h') {
                    chessboard[i][j] = new Horse(p1.getPlayer());
                }
                else if (c[k] == 'H') {
                    chessboard[i][j] = new Horse(p2->getPlayer());
                }
                else if (c[k] == 'b') {
                    chessboard[i][j] = new Bishop(p1.getPlayer());
                }
                else if (c[k] == 'B') {
                    chessboard[i][j] = new Bishop(p2->getPlayer());
                }
                else if (c[k] == 'k') {
                    chessboard[i][j] = new King(p1.getPlayer());
                }
                else if (c[k] == 'K') {
                    chessboard[i][j] = new King(p2->getPlayer());
                }
                else if (c[k] == 'q') {
                    chessboard[i][j] = new Queen(p1.getPlayer());
                }
                else if (c[k] == 'Q') {
                    chessboard[i][j] = new Queen(p2->getPlayer());
                }
                k++;
            }
        }
        getline(file, c);
        if (!stoi(c)) {
            nextTurn();
        }
        getline(file, c);
        p1.addKilled(c);
        getline(file, c);
        p2->addKilled(c);
        getline(file, c);
        p1.addPoints(stoi(c));
        getline(file, c);
        p2->addPoints(stoi(c));
        getline(file, c);
        playerName = c;
    }
    
}
Board::Board(string _user, string _playerName, int p) {    //for single player pass 1 & for multiplayer pass 2
    user = _user;
    playerName = _playerName;
    if (p == 1) {
        p2 = new Computer;
    }
    else if (p == 2) {
        p2 = new Player(2);
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j == 1)
            {
                chessboard[i][j] = new Pawn(p1.getPlayer());
            }
            else if (j == 6)
            {
                chessboard[i][j] = new Pawn(p2->getPlayer());
            }
            else if (j == 0)
            {
                if (i == 0 || i == 7)
                    chessboard[i][j] = new Rook(p1.getPlayer());
                if (i == 1 || i == 6)
                    chessboard[i][j] = new Horse(p1.getPlayer());
                if (i == 2 || i == 5)
                    chessboard[i][j] = new Bishop(p1.getPlayer());
                if (i == 3)
                    chessboard[i][j] = new King(p1.getPlayer());
                if (i == 4)
                    chessboard[i][j] = new Queen(p1.getPlayer());
            }
            else if (j == 7)
            {
                if (i == 0 || i == 7)
                    chessboard[i][j] = new Rook(p2->getPlayer());
                if (i == 1 || i == 6)
                    chessboard[i][j] = new Horse(p2->getPlayer());
                if (i == 2 || i == 5)
                    chessboard[i][j] = new Bishop(p2->getPlayer());
                if (i == 3)
                    chessboard[i][j] = new Queen(p2->getPlayer());
                if (i == 4)
                    chessboard[i][j] = new King(p2->getPlayer());
            }
            else
            {
                chessboard[i][j] = new Blank(1);
            }
        }
    }
    /*    chessboard[8][8] = {
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
void Board::drawChessboard()
{
    for (int i = 0; i < 8; i++)
    {
        cout << " +---+---+---+---+---+---+---+---+" << endl << i + 1 << "|";
        for (int j = 0; j < 8; j++)
        {
            if (j == cursorX && i == cursorY)
            {
                cout << "[" << chessboard[i][j]->getSymbol() << "]|";
            }
            else
            {
                cout << " " << chessboard[i][j]->getSymbol() << " |";
            }
        }
        cout << endl;
    }
    cout << " +---+---+---+---+---+---+---+---+\n"
        << "   a   b   c   d   e   f   g   h\n\n\n\n"
        << "+-------------------+-------------------+\n"
        << "|  " << setw(17) << setfill(' ') << left << user << "|  " << setw(17) << setfill(' ') << playerName << "|\n"
        << "+-------------------+-------------------+\n"
        << "|  Points " << setw(10) << left << setfill(' ') << p1.getPoints() << "|  Points " << setw(10) << left << setfill(' ') << p2->getPoints() << "|\n"
        << "|  Kills:           |  Kills:           |\n"
        << "|  " << setw(16) << left << setfill(' ') << p1.getKilled() << " |  " << setw(16) << left << setfill(' ') << p2->getKilled() << " |\n"
        << "+-------------------+-------------------+\n";
}
void Board::nextTurn(int p)
{
    if (p1.getTurn())
    {
        p1.setTurn(false);
        p2->setTurn(true);
        p1.addPoints(p);
    }
    else if (p2->getTurn())
    {
        p1.setTurn(true);
        p2->setTurn(false);
        p2->addPoints(p);
    }
}
void Board::pickDrop()
{
    static int to[2]; static int from[2];
    if (pickedPiece->getSymbol() == ' ')
    {
        if (p1.getTurn())
        {
            from[0] = cursorX;
            from[1] = cursorY;
            if (chessboard[cursorY][cursorX]->getPlayer() == p1.getPlayer())
            {
                pickedPiece = chessboard[cursorY][cursorX];
                chessboard[cursorY][cursorX] = new Blank(1);
            }
        }
        else if (p2->getTurn())
        {
            from[0] = cursorX;
            from[1] = cursorY;
            if (chessboard[cursorY][cursorX]->getPlayer() == p2->getPlayer())
            {
                pickedPiece = chessboard[cursorY][cursorX];
                chessboard[cursorY][cursorX] = new Blank(1);
            }
        }
    }
    else if (chessboard[cursorY][cursorX]->getSymbol() == ' ')
    {
        to[0] = cursorX;
        to[1] = cursorY;
        if (pickedPiece->isValid(from, to, chessboard))
        {
            chessboard[cursorY][cursorX] = pickedPiece;
            if (from[0] == to[0] && from[1] == to[1])
            {
                return;
            }
            nextTurn(10);
        }
        else
        {
            chessboard[from[1]][from[0]] = pickedPiece;
        }
        pickedPiece = new Blank(1);

    }
    else if (chessboard[cursorY][cursorX]->getSymbol() != ' ')
    {
        to[0] = cursorX;
        to[1] = cursorY;
        if (pickedPiece->getPlayer() != chessboard[to[1]][to[0]]->getPlayer() && pickedPiece->kill(from, to, chessboard)) {
            if (p1.getTurn())
            {
                p1.addKilled(chessboard[cursorY][cursorX]->getSymbol());
            }
            else if (p2->getTurn())
            {
                p2->addKilled(chessboard[cursorY][cursorX]->getSymbol());
            }
            chessboard[cursorY][cursorX] = pickedPiece;
            if (from[0] == to[0] && from[1] == to[1])
            {
                return;
            }
            nextTurn(80);

        }
        else
        {
            chessboard[from[1]][from[0]] = pickedPiece;
        }
        pickedPiece = new Blank(1);

    }
}
void Board::draw()
{
    do
    {
        system("cls");
        drawChessboard();
        if (p1.getTurn())
            predictMoves(*p2, chessboard, true);
        else if (p2->getTurn())
            predictMoves(p1, chessboard, true);
        input = _getch();
        switch (input)
        {
        case 72:
            if (cursorY == 0)
            {
                cursorY = 7;
            }
            else
            {
                cursorY--;
            }
            break;
        case 80:
            if (cursorY == 7)
            {
                cursorY = 0;
            }
            else
            {
                cursorY++;
            }
            break;
        case 77:
            if (cursorX == 7)
            {
                cursorX = 0;
            }
            else {
                cursorX++;
            }
            break;
        case 75:
            if (cursorX == 0)
            {
                cursorX = 7;
            }
            else
            {
                cursorX--;
            }
            break;
        case 'p':
            if (p1.getTurn())
                predictMoves(p1, chessboard);
            else if (p2->getTurn())
                predictMoves(*p2, chessboard);
            break;
        case 32:
            pickDrop();
            break;
        }
    } while (input != 'q');
    string list[2] = { " Save Game ", " Quit Game " };
    int choice = showMenu(list, 2);
    if (choice == 0)
    {
        ofstream file("SaveData\\" + user + ".txt");
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                file << chessboard[i][j]->getSymbol();
            }
        }
        file << endl << p1.getTurn() << endl << p1.getKilled() << endl << p2->getKilled() << endl << p1.getPoints() << endl << p2->getPoints() << endl << playerName;
    }
}


void Game::writeNewAcc(createAcc newAcc) {
    ofstream file;
    file.open("users.dat", ios::app);
    file << setw(50) << setfill('=') << "\n";
    file << "username: " << newAcc.username << endl;
    file << "password: " << newAcc.password << endl;
    file << "fname: " << newAcc.fname << endl;
    file << "lname: " << newAcc.lname << endl;
    file << "Time of Account Creation: " << getTime() << endl;
    file << setw(50) << setfill('=') << "\n";
    file.close();
    cout << "\nYou have Created an Account Successfully!\n";
    system("pause");
}
int Game::accountInfo() {
    cout << "Current Account Information";
    cout << "\nName: " << fname << " " << lname
        << "\nUsername: " << username
        << "\nPassword: " << password
        << "\nTime of Account Creation: " << TOC << "\n\n";
    system("pause");
    return 1;
}
int Game::checkUser(char username[]) {
    ifstream file("users.dat");
    string s;
    size_t pos;
    string search = "username: " + (string)username;
    while (file.good())
    {
        getline(file, s);
        pos = s.find(search);
        if (pos != string::npos && s.size() == search.size())
        {
            cout << "\nUser with this Username Already Exists! Try another Username.\n";
            return 1;
        }
    }
    return 0;
}
//Creates Account
void Game::createAccount() {
    createAcc newAcc;
    cout << "Create An Account\n";
    cout << "Enter your First Name: "; cin >> newAcc.fname;
    cout << "Enter your Last Name: "; cin >> newAcc.lname;
    do {
        cout << "Enter a Username: "; cin >> newAcc.username;
        int i = 0;
        while (newAcc.username[i] != '\0') {
            if (newAcc.username[i] >= 97 && newAcc.username[i] <= 122)
            {
                newAcc.username[i] = newAcc.username[i] - 32; //Converts Uppercase to Lowercase.
            }
            i++;
        }
    } while (checkUser(newAcc.username));
    int length = 0, a = 0;
    do {
        if (a > 0)
            cout << "\nYour Password Must Contain Minimum of 8 Characters!\n";
        cout << "Enter your Password ";
        if (a > 0)
            cout << "Again";
        else
            cout << "(Minimum 8 Characters)";
        cout << ": ";
        cin >> newAcc.password;

        while (newAcc.password[length] != '\0')
            length++;
        a++;
    } while (length < 8);


    writeNewAcc(newAcc);

}
//void activityLog(string s);
int Game::loginAccount() {
    bool check = 0;
    do {
        system("cls");
        cout << "Login Panel";
        login login;
        cout << "\nEnter a Username: "; cin >> login.username;
        cout << "Enter your Password: "; cin >> login.password;
        int i = 0;
        while (login.username[i] != '\0') { // '\0' null Character tells end of char array
            if (login.username[i] >= 97 && login.username[i] <= 122)
            {
                login.username[i] = login.username[i] - 32; // converting uppercase to lowercase
            }
            i++;
        }
        ifstream file("users.dat");
        if (!file) {
            file.close();
            cout << "\nNo Database Found.\nPlease Signup to create an account.\n";
            system("pause");
        }
        else {
            username = login.username;
            password = login.password;
            string s;
            size_t user_pos;
            size_t pass_pos;
            string user = "username: " + (string)login.username;
            string pass = "password: " + (string)login.password;
            bool acc = 0;
            while (file.good())
            {
                getline(file, s);
                user_pos = s.find(user);
                if (user_pos != string::npos && s.size() == user.size())
                {
                    bool pas = 0;
                    acc = 1;
                    getline(file, s);
                    pass_pos = s.find(pass);
                    if (pass_pos != string::npos && s.size() == pass.size())
                    {
                        pas = 1;
                        getline(file, s, ':');
                        file >> fname;
                        getline(file, s, ':');
                        file >> lname;
                        getline(file, s, ':');
                        file >> TOC;
                        activityLog(username + " Logged In.");
                        check = 1;
                        return 1;
                    }
                    if (!pas) {
                        cout << "\nIncorrect Password.\n";
                        system("pause");
                        check = 0;
                    }
                }

            }
            if (!acc) {
                cout << "\nNo Account found with this Username.\n";
                system("pause");
                check = 0;
            }

            file.close();
        }
    } while (!check);
    return 0;
}
int Game::welcome() {
    int loginChoice;
    string menu[2] = { " Login ", " SignUp " };
    loginChoice = showMenu(menu, 2);
    if (loginChoice == 0) {
        if (loginAccount())
            return 1;
    }
    else if (loginChoice == 1) {
        createAccount();
        system("cls");
        if (welcome())
            return 1;
    }
    return 0;
}
int Game::startGame()
{

    int choice;
    string menu[6] = { " New Game ", " Load Game ", " Account Info ", " History ", " Credits ", " Exit " };
    choice = showMenu(menu, 6);
    if (choice == 0)
    {
        cout << "Please Enter Second Player Name: ";
        cin >> playerName;
        system("CLS");
        cout << "INSTRUCTIONS:\n\n";
        cout << "1. Use your cursor keys to move between rows and columns.\n";
        cout << "2. Use spacebar to pick up your chess piece.\n";
        cout << "3. Move to the place where you want to place the piece and press spacebar.\n";
        cout << "4. Enter 'p' to show possible moves.\n";
        cout << "5. Enter 'q' to quit the current game.\n\n";

        cout << "Press any key to enter the game.\n";
        cin.get(); cin.get();
        activityLog(username + " Started Game with " + playerName + ".");
        Board b(fname + "_" + lname, playerName, 1);
        b.draw();
    }
    else if (choice == 1)
    {
        activityLog(username + " Loaded Saved Game.");
        string user = fname + "_" + lname;
        Board b(user);
        b.draw();
    }
    else if (choice == 2)
    {
        activityLog(username + " Check Account Info.");
        accountInfo();
        system("pause");
        return 1;
    }
    else if (choice == 3)
    {
        activityLog(username + " Checked History.");
        ifstream file("activity.log");
        string s, tempS;
        while (getline(file, s)) {
            if (s.find(username) != string::npos) {
                cout << s << '\n';
            }
        }
        system("pause");
        return 1;
    }
    else if (choice == 4)
    {
        activityLog(username + " Checked Credits.");
        system("CLS");

        cout << setw(30) << "CREDITS\n\n\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(35) << setfill(' ') << "Muhammad Naeem Tahir 056"<<"         |\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(29) << setfill(' ') << "Board Design & Moving Piece" << "               |\n";
        cout << setw(49) << setfill('-') << "\n\n\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(31) << setfill(' ') << "Muhammad Saad 060" << "             |\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(32) << setfill(' ') << "Menu, login design & Saving Game State" << "      |\n";
        cout << setw(49) << setfill('-') << "\n\n\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(31) << setfill(' ') << "Unaiza Naseem 087" << "             |\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(32) << setfill(' ') << "Chess Pieces, Validations & Check Detection" << " |\n";
        cout << setw(49) << setfill('-') << "\n\n\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(31) << setfill(' ') << "Wajeeha Qurban 089" << "             |\n";
        cout << setw(48) << setfill('-') << "\n|";
        cout << setw(29) << setfill(' ') << "Player Points, Turn & Kills" << "               |\n";
        cout << setw(49) << setfill('-') << "\n\n\n";

        cout << "Press any key to return to main menu\n";
        cin.get(); cin.get();
        return 1;
    }
    else if (choice == 5)
    {
        activityLog(username + " Exited.");
        return 0;
    }
}
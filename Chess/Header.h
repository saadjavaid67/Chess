
const int SIZE = 50;
struct login
{
    char username[SIZE];
    char password[SIZE];
};
struct createAcc {
    char fname[SIZE];
    char lname[SIZE];
    char username[SIZE];
    char password[SIZE];
};

class Player
{
    int player;
    int points;
    bool turn;
    string killed;
public:
    bool getTurn();
    void addKilled(char _killed);
    void addKilled(string _killed);
    string getKilled();
    void setTurn(bool _turn);
    void setPlayer(int p);
    int getPlayer();
    void addPoints(int s);
    int getPoints();
    Player();
    Player(int a);
};

class Computer : public Player
{
public:
    Computer();
    void move();
};

class Piece
{
protected:
    int value;
    int player;
    char symbol;
public:
    int isCheck();
    virtual bool isValid(int[2], int[2], Piece* [8][8]) = 0;
    virtual char getSymbol() = 0;
    virtual bool kill(int x[2], int y[2], Piece* chessboard[8][8]);
    int getPlayer();
};
class Pawn :public Piece
{
public:
    Pawn(int a);
    bool kill(int x[2], int y[2], Piece* chessboard[8][8]);
    char getSymbol();
    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};
class Rook :public Piece
{
public:
    Rook(int a);
    char getSymbol();
    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};
class Blank :public Piece
{
public:
    Blank(int a);
    char getSymbol();
    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};
class King :public Piece
{
public:
    King(int a);
    char getSymbol();
    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};
class Queen :public Piece
{
public:
    Queen(int a);
    char getSymbol();
    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};
class Horse :public Piece
{
public:
    Horse(int a);
    char getSymbol();
    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};
class Bishop :public Piece
{
public:
    Bishop(int a);
    char getSymbol();

    bool isValid(int from[2], int to[2], Piece* chessboard[8][8]);
};

class Board
{
protected:
    string user, playerName;
    Piece* chessboard[8][8];
    Piece* pickedPiece = new Blank(1);
    Player p1 = 1;
    Player* p2;
    int cursorX = 0, cursorY = 0, input;
public:
    Board(string _user);
    Board(string _user, string _playerName, int p);
    void drawChessboard();
    void nextTurn(int p = 0);
    void pickDrop();
    void draw();
};

class Game
{
    string fname, lname, username, password, TOC, playerName;
    int day, year, month, menu;
public:
    void writeNewAcc(createAcc newAcc);
    int accountInfo();
    int checkUser(char username[]);
    void createAccount();
    int loginAccount();
    int welcome();
    int startGame();
};
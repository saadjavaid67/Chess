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
#include"Header.h"

int main()
{
    Game g;
    int a;
    if (g.welcome())
        do {
            a = g.startGame();
        } while (a);

        return 0;
}
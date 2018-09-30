#ifndef START_H
#define START_H

#include <windows.h>
#include <conio.h>

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15

//Esconde o cursor no cmd
void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor = { 1, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}


//Pula para a posicao (x, y) no cmd
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Muda a cor de escrita
void textcolor(int text, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(text | background << 4));
}


void cabecalho()
{
	gotoxy(0, 0);
	textcolor(LIGHTYELLOW, BLACK);
	std::cout << "Memoria Cache";
	gotoxy(0, 1);
	textcolor(YELLOW, BLACK);
	std::cout << "Engenharia de Computacao - UNIVALI";
	gotoxy(0, 2);
	std::cout << "Arquitetura de Computadores";
	gotoxy(0, 3);
	std::cout << "Andriy Fujii";
	textcolor(WHITE, BLACK);
}

#endif // START_H

#include "game.h"
#include <iomanip>
#include <Windows.h>
#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int convertToNumber(char letter);

vector<COORD> positions;


void game::render()
{
	plansza.render();
}

void board::render()
{

	COORD posStart;
	posStart.X = 0;
	posStart.Y = 5;

	SetConsoleCursorPosition(h, posStart);
	static CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize.X = 20;
	font.dwFontSize.Y = 20;
	SetCurrentConsoleFontEx(h, NULL , &font);

	string alphabet = "ABCDEFGHIJ";

	cout << setw(5) << " ";
	for (int i{ 0 }; i < 10; i++)
	{
		cout << alphabet[i];
		cout << setw(5) << " ";
	}
	cout << "\n";

	for (int i = 0; i < 10; i++)
	{
		cout << setw(2) <<  i + 1;
		cout << "|";
		for (int j = 0; j < 10; j++)
		{
			cout << setw(3) << "-";
			cout << setw(3) << "|";
		}
		cout << '\n';
	}


}

void pionek::drawPionek(int PosY, int PosX)
{
	COORD pozycja;
	switch (PosX)
	{

	case 1:
		pozycja.X = 3;
		break;
	case 2:
		pozycja.X = 9;
		break;
	case 3:
		pozycja.X = 15;
		break;
	case 4:
		pozycja.X = 21;
		break;
	case 5: 
		pozycja.X = 27;
		break;
	case 6:
		pozycja.X = 33;
		break;
	case 7:
		pozycja.X = 39;
		break;
	case 8:
		pozycja.X = 45;
		break;
	case 9:
		pozycja.X = 51;
		break;
	case 10:
		pozycja.X = 57;
		break;
	default:
		break;
	}


	pozycja.Y = PosY + 5;
	SetConsoleCursorPosition(h, pozycja);
	cout << setw(3)<< "#";
	
	positions.push_back(pozycja);

	
	COORD inpPos;
	inpPos.X = 2;
	inpPos.Y = 2;
	SetConsoleCursorPosition(h, inpPos);

}

void player::wybor_pola()
{
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(h, pos);
	cout << "Podaj pole: (X:Y)";

	string pole;
	cin >> pole;
	int PosY = stoi(pole.substr(pole.length()-1));
	char PosX_s = pole[0];
	int PosX = 0;
	if (convertToNumber(PosX_s) != -1)
	{
		PosX = convertToNumber(PosX_s);
	}
	else
	{
		cout << "Blednia podana liczba" << endl;
		return;
	}

	pionek postac(PosX, PosY, pionek::stan::caly);
	postac.drawPionek(PosY, PosX);
}

int convertToNumber(char letter)
{
	const char iChar = toupper(letter);
	return((iChar >= 'A' && iChar <= 'J') ? iChar - 64 : -1);
}

auto bot::random_pos()
{
	srand(time(0));
	
	int posY = (rand() % 11);
	int posX = (rand() % 11);	
	int pos[2] = {posX, posY};

	return pos;
}

void bot::bot_play()
{
	bot botO;
	auto pos = botO.random_pos();
	auto posX = pos[0];
	auto posY = pos[1];
	COORD position = { posX, posY };

	if (botO.make_guess(pos)) {
		SetConsoleCursorPosition(h, position);
		SetConsoleTextAttribute(h, BACKGROUND_RED);
		SetConsoleCursorPosition(h, { 2 , 3 });
		cout << "Statek zostal zbity! " << endl;
	}
	else
	{
		cout << "Bot nie trafil [" << posX << " ; " << posY << " ]" << endl;
	}

	

}

bool bot::make_guess(int* coord)
{
	auto pos = coord;
	auto posX = coord[0];
	auto posY = coord[1];
	
	for (auto a : positions)
	{
		if (a.Y == posY && a.X == posX)
		{
			return true;
		}
	}
	return false;
}

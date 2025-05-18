#include "game.h"
#include <iomanip>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);



void game::render()
{
	plansza.render();
}

void board::render()
{
	
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
	pionek p();

}

void player::wybor_pola()
{
	cout << "Podaj pole: (X:Y)";

	string pole;
	cin >> pole;
	int PosX = stoi(pole.substr(0));
	string PosY = pole.substr(2);
	
}

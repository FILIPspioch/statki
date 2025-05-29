#include "game.h"
#include <iomanip>
#include <Windows.h>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <regex>
#include <thread>
#include<chrono>


//losowanie
#include <functional>
#include <random>

//pair
#include <utility>



using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int convertToNumber(char letter);
char convertToLetter(int number);
auto rand_c = bind(uniform_int_distribution<int>{0, 9}, default_random_engine{});

vector<COORD> positions;

WORD default_console;
CONSOLE_SCREEN_BUFFER_INFO info;


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
	
	COORD pozycje_w = {PosX, PosY };
	positions.push_back(pozycje_w);

	
	COORD inpPos;
	inpPos.X = 2;
	inpPos.Y = 2;
	SetConsoleCursorPosition(h, inpPos);
	

}

void player::wybor_pola()
{
	GetConsoleScreenBufferInfo(h, &info);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(h, pos);
	string message = "Podaj pole: (X:Y)";
	cout << message;
	
	cout << "    ";
	SetConsoleCursorPosition(h, {(short)(pos.X + message.length()), pos.Y});

	string pole;
	cin >> pole;

	regex wzor("[a-jA-J]:(10|[1-9])");
	smatch wynik;
	if (regex_match(pole, wynik, wzor))
	{
		int PosY = stoi(pole.substr(pole.find_first_of(':') + 1, string::npos));
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
	else
	{
		pos.X = 0;
		pos.Y = 0;
		SetConsoleCursorPosition(h, pos);
		cout << "Zle wprowadzona pozycja! Wpisz jeszcze raz" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		SetConsoleCursorPosition(h, { 0,0 });
		cout <<setw(100) << " ";
		player::wybor_pola();
	}
}

int convertToNumber(char letter)
{
	const char iChar = toupper(letter);
	return((iChar >= 'A' && iChar <= 'J') ? iChar - 64 : -1);
}

char convertToLetter(int number)
{
	const int liczba = number;
	return ((liczba >= 1 && liczba <= 10) ? liczba + 64 : -1);
}

auto bot::random_pos()
{	
	int posY = rand_c();
	int posX = rand_c();	 

	return pair<int, int>{posX, posY};
}

void bot::bot_play()
{
	bot botO;


	COORD m_pos;
	m_pos.X = 5;
	m_pos.Y = 30;

	auto pos = botO.random_pos();
	if (botO.make_guess(pos) != -1) {
		SetConsoleCursorPosition(h, { positions[botO.make_guess(pos)].X, positions[botO.make_guess(pos)].Y});
		SetConsoleTextAttribute(h, BACKGROUND_RED);
		SetConsoleCursorPosition(h, { 2 , 25 });
		cout << "Statek zostal zbity! " << convertToLetter(pos.first) << " ; " << pos.second << endl;
		if (bot::displayLog)
		{

			bot::log(pos.first, pos.second);
		}

		SetConsoleTextAttribute(h, default_console);
	}
	else
	{

		if(bot::displayLog)
		{

			
		bot::log(pos.first, pos.second);
		}
	}
}

int bot::make_guess(pair<int, int>& pozycja)
{
	auto posX = pozycja.first;
	auto posY = pozycja.second;
	
	for (int i{0}; i< 10; i++)
	{
		if (positions[i].Y == posY && positions[i].X == posX)
		{
			return i;
		}	
	}
	return -1;
	
}

void bot::log(int x, int y)
{

	default_console = info.wAttributes;

	
	SetConsoleTextAttribute(h, BACKGROUND_GREEN);

	cout << "|";
	for (int i{ 0 }; i < 10; i++)
	{
		if (i != 5)
		{
			cout << "-";
		}
		else
		{
			cout << "Bot Log";
		}
	}

	cout << "|" << endl;

	cout << "Bot wybral: x = " << convertToLetter(x) << "; y = " << y << endl;

	cout << "|";
	for (int i{ 0 }; i < 10; i++)
	{
		if (i != 5)
		{
			cout << "-";
		}
		else
		{
			cout << "Koniec loga";
		}
	}

	cout << "|" << endl;


	SetConsoleTextAttribute(h, default_console);
}

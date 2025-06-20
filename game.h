#pragma once
#include <vector>
#include<iostream>
#include <utility>


class board
{
public:
	//10 x 10 


	void render();
};

class player
{
public:
	int liczba_pionkow = 10;
	void wybor_pola();
};

class pionek
{
public:
	int posY;
	int posX;

	enum class stan
	{
		zatopiony = 1,
		caly
	};

	stan stanPionka;
public:
	pionek(int posX, int posY, stan stanP)
	{
		this->posX = posX;
		this->posY = posY;
		this->stanPionka = stanP;
	}

	void drawPionek(int PosY, int PosX);

};

class bot
{
public:
	auto random_pos();
	void bot_play();
	int make_guess(std::pair<int, int>& pozycja);
	void log(int x, int y );
	bool displayLog = false;
};

class game
{
public:
	board plansza;
	player gracz;
	void render();

	bool game_stop;
};


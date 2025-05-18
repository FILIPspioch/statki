#pragma once
#include <vector>
#include<iostream>


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
	size_t posY;
	size_t posX;

	enum class stan
	{
		zatopiony,
		caly,
	};

	stan stanPionka;
public:
	pionek(size_t posX, size_t posY, stan stanP)
	{
		this->posX = posX;
		this->posY = posY;
		this->stanPionka = stanP;
	}

	void drawPionek(int PosY, int PosX);
};

class game
{
public:
	board plansza;
	player gracz;
	void render();

	bool game_stop;
};


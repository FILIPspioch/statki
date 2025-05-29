#include <iostream>
#include "game.h"

using namespace std;

void gra();


int main()
{
	gra();
	return 0;
}

void gra()
{
	game gra;
	player gracz;
	gra.render();

	bot Gracz_Bot;

	do
	{	
		
		gracz.wybor_pola();
		gracz.liczba_pionkow--;
		cout << "Pozostało pionkow: " << gracz.liczba_pionkow << " " << endl;
		
		if (gracz.liczba_pionkow == 0)
		{
			cout << "Brak pionkow. Koniec etapu rozstawiania!" << endl;
			break;
		}
	} while (true);

	for (int i{ 0 }; i < 100; i++)
	{
		Gracz_Bot.bot_play();
	}

}
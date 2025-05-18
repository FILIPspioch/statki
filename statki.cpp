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
	do
	{
		gra.render();
		cout << "Pozostało pionków: " << gracz.liczba_pionkow << endl;
		gracz.wybor_pola();
		gracz.liczba_pionkow--;

	} while (gra.game_stop = false);
}
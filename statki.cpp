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
	do
	{		
		cout << "Pozostało pionkow: " << gracz.liczba_pionkow << endl;
		gracz.wybor_pola();
		gracz.liczba_pionkow--;
		if (gracz.liczba_pionkow == 0)
		{
			cout << "Brak pionkow. Koniec etapu rozstawiania!" << endl;
		}

		
	} while (true);
}
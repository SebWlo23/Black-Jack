#include "Kasyno.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>

using namespace std;

int get_safe_intiger(int dol, int gora)
{
	int x;
	cin >> x;
	while (cin.fail() || x <= dol || x >= gora)
	{
		cout << "Podaj poprawna wartosc:";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> x;
	}
	return x;
}

Kasyno::Kasyno()
{
	for (int kolor = 0; kolor < 4; kolor++)
	{
		for (int symbol = 0; symbol < 14; symbol++)
		{
			tabKart[(kolor*13)+symbol] = new Karta(kolor, symbol);			
		}
	}
}

Kasyno::~Kasyno()
{
	delete[] ile_graczy;

	for(int i = 0; i<52; i++)
	{
		delete tabKart[i];
	}
}

void Kasyno::Tasuj()
{
	int i;
	Karta* temp;
	srand(time(NULL));

	for (i = 0; i < 52; i++)
	{
		int x = rand() % 52;
		temp = tabKart[i];
		tabKart[i] = tabKart[x];
		tabKart[x] = temp;
	}
}


Karta* Kasyno::dajKarte()
{		
	Karta* karta = tabKart[index_talii];
	index_talii++;
	return karta;
}

void Kasyno::Graj()
{
	ilosc_wygranych = 0;
	ilosc_graczy = 0;
	cout << "Ile graczy ma grac(1-3):" << endl;
	ilosc_graczy = get_safe_intiger(0,4);
	ile_graczy = new Gracz[ilosc_graczy];
	
	Tasuj();

	for (int i = 0; i < ilosc_graczy; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			ile_graczy[i].wezKarte(dajKarte());
		}
		//ile_graczy[i].pokazReke();
		ile_graczy[i].ustaw_nick();
		ile_graczy[i].znajdz_kasyno(this);
		
		cout << "\n";
	}

	
	int ilosc_pasow = 0;
	while (ilosc_pasow != ilosc_graczy)
	{
		ilosc_pasow = 0;
		for (int i = 0; i < ilosc_graczy; i++)
		{
			
			if (ile_graczy[i].czy_pasuje() == 0)
			{
				cout << endl << "Gracz " << ile_graczy[i].daj_nick() << endl;
				//ile_graczy[i].wezKarte(dajKarte());
				ile_graczy[i].pokazReke();
				cout << "Punkty " << ile_graczy[i].iloscPunktow() << endl;
				ile_graczy[i].wybor_gracza();

				if (ile_graczy[i].czy_pasuje() == 0)
				{
					ile_graczy[i].wezKarte(dajKarte());
				}
			}
			else
			{
				ilosc_pasow++;
			}
		}
	}

	int najwieksza = 0;
	int tab_pzegranych[10];
	for (int i = 0; i < ilosc_graczy; i++)
	{
		if (ile_graczy[i].iloscPunktow() == 21)
		{
			cout << "Zwyciezcy: " << ile_graczy[i].daj_nick() << "\n";
			ilosc_wygranych++;
		}
		else
		{
			tab_pzegranych[i] = ile_graczy[i].iloscPunktow();
		}
	}

	if (ilosc_wygranych == 0 )
	{
		bool zmiana = false;
		for (int i = 0; i < ilosc_graczy - ilosc_wygranych; i++)
		{
			if (tab_pzegranych[i] > najwieksza && tab_pzegranych[i] < 21)
			{
				najwieksza = tab_pzegranych[i];
			}
		}

		for (int i = 0; i < ilosc_graczy - ilosc_wygranych; i++)
		{
			if (ile_graczy[i].iloscPunktow() == najwieksza)
			{
				cout << "Zwyciezcy: " << ile_graczy[i].daj_nick() << "\n";
				zmiana = true;
			}
			
		}
		if (zmiana == false)
		{
			cout << "Brak zwyciezcow" << "\n";
		}
	}

	for (int i = 0; i < 10; i++)
	{
		tab_pzegranych[i] = 0;
	}

	int wybor1 = 0;

	zapisz_gre();
	cout << "\n" << "Zapisano w pliku wyniki.txt" << endl;
	do 
	{
		cout << "\n" << "Chcesz zagrac jeszcze raz?" << endl;
		cout << "1. Tak " << endl;
		cout << "2. Nie" << endl;
		cout << "Wybieram: ";
			 wybor1 = get_safe_intiger(0,3);
		
		switch (wybor1)
		{
		case 1:
			system("cls");
			nowa_gra();
			break;
		case 2:
			break;
		default:
			cout << "Nie ma takiej opcji" << endl;
		}

	}while (wybor1 < 1 && wybor1 > 2);

}

void Kasyno::nowa_gra()
{
	delete[] ile_graczy;
	index_talii = 0;
	
	ilosc_wygranych = 0;
	Graj();
}


void Kasyno::zapisz_gre()
{
	fstream plik;
	plik.open("wyniki.txt", ifstream::app);
	if (plik.is_open())
	{
		plik << "\n";
		for (int i = 0; i < ilosc_graczy; i++)
		{
			plik << setw(3) << left << ile_graczy[i].daj_nick()  << "\t";
			ile_graczy[i].wypisz_reke(plik);
			plik << setw(3) << left <<" Punkty: " << ile_graczy[i].iloscPunktow() << endl;
		}
	}
	plik.close();
}
#include "Gracz.h"
using namespace std;

int get_safe_intiger2(int dol, int gora)
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

Gracz::Gracz() 
{
    punkty = 0;
    info_pas = 0;
    *karty_gracza = nullptr;
}

void Gracz::wezKarte(Karta* _karta)
{
	if (index_gracza < 10)
	{
		karty_gracza[index_gracza++] = _karta;
	}
	punkty = punkty + _karta->getWartosc();
}




void Gracz::pokazReke()
{
    for (int i = 0; i < index_gracza; i++)
    {
        karty_gracza[i]->wypisz();
        cout << "\t";
    }
    cout << endl;
}

bool Gracz::czy_pasuje()
{
    return info_pas;
}

int Gracz::iloscPunktow()
{
    return punkty;
}

void Gracz::wybor_gracza()
{
	if (info_pas == 0 && punkty < 21)
	{
		int wybor = 0;
		cout << "\n" << "Wybierz opcje:" << endl;
		cout << "1. Dobierz karte" << endl;
		cout << "2. Spasuj" << endl;

            wybor = get_safe_intiger2(0,3);

		do
		{
			switch (wybor)
			{
			case 1:
				this->info_pas = 0;
				break;
			case 2:
				this->info_pas = 1;
				break;
			default:
				cout << "Nie ma takiej opcji" << endl;
				break;
			}
		} while (wybor < 1 || wybor > 2);
	}
	else
	{
		cout << "Automatycznie zpasowano" << endl;
		cout << endl;
		this->info_pas = 1;
	}
}

void Gracz::znajdz_kasyno(Kasyno* wsk)
{
	kasyno = wsk;
}

void Gracz::wypisz_reke(ostream& plik)
{
	for (int i = 0; i < index_gracza; i++)
	{

		if (karty_gracza[i]->getKolor() == 3)
		{
			plik << "Kier  ";
		}
		else if (karty_gracza[i]->getKolor() == 4)
		{
			plik << "Karo  ";
		}
		else if (karty_gracza[i]->getKolor() == 5)
		{
			plik << "Trefl ";
		}
		else if (karty_gracza[i]->getKolor() == 6)
		{
			plik << "Pik   ";
		}
		plik << karty_gracza[i]->getFigura() << "  ";
	}
}

void Gracz::ustaw_nick()
{
	string test;
	cout << "Podaj nick jaki chcesz ustawic(max 20 znakow):";
	cin >> test;

	while (test.length() > 20)
	{
		cout << "Za dlugi nick, sproboj ponownie!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> test;
	}

	if (test.length() < 20)
	{
		nick = test;
	}
}

string Gracz::daj_nick()
{
	return nick;
}


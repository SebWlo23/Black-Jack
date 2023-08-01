#include <iostream>
#include "Kasyno.h"
#include "Gracz.h"

using namespace std;


int main()
{
	cout << "Witamy w Kasynie!" << endl;
	Kasyno casino;
	casino.Graj();
	system("pause");
	return 0;
}
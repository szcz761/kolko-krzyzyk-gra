
#include "computer_game.h"



int main()
{
	try
	{
		int rozmiar, warunek,poziom;
		cout << "Kolko i krzyzk" << endl;
		cout << "Podaj rozmiar tablicy:" << endl;
		cin >> rozmiar;
		//rozmiar = 5;
		cout << "Podaj warunek wygranej:" << endl;
		cin >> warunek;
		cout << "wybierz poziom komputera:" << endl;
		cin >> poziom;
		//warunek = 3;
		computer_game g(rozmiar, warunek,poziom);
		//game g(5, 5);


		//computer c(g);

		//g.stworz_drzewo();

		//g.gra_dwuosobowa();
		g.gra_jednoosobowa();
	}
	catch (string w)
	{
		cout << "Wyjatek: " << w << endl;
	}
	system("pause");
	return 0;
}


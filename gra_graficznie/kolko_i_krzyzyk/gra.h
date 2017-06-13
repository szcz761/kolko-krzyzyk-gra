#ifndef GAME_H
#define GAME_H
#include "drzewo.h"
using namespace std;


class game {
private:
    int size;
    char **tab;
    int warunek_wygranej;
    int ruchy;
    int stan_gry;
public:


    game(int s,int w)
    {
        stan_gry = 0;
        size = s;
        warunek_wygranej = w;
        ruchy = 0;
        if (s <= 0)											//rozmiar jako liczba ujemna
        {
            cout << "rozmiar zamaly do gry! ustawiam 3" << endl;
            size=3;
        }
        if (w > s)										//warunek wygranej wiekszy niz rozmiar - nie da sie wygrac
        {
            cout << "warunek wygranej wiekszy niz rozmiar nie da sie wygrac! zamieniam warunek na rozmiar tablicy" << endl;
            warunek_wygranej = size;
        }
        tab = new char *[size];						//alokacja pamieci dla kazdej kolumny
        for (int i = 0; i<size; i++)
        {
            tab[i] = new char[size];				//alokacja pamieci dla kazdego wiersza
            for (int j = 0; j<size; j++)			//uzupelnianie tablicy znakami pustymi czyli w moim przypadku "*"
            {
                tab[i][j] = '*';
            }
        }
    }

    game(game* g)
    {
        size = g->size;
        warunek_wygranej = g->warunek_wygranej;
        ruchy = g->ruchy;
        stan_gry = g->stan_gry;
        tab = new char *[size];						//alokacja pamieci dla kazdej kolumny
        for (int i = 0; i<size; i++)
        {
            tab[i] = new char[size];				//alokacja pamieci dla kazdego wiersza
            for (int j = 0; j<size; j++)			//uzupelnianie tablicy znakami pustymi czyli w moim przypadku "*"
            {
                tab[i][j] = g->tab[i][j];
            }
        }
    }

    ~game()
    {
        for (int i = 0;i<size;i++)
            delete[] tab[i];
        delete[] tab;
    }

    void zamien(game* g)
    {
        size = g->size;
        warunek_wygranej = g->warunek_wygranej;
        ruchy = g->ruchy;
        stan_gry = g->stan_gry;
        char **tmp = tab;
        tab = new char *[size];						//alokacja pamieci dla kazdej kolumny
        for (int i = 0; i<size; i++)
        {
            tab[i] = new char[size];				//alokacja pamieci dla kazdego wiersza
            for (int j = 0; j<size; j++)			//przepisanie tablicy
            {
                tab[i][j] = g->tab[i][j];
            }
        }
        for (int i = 0;i<size;i++)
            delete[] tmp[i];
        delete[] tmp;
    }

    int get_stan_gry()
    {
        return stan_gry;
    }

    char** get_tab()
    {
        return tab;
    }

    int get_ruchy()
    {
        return ruchy;
    }

    void set_ruchy(int i)
    {
         ruchy=i;
    }

    int get_warunek_wygranej()
    {
        return warunek_wygranej;
    }

    int get_size()
    {
        return size;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout<<" "<<tab[i][j]<<" ";
            }
            cout << endl;
        }
    }

    void ruchX()
    {
        int i, j;
        cout << "Ruch X" << endl;
        cout << "Podaj wspolrzedne X:";
        cin >> j;
        cout << "Podaj wspolrzedne Y:";
        cin >> i;
        if (i >= size || j >= size) //w razie wyjscia po za zakres tablicy
        {
            cout << "zle parametry! podaj inne!" << endl;
            ruchX();
            return;
        }
        if (tab[i][j] == '*')
        {
            tab[i][j] = 'X';
            ruchy++;
        }
        else
        {
            cout << "na tym polu juz kots cos postawil! podaj inne wspolzedne!" << endl;
            ruchX();
            return;
        }
    }

    void ruchO()
    {
        int i, j;
        cout << "Ruch O" << endl;
        cout << "Podaj wspolrzedne X:";
        cin >> j;
        cout << "Podaj wspolrzedne Y:";
        cin >> i;
        if (i >= size || j >= size) //w razie wyjscia po za zakres tablicy
        {
            cout << "zle parametry! podaj inne!" << endl;
            ruchO();
            return;
        }
        if (tab[i][j] == '*')                  //gdy nic nie bylo postawione ok
        {
            tab[i][j] = 'O';
            ruchy++;						//inkrementujemy ruchy
        }
        else                              //gdy pole juz zajete
        {
            cout << "na tym polu juz kots cos postawil! podaj inne wspolzedne!" << endl;
            ruchO();
            return;
        }
    }

    int ruchX(int i, int j)
    {
        if (i >= size || j >= size) //w razie wyjscia po za zakres tablicy
            return -1;
        if (tab[i][j] == '*')
        {
            tab[i][j] = 'X';
            ruchy++;
            //wsp_gry();
            return 0;
        }
        else
            return -2;
    }

    int ruchO(int i, int j)
    {
        if (i >= size || j >= size) //w razie wyjscia po za zakres tablicy
            return -1;
        if (tab[i][j] == '*')
        {
            tab[i][j] = 'O';
            ruchy++;
        //	wsp_gry();
            return 0;
        }
        else
            return -2;
    }

    bool czywygrany()		//funkcja sprawdzajaca czy zawodnik wygral
    {
        for (int i = 0; i<size; i++)
        {
            for (int j = 0; j<size; j++)
            {
                if (tab[i][j] != '*')
                {
                    int licznik = 0;
                    if (j < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i][j + k] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa X(poziomo)" << endl;
                                return true;
                            }
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i][j + k] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa O(poziomo)" << endl;
                                return true;
                            }
                        }
                    }

                    if (i < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa X(pionowo)" << endl;
                                return true;
                            }
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa O(pionowo)" << endl;
                                return true;
                            }
                        }
                    }

                    if (j < size - (warunek_wygranej - 1) && i < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j + k] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa X(prawy skos)" << endl;
                                return true;
                            }
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j + k] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa O(prawy skos)" << endl;
                                return true;
                            }
                        }
                    }

                    if (j > 1 && i < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j - k] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa X(lewy skos)" << endl;
                                return true;
                            }
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j - k] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                cout << "Wygrywa O(lewy skos)" << endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    int wsp_gry()		//funkcja przypisujaca wspolczynnik gry
    {
        int licznikX = 0;
        int licznikO = 0;
        int licznik = 0;
        for (int i = 0; i<size; i++)
        {
            for (int j = 0; j<size; j++)
            {
                if (tab[i][j] != '*')
                {
                    if (j < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;

                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i][j + k] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = -2;
                                return -2;
                            }
                            if (licznik > licznikX)
                                licznikX = licznik;
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i][j + k] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = 2;
                                return 2;
                            }
                            if (licznik > licznikO)
                                licznikO = licznik;
                        }
                    }

                    if (i < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = -2;
                                return -2;
                            }
                            if (licznik > licznikX)
                                licznikX = licznik;
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = 2;
                                return 2;
                            }
                            if (licznik > licznikO)
                                licznikO = licznik;
                        }
                    }

                    if (j < size - (warunek_wygranej - 1) && i < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j + k] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = -2;
                                return -2;
                            }
                            if (licznik > licznikX)
                                licznikX = licznik;
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j + k] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = 2;
                                return 2;
                            }
                            if (licznik > licznikO)
                                licznikO = licznik;
                        }
                    }

                    if (j > 1 && i < size - (warunek_wygranej - 1))
                    {
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j - k] == 'X')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = -2;
                                return -2;
                            }
                            if (licznik > licznikX)
                                licznikX = licznik;
                        }
                        licznik = 0;
                        for (int k = 0; k < warunek_wygranej; k++)
                        {
                            if (tab[i + k][j - k] == 'O')
                            {
                                licznik++;
                            }
                            if (licznik == warunek_wygranej)
                            {
                                stan_gry = 2;
                                return 2;
                            }
                            if (licznik > licznikO)
                                licznikO = licznik;
                        }
                    }
                }
            }
        }
        if (licznikX > licznikO)
        {
            stan_gry = -1;
            return -1;
        }
        else if (licznikX == licznikO)
        {
            stan_gry = 0;
            return 0;
        }
        else
        {
            stan_gry = 1;
            return 1;
        }
    }

    bool czyremis()
    {
        if (ruchy == size*size)
        {
            return true;
            cout << "remis!!!"<< endl;
        }
        return false;
    }

    void gra_dwuosobowa()
    {
        while (!(czywygrany()||czyremis()))
        {
            system("cls");
            print();
            ruchX();
            if (!(czywygrany()||czyremis()))
            {
                system("cls");
                print();
                ruchO();
            }
        }
        system("cls");
        if(!czywygrany())
            czyremis();
        print();
    }




};
#endif

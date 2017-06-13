#pragma once
#ifndef COMPUTER_GAME_H
#define COMPUTER_GAME_H
#include "gra.h"
using namespace std;


class computer_game: private game{
private:
    drzewo<game*> decyzje;
    int poziom;
public:
    computer_game(int s, int w,int p):game(s,w),poziom(p)
    {}

    computer_game(int s, int w) :game(s, w)
    {
        if (w % 2 == 0)
            poziom = w - 1;
        else
            poziom = w;
    }

    void del_wezel(wezel<game*>* ojciec)											// usuwa wszystkie gry z drzewa
    {
        if (ojciec->get_sons_count() == 0)
            delete ojciec->get_element();
        else
        {
            for(int i = 0; i < ojciec->get_sons_count();i++)
                del_wezel(ojciec->get_next(i));
            delete ojciec->get_element();
        }
    }

    void rusz_sie()
    {
        if (get_ruchy() == 0)															//pierwszy rych na srodek planszy
        {
            ruchO(get_size() / 2, get_size() / 2);
            return;
        }
        for(int i=0;i<decyzje.get_head()->get_sons_count();i++)							//usuniecie wszystkich gier z drzewa decyecyzji
            del_wezel(decyzje.get_head()->get_next(i));
        while(decyzje.get_head()->get_sons_count()!=0)									//usuniecie calego drzewa
            decyzje.remove_son(0, decyzje.get_head());
        decyzje.get_head()->set_element(this);											//ustawienie heda na ta aktualnaa gre

        for (int i = 0; i < get_size();i++) {											//w razie gdyby komputer mial w tym ruchu wygrac -wygraj
            for (int j = 0; j < get_size();j++){
                game* kolejny_ruch = new game(this);
                if (kolejny_ruch->ruchO(i, j) == 0)
                {
                    if (kolejny_ruch->wsp_gry() == 2)
                    {
                        zamien(kolejny_ruch);
                        return;
                    }
                }
                else
                    delete kolejny_ruch;
            }
        }
        int ktory_ruch = stworz_drzewo(decyzje.get_head(), poziom);					//przeszukaj rozwiazania i wybierz najlepsze
        zamien(decyzje.get_head()->get_next(ktory_ruch)->get_element());			//zamien stan aktalnej gry z wybranym rozwiazaniem gdzie O ruszylo sie jeden raz.
    }


    int stworz_drzewo(wezel<game*>* tmp,int poziom)			//tworzy drzewo decyzji siekajace rucha do przodu o wartooscii poziom
    {
        if (poziom == 0)
            return tmp->get_element()->wsp_gry();									//jzeli poziom osoagnal maksymalna glebokosc zwroc stan gry
        game* kolejny_ruch;
        for (int i = 0; i < get_size();i++)											//sproboj strzelic w kazde miejsce na planszy
        {
            for (int j = 0; j < get_size();j++)
            {
                kolejny_ruch = new game(tmp->get_element());								//tworzy nowa gre
                if (poziom % 2 == 0)												//jesli parzyste - my jedziemy
                {
                    if (kolejny_ruch->ruchX(i, j) == 0)										//jeslij pole nie jest zajete
                        decyzje.add_son(kolejny_ruch, tmp);					//dodaj gre z tym ruchem do drzewa decyzji
                    else
                        delete kolejny_ruch;												//jeslij pole zajete usun gre z ta decyzja
                }
                else
                {
                    if (kolejny_ruch->ruchO(i, j) == 0)										//jesli nie parzyste -komp jedze i robi to samo co my wyrzej
                        decyzje.add_son(kolejny_ruch, tmp);
                    else
                        delete kolejny_ruch;
                }
            }
        }
        int *tab_wynik = new int [tmp->get_sons_count()];							//tworzymy tablice z wspolczynnikami wygranej odpowiadjace roznym drogom z tej sytuacji
        int licz1=0, licz_1=0, licz0=0,x=0,o=0;												//iteraory ile dobryh drog ile zlych
        for (int i = 0;i < tmp->get_sons_count();i++)
            tab_wynik[i]=stworz_drzewo(tmp->get_next(i), poziom - 1);				//dla kazdego rozwiazania sprawdzamy rekurencyjnie kolejne kroki az do poziomu 0
       // int waga=0;
        for (int i = 0;i < tmp->get_sons_count();i++)								//zwiekszamy ilosc poszczegolnych rozwiazan
        {
           // waga=waga+tab_wynik[i];
            if (tab_wynik[i] == 2)
                licz1++;
            else if (tab_wynik[i] == 1)
                licz1++;
            else if (tab_wynik[i] == 0)
                licz0++;
            else if (tab_wynik[i] == -1)
                licz_1++;
            else
                licz_1++;
        }
        if (tmp->get_element() == this)												//jesli jestesmy na najwyzszym poziomie
        {
            int max=-5, j=0;
            for (int i = 0;i < tmp->get_sons_count();i++)
                if (tab_wynik[i] > max)
                {
                    max = tab_wynik[i];												//zwracamy najlepszą droge
                    j = i;
                }
            return j;

        }
        delete[] tab_wynik;
        //return waga;
        if(poziom % 2 == 0)													//X chce wygrac wiec jedzie najlepiej (-1)
        {

            if (x > 0)
                return -1;
            else if (licz_1 > 0)
                return -1;
            else if (licz0 > 0)
                return 0;
            else if (licz1 > 0)
                return 1;
            else
                return 1;

        }
        else																//O chce wygrac wiec chce zwrucic 1 jak moze
        {
            if (o > 0)
                return 1;
             if (licz1 > 0)
                return 1;
            else if (licz0 > 0)
                return 0;
            else if (licz_1 > 0)
                return -1;
            else
                return -1;
        }


    }

    void gra_jednoosobowa()												//gra
    {
        while (!(czywygrany() || czyremis()))							//dopuki nie wygrana
        {
            system("cls");
            print();
            rusz_sie();													//wyswietl plansze i wykonaj ruch komputera O
            if (!(czywygrany() || czyremis()))							//jesli nie wygrana jeszcze to wyswietl plansze i wykonaj ruch X
            {
                system("cls");
                print();
                ruchX();
            }
        }
        system("cls");
        if (!czywygrany())												// jesli ktos juz wygrał albo remis wyswietl kominikat i plansze
        {
            cout << "REMIS" << endl;
            czyremis();
        }
            print();
    }

};
#endif;

#pragma once

#ifndef _WEZEL_
#define _WEZEL_

#include <string>

template<typename E>
class wezel
{
private:
    E element;
    wezel<E>** next;
    wezel<E>* back;
    int sons;
public:
    wezel()
    {
        next = NULL;
        back = NULL;
        sons = 0;
    }

    E get_element()
    {
        return element;
    }

    void set_element(E elem)
    {
        element = elem;
    }

    wezel<E>* get_next(int i)
    {
        if (i > sons)
        {
            std::string wyjatek = "wezel get_next(i) zly index nie mozna zwrocic";
            throw wyjatek;
        }
        else if (sons == 0)
            return NULL;
        else
            return next[i];
    }

    void set_next_add(wezel<E>* nastepny)            //zapewnia powieksza tablice synow i wstawia nowego syna
    {
        wezel<E>** tmp = next;
        next = new wezel<E>*[sons + 1];
        for (int i = 0;i < sons;i++)
            next[i] = tmp[i];
        next[sons] = nastepny;
        delete tmp;
        sons++;
    }

    void set_next_del(int j)                   //zmniejsza tablice synow
    {
        wezel<E>** tmp = next;
        next = new wezel<E>*[sons - 1];

        for (int i = 0;i < sons - 1;i++)
        {
            if (i >= j)
                next[i] = tmp[i + 1];
            else
                next[i] = tmp[i];
        }
        delete tmp;
        sons--;
    }

    wezel<E>* get_back()
    {
        return back;
    }

    void set_back(wezel<E>* poprzedni)
    {
        back = poprzedni;
    }

    int get_sons_count()
    {
        return sons;
    }

    void set_sons_count(int i)
    {
        sons = i;
    }
};
#endif

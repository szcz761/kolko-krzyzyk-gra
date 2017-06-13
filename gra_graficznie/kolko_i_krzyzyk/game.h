#ifndef GAME_H
#define GAME_H
#include"drzewo.h"
using namespace std;

//template<typename E>
class game{
private:
    int size;
    char **tab;
public:
    game(int size=3)
    {
       tab=new char*[size];

        for(int i=0;i<size;i++)
            tab[i]=new char [size];

        for(int i=0;i<size;i++)
            for(int j=0;i<size;i++)
                tab[i][j]='*';
    }

    ~game()
    {
        for(int i=0;i<size;i++)
            delete[] tab[i];
        delete[] tab;
    }

    void print()
    {
        for(int i=0;i<size;i++)
        {
            for(int j=0;i<size;i++)
                cout<<tab[i][j]<<" ";
            cout<<endl;
        }
    }





};
#endif // GAME_H

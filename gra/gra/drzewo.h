
#ifndef _DRZEWO_
#define _DRZEWO_

#include "wezel.h"
#include <iostream>


using namespace std;

template<typename E>
class drzewo
{
private:
	wezel<E>* head;
	int s;
public:
	drzewo()
	{
		head = new wezel<E>;
		s = 1;
	}

	~drzewo()
	{
		remove_this(head);
	}

	bool empty()
	{
		if (head->get_sons_count() == 0)
			return true;
		else
			return false;
	}

	wezel<E>* get_head()
	{
		return head;
	}

	wezel<E>* add_son(const E dana, wezel<E>* ojciec)
	{
		ojciec->set_next_add(new wezel <E>);
		ojciec->get_next(ojciec->get_sons_count() - 1)->set_element(dana);
		ojciec->get_next(ojciec->get_sons_count() - 1)->set_back(ojciec);
		s++;
		return ojciec->get_next(ojciec->get_sons_count() - 1);
	}

	void remove_this(wezel<E>* ojciec)
	{
		if (ojciec->get_sons_count() == 0)
		{
			delete ojciec;
			s--;
		}
		else
		{
			while (ojciec->get_sons_count() != 0)
			{
				remove_this(ojciec->get_next(0));
				ojciec->set_next_del(0);
			}
			delete ojciec;
			s--;
		}
	}

	E remove_son(int i, wezel<E>* ojciec)
	{
		if (i >= ojciec->get_sons_count())
		{
			string wyjatek = "drzewo remove_son(i) zly index nie mozna usunac ";
			throw wyjatek;
		}
		else
		{
			E tmp = ojciec->get_next(i)->get_element();
			remove_this(ojciec->get_next(i));
			ojciec->set_next_del(i);
			return tmp;
		}
	}

	E get_son(int i, wezel<E>* ojciec)
	{
		if (i >= ojciec->get_sons_count())
		{
			string wyjatek = "drzewo remove_son(i) zly index nie mozna usunac ";
			throw wyjatek;
		}
		else
			return ojciec->get_next(i)->get_element();
	}


	int size()
	{
		return s;
	}
	//=====================================================PRINT========================================
	void print_post(wezel<E>* ojciec)
	{
		if (ojciec->get_sons_count() == 0)
			cout << ojciec->get_element() << endl;
		else
		{
			for (int i = 0; i < ojciec->get_sons_count();i++)
			{
				print_post(ojciec->get_next(i));
			}
			cout << ojciec->get_element() << endl;
		}
	}

	void print_post()
	{
		wezel<E>* ojciec = get_head();
		if (ojciec->get_sons_count() == 0)
			cout << ojciec->get_element() << endl;
		else
		{
			for (int i = 0; i < ojciec->get_sons_count();i++)
			{
				print_post(ojciec->get_next(i));
			}
			cout << ojciec->get_element() << endl;
		}
	}

	void print_pre(wezel<E>* ojciec)
	{
		if (ojciec->get_sons_count() == 0)
			cout << ojciec->get_element() << endl;
		else
		{
			cout << ojciec->get_element() << endl;
			for (int i = 0; i < ojciec->get_sons_count();i++)
			{
				print_pre(ojciec->get_next(i));
			}
		}
	}

	void print_pre()
	{
		wezel<E>* ojciec = get_head();
		if (ojciec->get_sons_count() == 0)
			cout << ojciec->get_element() << endl;
		else
		{
			cout << ojciec->get_element() << endl;
			for (int i = 0; i < ojciec->get_sons_count();i++)
			{
				print_pre(ojciec->get_next(i));
			}
		}
	}

	int height(wezel<E> *ojciec)
	{

		if (ojciec->get_sons_count() == 0)
			return 0;
		else
		{
			int h = 0;
			for (int i = 0;i < ojciec->get_sons_count();i++)
			{
				int k = height(ojciec->get_next(i));
				if (h < k)
					h = k;
			}
			return h + 1;
		}
	}

};


#endif

#pragma once
#include <iostream>
#include <string>

using namespace std;


template <class T>
struct TLink
{
	T val;
	TLink* pNext;
};

template <class T>
class TList
{
public:
	TLink<T>* pFirst, * pLast, * pCurr, * pPrev, * pStop;
	int size, pos;
public:
	void InsLast(T elem);
	void InsFirst(T elem);
	void InsCurr(T elem);
	TList(const TList<T>& lst);
	void DelCurr();
	void DelFirst();
	friend std::istream& operator >> (std::istream& in, TList<T> lst);
	friend std::ostream& operator << (std::ostream& out, const TList<T> lst);
	TList()
	{
		size = 0;
		pos = 0;
		pStop = NULL;
		pFirst = pStop;
		pLast = pStop;
		pCurr = pStop;
		pPrev = pStop;
	}
	~TList()
	{
		pCurr = pPrev = pStop;
		size = 0;
		pos = 0;
		while (pFirst != pStop);
		{
			TLink<T>* tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
		}
	}
	void Reset()
	{
		pCurr = pFirst;
	}
	bool IsEnd() const
	{
		return pCurr == pStop;
	}
	void GoNext()
	{
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
	int Get_Size()const
	{
		return size;
	}
	friend std::ostream& operator <<(std::ostream& out, const TList<T> lst)
	{
		TLink<T>* temp = lst.pFirst;
		while (temp != lst.pStop)
		{
			out << temp->val << ' ';
			temp = temp->pNext;
		}
		return out;
	}
	friend std::istream& operator >> (std::istream& in, TList<T> lst)
	{
		std::cout << "Size=";
		int temp;
		in >> temp;
		if (temp < 0)
			throw 0;
		for (int i = 0; i < temp; i++)
		{
			T t;
			in >> t;
			lst.InsLast(t);
		}
		return in;
	}
};
	template <class T>
	TList<T>::TList(const TList<T>& lst)
	{
		if (lst.size == 0)
		{
			pStop = lst.pStop;
			pFirst = pLast = pCurr = pPrev = pStop;
			size = 0;
			pos = 0;
		}
		else
		{
			pStop = lst.pStop;
			pCurr = pPrev = pStop;
			pos = 0;
			TLink<T>* prev = new TLink<T>;
			prev->val = lst.pFirst->val;
			prev->pNext = pStop;
			pFirst = prev;
			TLink<T>* curr = lst.pFirst;
			while (curr->pNext != pStop)
			{
				curr = curr->pNext;
				TLink<T>* link = new TLink<T>;
				link->val = curr->val;
				link->pNext = pStop;
				prev->pNext = link;
				prev = link;
			}
			size = lst.size;
			pLast = prev;
		}
	}
	template<class T>
	void TList<T>::InsFirst(T elem)
	{
		TLink<T>* temp = new TLink<T>;
		temp->val = elem;
		if (size == 0)
		{
			temp->pNext = pStop;
			pFirst = pLast = temp;
		}
		else
		{
			temp->pNext = pFirst;
			pFirst = temp;
		}
		size++;
	}
	template<class T>
	void TList<T>::InsLast(T elem)
	{
		TLink<T>* temp = new TLink<T>;
		temp->val = elem;
		temp->pNext = pStop;
		if (size == 0)
		{
			pFirst = pLast = temp;
		}
		else
		{
			pLast->pNext = temp;
			pLast = temp;
		}
		size++;
	}
	template<class T>
	void TList<T>::DelFirst()
	{
		if (size == 0)
			throw 0;
		else
		{
			TLink<T>* temp = pFirst->pNext;
			delete pFirst;
			pFirst = temp;
			size--;
		}
	}
	template <class T>
	void TList<T>::DelCurr()
	{
		if (size == 0 || pCurr == pStop)
			throw 0;
		if (pCurr == pFirst)
		{
			DelFirst();
			pCurr = pFirst;
		}
		else
		{
			pPrev->pNext = pCurr->pNext;
			delete pCurr;
			pCurr = pPrev->pNext;
			size--;
		}
	}
	template<class T>
	void TList<T>::InsCurr(T elem)
	{
		if (size == 0)
		{
			InsLast(elem);
			pPrev = pLast;
			pCurr = pPrev->pNext;
		}
		else
		{
			if (pCurr == pFirst)
			{
				InsFirst(elem);
				pPrev = pFirst;
				pCurr = pPrev->pNext;
			}
			else
			{
				TLink<T>* temp = new TLink<T>;
				pPrev->pNext = temp;
				temp->val = elem;
				temp->pNext = pCurr;
				pPrev = temp;
				size++;
			}
		}
	}


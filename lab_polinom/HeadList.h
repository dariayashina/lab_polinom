#pragma once
#include "List.h"
template<class T>
class THeadList : public TList<T> {
protected:
	TLink<T>* pHead;
public:
	THeadList();
	THeadList(const THeadList& h);
	~THeadList();
	void InsFirst(T elem);
	void InsLast(T elem);
	void InsCurr(T elem);
	void DelCurr();
	void DelFirst();
};
template<class T>
THeadList<T>::THeadList() :TList<T>()
{
	pHead = new TLink<T>;
	TList<T>::pStop = pHead;
	pHead->pNext = TList<T>::pStop;
	TList<T>::pFirst = TList<T>::pLast = TList<T>::pCurr = TList<T>::pPrev = TList<T>::pStop;
}
template<class T>
THeadList<T>::THeadList(const THeadList<T>& h)
{
	pHead = new TLink<T>;
	TList<T>::pStop = TList<T>::pFirst = TList<T>::pLast = TList<T>::pPrev = TList<T>::pCurr = pHead;
	pHead->pNext = TList<T>::pStop;
	if (h.size)
	{
		TLink<T>* prev = new TLink<T>;
		pHead->pNext = prev;
		TList<T>::pFirst = prev;
		TList<T>::pFirst->val = h.pFirst->val;
		TList<T>::pFirst->pNext = TList<T>::pStop;
		TLink<T>* curr = h.pFirst->pNext;
		while (curr != h.pStop)
		{
			TLink<T>* temp = new TLink<T>;
			temp->val = curr->val;
			temp->pNext = TList<T>::pStop;
			prev->pNext = temp;
			prev = temp;
			curr = curr->pNext;
		}
		TList<T>::pLast = prev;
	}
	TList<T>::size = h.size;
	TList<T>::pos = 0;
}
template<class T>
THeadList<T>::~THeadList()
{
	TList<T>::~TList();
	delete pHead;
}
template<class T>
void THeadList<T>::InsFirst(T elem)
{
	TList<T>::InsFirst(elem);
	pHead->pNext = TList<T>::pFirst;
}
template<class T>
void THeadList<T>::InsLast(T elem)
{
	TList<T>::InsLast(elem);
	pHead->pNext = TList<T>::pFirst;
}
template<class T>
void THeadList<T>::InsCurr(T elem)
{
	TList<T>::InsCurr(elem);
	pHead->pNext = TList<T>::pFirst;
}
template <class T>
void THeadList<T>::DelFirst()
{
	TList<T>::DelFirst();
	pHead->pNext = TList<T>::pFirst;
}
template <class T>
void THeadList<T>::DelCurr()
{
	TList<T>::DelCurr();
	pHead->pNext = TList<T>::pFirst;
}
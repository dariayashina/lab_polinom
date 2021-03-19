#pragma once
#include"List.h"
#include"HeadList.h"
#include"Monom.h"

using namespace std;
class TPolinom:public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(const TPolinom& p);
	void InsMonom(const TMonom& m);
	TPolinom& operator=(const TPolinom& p);
	TPolinom& operator += (const TPolinom& p);
	TPolinom operator + (const TPolinom& p);
	TPolinom operator * (const double val);
	TPolinom operator * (const TMonom& m);
	friend std::istream& operator >> (std::istream& in, TPolinom& p)
	{
		std::cout << "Size=";
		int temp;
		in >> temp;
		if (temp < 0)
			throw 0;
		for (int i = 0; i < temp; i++)
		{
			TMonom m;
			in >> m;
			p.InsMonom(m);
		}
		return in;
	}
	friend ostream& operator << (ostream& out, TPolinom& p)
	{
		for (p.Reset(); !p.IsEnd(); p.GoNext())
		{
			out << p.pCurr->val << ' ';
		}
		if (!p.size)
			out << "Polinom empty";
		return out;
	}
};

TPolinom::TPolinom() :THeadList<TMonom>()
{
	TMonom temp;
	temp.z = -1;
	temp.coeff = 0.0;
	pHead->val = temp;
}

TPolinom::TPolinom(const TPolinom& p) : THeadList<TMonom>(p)
{
	pHead->val = p.pHead->val;
}

void TPolinom::InsMonom(const TMonom& m)
{
	Reset();
	while (true)
	{
		if (pCurr->val < m)
		{
			InsCurr(m);
			break;
		}
		if (pCurr->val == m)
		{
			if (pCurr->val.coeff + m.coeff != 0)
				pCurr->val.coeff += m.coeff;
			else
				DelCurr();
			break;
		}
		GoNext();
	}
}

TPolinom& TPolinom::operator+=(const TPolinom& p)
{
	Reset();
	TLink<TMonom>* curr = p.pFirst;
	while (curr != p.pStop)
	{
		if (pCurr->val < curr->val)
		{
			InsCurr(curr->val);
			curr = curr->pNext;
		}
		else
		{
			if (pCurr->val == curr->val)
			{
				double tmp = pCurr->val.coeff + curr->val.coeff;
				pCurr->val.coeff = tmp;
				if (tmp)
					GoNext();
				else
					DelCurr();
				curr = curr->pNext;
			}
			else
				GoNext();
		}
	}
	return *this;
}

TPolinom TPolinom::operator+(const TPolinom& p)
{
	TPolinom res(*this);
	res.Reset();
	TLink<TMonom>* curr = p.pFirst;
	while (curr != p.pStop)
	{
		if (res.pCurr->val < curr->val)
		{
			res.InsCurr(curr->val);
			curr = curr->pNext;
		}
		else
		{
			if (res.pCurr->val == curr->val)
			{
				double tmp = res.pCurr->val.coeff + curr->val.coeff;
				if (tmp)
				{
					res.pCurr->val.coeff = tmp;
					res.GoNext();
				}
				else
					res.DelCurr();
				curr = curr->pNext;
			}
			else
			{
				res.GoNext();
			}
		}
	}
	return res;

}

TPolinom TPolinom:: operator*(const double val)
{
	if (val == 0.0)
	{
		TPolinom res;
		return res;
	}
	else
	{
		TPolinom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext())
			res.pCurr->val.coeff *= val;
		return res;
	}
}

TPolinom TPolinom::operator*(const TMonom& m)
{
	if (m.coeff == 0.0)
	{
		TPolinom res;
		return res;
	}
	else
	{
		TPolinom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext())
			res.pCurr->val = res.pCurr->val * m;
		return res;
	}
}

TPolinom& TPolinom::operator=(const TPolinom& p)
{
	if (this != &p)
	{
		if (!p.size)
		{
			TList<TMonom>::~TList();
		}
		else
		{
			if (size < p.size)
			{
				int tmp = p.size - size;
				TLink<TMonom>* curr = pLast;
				for (int i = 0; i < tmp; i++)
				{
					TLink<TMonom>* new_elem = new TLink<TMonom>;
					curr->pNext = new_elem;
					curr = new_elem;
					curr->pNext = pStop;
				}
				pFirst = pHead->pNext;
				pLast = curr;
				curr = p.pFirst;
				for (Reset(); !IsEnd(); GoNext())
				{
					pCurr->val = curr->val;
					curr = curr->pNext;
				}
			}
			else
			{
				TLink<TMonom>* curr = p.pFirst;
				Reset();
				while (true)
				{
					pCurr->val = curr->val;
					curr = curr->pNext;
					if (curr == p.pStop)
						break;
					GoNext();
				}
				pLast = pCurr;
				GoNext();
				while (!IsEnd())
				{
					TLink<TMonom>* t = pCurr;
					GoNext();
					delete t;
				}
				pLast->pNext = pStop;
				pPrev = pLast;
			}
		}
	}
	size = p.size;
	pos = 0;
	return *this;
}
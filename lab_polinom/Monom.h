#pragma once
#include <iostream>
#include <string>

using namespace std;

struct TMonom
{
    double coeff;
    int x, y, z;
	TMonom(int x_ = 0, int y_ = 0, int z_ = 0, double coeff_ = 1.0);
	bool operator < (const TMonom& m) const;
	bool operator == (const TMonom& m) const;
	bool operator >(const TMonom& m) const;
	TMonom& operator =(const TMonom& m);
	TMonom operator *(const TMonom& m);
	TMonom operator *(const double alpha);
	std::string print(char p, int pow) const;
	void input(char p, int val);
	friend std::istream& operator >> (std::istream& in, TMonom& m)
	{
		std::string res;
		in >> res;
		bool flag = false;
		for (unsigned int i = 0; i < res.size(); i++)
		{
			if (res[i] == 'x' || res[i] == 'y' || res[i] == 'z')
			{
				flag = true;
			}
			if (flag)
			{
				if (i + 1 < res.size())
				{
					if (res[i + 1] == '^')
					{
						m.input(res[i], res[i + 2] - '0');
						i += 2;
					}
					else
						m.input(res[i], 1);
				}
				else
					m.input(res[i], 1);

			}
			else
				if (i == 0)
				{
					std::string tmp;
					unsigned int j;
					for (j = 0; j < res.size(); j++)
					{
						if (res[j] == 'x' || res[j] == 'y' || res[j] == 'z')
							break;
						tmp += res[j];
					}
					i = j - 1;
					if (tmp == "-")
						m.coeff = -1;
					else
						m.coeff = std::stod(tmp);
				}
		}
		return in;
	}
	friend std::ostream& operator << (std::ostream& out, const TMonom& m)
	{
			if (m.x + m.y + m.z)
			{
				if (m.coeff != 1.0)
				{
					if (m.coeff != -1.0)
						out << m.coeff;
					else
						out << '-';
				}
				if (m.coeff != 1.0 && m.coeff != -1.0 && m.x)
					out << '*';
				out << m.print('x', m.x);
				if (m.x && m.y)
					out << '*';
				out << m.print('y', m.y);
				if (m.x && m.y && m.z)
					out << '*';
				out << m.print('z', m.z);
			}
			else
				out << m.coeff;
			return out;
		}
		
};
TMonom::TMonom(int x_, int y_, int z_, double coeff_)
{
	x = x_;
	y = y_;
	z = z_;
	coeff = coeff_;
}
bool TMonom::operator <(const TMonom& m) const
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return sum < sum_m;
}
bool TMonom::operator >(const TMonom& m) const
{
	int sum = x + y + z;
	int sum_m = m.x + m.y + m.z;
	return sum > sum_m;
}
bool TMonom::operator == (const TMonom& m) const
{
	return x == m.x && y == m.y && z == m.z;
}
TMonom& TMonom::operator =(const TMonom& m)
{
	coeff = m.coeff;
	x = m.x;
	y = m.y;
	z = m.z;
	return *this;
}
TMonom TMonom:: operator *(const TMonom& m)
{
	TMonom res;
	res.x = x + m.x;
	res.y = y + m.y;
	res.z = z + m.z;;
	res.coeff = coeff * m.coeff;
	return res;
}
TMonom TMonom:: operator *(const double alpha)
{
	TMonom res(this->x, this->y, this->z, this->coeff);
	res.coeff *= alpha;
	return res;
}
void TMonom::input(char p, int val)
{
	switch (p)
	{
	case 'x':x = val;
		break;
	case'y':y = val;
		break;
	case'z':z = val;
		break;
	}
}
std::string TMonom::print(char p, int pow) const
{
	std::string res = "";
	if (pow != 0)
	{
		if (pow > 1)
		{
			res += p;
			res += '^';
			res += std::to_string(pow);
		}
		else
		{
			res += p;
		}
	}
	return res;
}
//Andrew Lin 5/8/2017
#include "poly0.h" 
#include <cassert>
#include <cmath>
#include <climits>
using namespace std;
namespace main_savitch_3 
{
	const unsigned int polynomial::CAPACITY;
	const unsigned int polynomial::MAX_EX;
	polynomial::polynomial(double c, unsigned int exponent)
	{
		assert(exponent <= MAX_EX);
		for (int i = 0; i < CAPACITY; i++)
			coef[i] = 0;
		coef[exponent] = c;
		if(c == 0)
			current_degree = 0;
		else
			current_degree = exponent;
	}
	void polynomial::add_to_coef(double amount, unsigned int exponent)
	{
		assert(exponent <= MAX_EX);
		coef[exponent] += amount;
		for(int i = 0; next_term(i) != 0; i = next_term(i))
			current_degree = next_term(i);

	}
	void polynomial::assign_coef(double coefficient, unsigned int exponent)
	{
		assert(exponent <= MAX_EX);
		coef[exponent] = coefficient;
		for(int i = 0; next_term(i) != 0; i = next_term(i))
			current_degree = next_term(i);
	}
	void polynomial::clear( )
	{
		for(int i = 0; i < CAPACITY; i++)
			coef[i] = 0;
		current_degree = 0;

	}
	double polynomial::coefficient(unsigned int exponent) const
	{
		if(exponent > MAX_EX)
			return 0;
		else
			return coef[exponent];
	}
	// unsigned int polynomial::degree( ) const
	// {
	// 	unsigned int temp = 0;
	// 	double max = 0;
	// 	for(int i = 0; i < CAPACITY; i++)
	// 	{
	// 		if(coef[i] > max)
	// 		{
	// 			max = coef[i];
	// 			temp = i;
	// 		}

	// 	}
	// 	return temp;
	// }
	polynomial polynomial::derivative( ) const
	{
		polynomial temp;
		for(int i = 1; i < CAPACITY; i++)
			temp.assign_coef(i*coefficient(i), i-1);
		
		return temp;

	}
	double polynomial::eval(double x) const
	{
		double sum = 0;
		for(int i = 0; i < CAPACITY; i++)
		sum += coef[i] * pow(x, i);
		return sum;
	}
	unsigned int polynomial::next_term(unsigned int e) const
	{
		unsigned int n = 0;
		for(int i = e + 1; i < CAPACITY; i++)
		{
		 	if(coefficient(i) != 0)
		 	{
		 		n = i;
		 		break;
		 	}
		}
		return n;
	}
	unsigned int polynomial::previous_term(unsigned int e) const
	{
		unsigned int n = UINT_MAX;
		for(int i = 0; i < e; i++)
			if(coefficient(i) != 0)
				n = i;
			
		
		return n;
	}
	// double polynomial::operator( ) (double x) const
	// {
	// 	return eval(x);
	// }
	polynomial operator -(const polynomial& p1, const polynomial& p2)
	{
		polynomial temp;
		for (int i = 0; i < polynomial::CAPACITY; i++)
			temp.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
		return temp;
	}
	polynomial operator +(const polynomial& p1, const polynomial& p2)
	{
		polynomial temp;
		for (int i = 0; i < polynomial::CAPACITY; i++)
			temp.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
		return temp;
	}
	polynomial operator *(const polynomial& p1, const polynomial& p2)
	{
		assert(p1.degree( ) + p2.degree( ) <= polynomial::MAX_EX);
		polynomial temp;
		for (int i = 0; i < polynomial::CAPACITY; i++)
			for (int j = 0; j < polynomial::CAPACITY; j++)
				if((i+j) <= polynomial::MAX_EX)
					temp.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
		return temp;
	}
	ostream& operator << (ostream& out, const polynomial& p)
	{
		int x = 0;
		for(int i = polynomial::MAX_EX ; i >= 0; i--)
		{
			if(p.coefficient(i) != 0)
			{
				if(x == 0)
				{
					if(i!=0)
					{
						if(p.coefficient(i) < 0)
						{
							out << "-";
						}
						out << fabs(p.coefficient(i)) << "x^" << i; 
					}
					if(i == 0){
						out << p.coefficient(i);
					}
					x = 1;
					continue;
				}
				if(x > 0)
				{
					if(p.coefficient(i) < 0 && i != 0 && i != 1)
						out << " - " << fabs(p.coefficient(i)) << "x^" << i;
					if(p.coefficient(i) > 0 && i != 0 && i != 1)
						out << " + " << fabs(p.coefficient(i)) << "x^" << i;
					if(p.coefficient(i) < 0 && i == 0)
						out << " - " << fabs(p.coefficient(i));
					if(p.coefficient(i) > 0 && i == 0)
						out << " + " << fabs(p.coefficient(i));
					if(p.coefficient(i) < 0 && i == 1)
						out << " - " << fabs(p.coefficient(i)) << "x";
					if(p.coefficient(i) > 0 && i == 1)
						out << " + " << fabs(p.coefficient(i)) << "x";
				}
			}
		}
		if(x == 0)
			out << endl;
		if(x > 0)
			out << endl;
	}	
}

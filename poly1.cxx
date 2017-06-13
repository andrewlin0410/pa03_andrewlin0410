//Andrew Lin 5/8/2017
#include <iostream>
#include <cassert>
#include <cmath>
#include <math.h>
#include <climits>
#include "poly1.h"
using namespace std;
namespace main_savitch_4
{
	//const size_t polynomial::DEFAULT_CAPACITY;
	void polynomial::find_root(double& answer,bool& success,unsigned int& iterations, double guess, unsigned int maximum_iterations, double epsilon) const{
	}
	polynomial::polynomial(double c, unsigned int exponent)
	{
		if(exponent >= 30)
		{
			coef = new double[exponent+1];
			size = exponent + 1;
		}
	
		if(exponent < 30)
		{
			coef = new double[30];
			size = 30;
		}
		for(int i = 0; i < size ; i++)
			coef[i] = 0;
		coef[exponent] = c;
		current_degree = 0;
		if(c != 0)
			current_degree = exponent;
	}
	
	
	polynomial& polynomial::operator =(const polynomial& source)
	{
		// unsigned int x;
		// if(this == &source)
		// 	return *this;
		
		
		//if(this->size >= source.size){
		delete [] coef;
			//this->coef = new double[this->size];
		coef = new double[source.size];
		size = source.size;
		current_degree = source.current_degree;
		for(int i = 0; i < source.size; i++)
			coef[i] = source.coef[i];
		//}
		
		// if(this->size < source.size){
		// 	delete [] this->coef;
		// 	this->coef= new double[source.size+1];
		// 	this->size= source.size;
		// 	for(int j=0; j<source.size; j++){
		// 		this->coef[j]=source.coef[j];
		// 	}
		// }
		// for(int i = 0; next_term(i)!=0; i = next_term(i))
		// 	current_degree = next_term(i);
		//return *this;
	}
	
	polynomial::polynomial(const polynomial& source)
	{
		coef = new double[source.size];
		size = source.size;
		current_degree = source.current_degree;
		for(int i = 0; i < source.size; i++)
			coef[i] = source.coef[i];
	}
	
	polynomial::~polynomial(){
		delete [] coef;
	}
	
	void polynomial::reserve(unsigned int number){
		polynomial temp=*this;
		if(number<this->current_degree){
			return;
		}
		else{
			delete [] this->coef;
			this->coef = new double[number];
			this->size = number;
			this->current_degree= temp.current_degree;
			for(int i=0; i<=number; i++){
				if(i<=temp.size){
					this->coef[i]=temp.coef[i];
				}
				else{
					this->coef[i]=0;
				}
			}
			return;
		}
	}
	
	
	void polynomial::add_to_coef(double amount, unsigned int exponent){
		// unsigned int x;
		if(exponent < size)
			coef[exponent] += amount;
		if(exponent >= size)
		{
			reserve(exponent+20);
			coef[exponent] += amount;
		}
		current_degree = 0;
		for(int i = 0; next_term(i) != 0; i = next_term(i))
			current_degree = next_term(i);
		
	}
	
	void polynomial::assign_coef(double coefficient, unsigned int exponent)
	{
		unsigned int x;
		if(exponent < size){
			coef[exponent] = coefficient;
		}
		if(exponent >= size){
			reserve(exponent+20);
			coef[exponent] = coefficient;
		}
		current_degree = 0;
		for(int i = 0; next_term(i) != 0; i = next_term(i))
			current_degree = next_term(i);
	}
	
	void polynomial::clear(){
		for(int i=0;i<=this->size;i++){
			coef[i]=0;
		}
		current_degree=0;
	}
	
	double polynomial::coefficient(unsigned int exponent) const
	{
		if(exponent < size)
			return coef[exponent];
		if(exponent >= size)
			return 0;
	}
	
	polynomial polynomial::derivative() const
	{
		polynomial temp;
		for(int i = 0; i < size; i++)
			temp.assign_coef((coefficient(i+1)*(i+1)),i);
		return temp;
	}
	
	double polynomial::eval(double x)const{
		double total=0.0;
		for(int i=0; i<this->size;i++)
			total = total + (coef[i]*(pow((double)x,(double)i)));
		return total;
	}
	
	unsigned int polynomial::next_term(unsigned int e) const
	{
		unsigned int n = 0;
		for(int i = size-1; i > e; i--)
			if(coefficient(i) != 0)
				n = i;
		return n;
	}
	
	unsigned int polynomial::previous_term(unsigned int e) const
	{
		unsigned int n = UINT_MAX;
		for(unsigned int i = 0; i < e; i++)
			if(coefficient(i) != 0)
				n = i;
		return n;
	}
	
	polynomial operator -(const polynomial& p1, const polynomial& p2){
		polynomial temp;
		for(unsigned int i=0;p1.next_term(i)!=0; i=p1.next_term(i)){
			temp.assign_coef(p1.coefficient(i),i);
		}
		for(unsigned int j=0;p2.next_term(j)!=0; j=p2.next_term(j)){
			temp.add_to_coef((-1*(p2.coefficient(j))),j);
		}
	}
	
	polynomial operator +(const polynomial& p1, const polynomial& p2)
    {
		polynomial temp;
		for(int i = 0; p1.next_term(i) != 0; i = p1.next_term(i))	
			temp.assign_coef(p1.coefficient(i), i);
		for(int j = 0; p2.next_term(j) != 0; j = p2.next_term(j))
			temp.add_to_coef(p2.coefficient(j), j);
		
		return temp;
	}
	polynomial operator *(const polynomial& p1, const polynomial& p2){
		polynomial temp;
		double x=0;
		for(int i=0; p1.next_term(i)!=0; i=p1.next_term(i)){
			for(int j=0; p2.next_term(j)!=0; j=p2.next_term(j)){
				x=(p1.coefficient(i))*(p2.coefficient(j));
				temp.add_to_coef(x,(i+j));
			}
		}
	return temp;
	}
		
	ostream& operator <<(ostream& out, const polynomial& p){
		int x=0;
		for(int i=400; i>=0; i--){
			if(p.coefficient(i)!=0.0){
				if(x==0){
					if(i!=0){
						if(p.coefficient(i)<0){
							out << "-";
						}
						out << fabs(p.coefficient(i)) << "x^" << i; 
					}
					if(i==0){
						out << p.coefficient(i);
					}
					x=1;
					continue;
				}
				if(x>0){
					if(p.coefficient(i)<0 && i!=0 && i!=1){
						out << " - " << fabs(p.coefficient(i)) << "x^" << i;
					}
					if(p.coefficient(i)>0 && i!=0 && i!=1){
						out << " + " << fabs(p.coefficient(i)) << "x^" << i;
					}
					if(p.coefficient(i)<0 && i==0){
						out << " - " << fabs(p.coefficient(i));
					}
					if(p.coefficient(i)>0 && i==0){
						out << " + " << fabs(p.coefficient(i));
					}
					if(p.coefficient(i)<0 && i==1){
						out << " - " << fabs(p.coefficient(i)) << "x";
					}
					if(p.coefficient(i)>0 && i==1){
						out << " + " << fabs(p.coefficient(i)) << "x";
					}
					


				}
			}
		}
		if(x==0){
			out << endl;
		}
		if(x>0){
			out << endl;
		}
	}
}
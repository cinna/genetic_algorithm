#include "StdAfx.h"
#include "gen.h"
#include <bitset>

using namespace std;


bool operator == (gen &rhs,gen &lhs)
{
	return (rhs.x==lhs.x && rhs.y==lhs.y);
}
const gen &gen::operator = (gen &rhs)
{
	this->x=rhs.x;
	this->y=rhs.y;
	this->fitness=rhs.fitness;
	return *this;
}

bool operator < (gen &rhs,gen &lhs)
{
	return (lhs.fitness > rhs.fitness);
}
void gen::mutation()
{
	bitset<(sizeof(unsigned long int)*8)> a,b;
	a=x;
	b=y;
	a.flip(rand()%(sizeof(unsigned long int)*8));
	b.flip(rand()%(sizeof(unsigned long int)*8));
	x=a.to_ulong();
	y=b.to_ulong();
}
gen &gen::crossover(gen &a)
{
	int i,temp;
	int n=rand()%(sizeof(unsigned long int)*8);
	bitset<(sizeof(unsigned long int)*8)> c,s;
	c=x;
	s=a.getx();
	for (i=0;i<(sizeof(unsigned long int)*8)&&i<n;i++)
	{
		temp=c[i];
		c[i]=s[i];
		s[i]=temp;
	}
	x=c.to_ulong();
	a.setx(s.to_ulong());

	c=y;
	s=a.gety();
	for (i=0;i<(sizeof(unsigned long int)*8)&&i<n;i++)
	{
		temp=c[i];
		c[i]=s[i];
		s[i]=temp;
	}
	y=c.to_ulong();
	a.sety(s.to_ulong());
	return a;
}
gen::gen(void)
{

	x=(unsigned long int)(rand()*(ULONG_MAX/RAND_MAX));
	y=(unsigned long int)(rand()*(ULONG_MAX/RAND_MAX));
}
gen::gen(unsigned long int a,unsigned long int b)
{
	x=a;
	y=b;
}

gen::~gen(void)
{
}

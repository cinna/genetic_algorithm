#pragma once
#include <climits>
class gen
{
private:
	unsigned long int x;
	unsigned long int y;
	
	float fitness;
public:
	gen(unsigned long int ,unsigned long int );
	void setfitness(float a){fitness=a;}
	float getfitness(){return fitness;}
	void setx(unsigned long int a){x=a;}
	void sety(unsigned long int a){y=a;}

	void mutation();
	gen &crossover(gen &);

	const gen &operator = (gen &);
	
	unsigned long int getx(){return x;}
	unsigned long int gety(){return y;}
	
	float getfx(){return ((float)x/(float)ULONG_MAX);} //[0,1] :  boundary
	float getfy(){return ((float)y/(float)ULONG_MAX);}
	
	friend bool operator == (gen &,gen &);
	friend bool operator < (gen &,gen &);
	

	

	gen(void);
	~gen(void);
};

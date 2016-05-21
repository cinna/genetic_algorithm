#pragma once
#include "gen.h"
#include <list>
#include <GL/glut.h>
using namespace std;

typedef list<gen *> genList;

class nation
{

private:
genList population;
genList government;
genList Ngeneration;
gen policy;
public:
	float color[3];
	GLfloat ctlpoints[16][16][3];

    void initsurface(void);
	void fitness (gen &);
	float distpolicy (gen &a);

	bool initialize(int );
	void setgovernment();
	bool is_government(gen *);
	void setpolicy();
	gen* WantToMigrate();
	genList getpopulation(){return population;}
	gen *getpolicy(){return &policy;}
	gen *RouletteSelection();
	void setfitness();
	void newgeneration();
	void mutation();
	void crossover();
	GLfloat *points();
	GLfloat *policypoint();
	int popsize();
	bool hill_valley(gen *a,gen *b);
	void merge(nation );
	void add(gen *);
	void remove(gen *);
	//bool gless (gen *rhs,gen *lhs);
	nation(void);
	~nation(void);
};

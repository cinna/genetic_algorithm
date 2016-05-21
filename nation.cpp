#include "StdAfx.h"
#include "nation.h"
#include <ctime>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <GL/glut.h>
#include "Nurbs.cpp"



void nation::initsurface(void)
{
  /*  int u, v;
	int i,j;
    for (u = 0; u < 4; u++) {
	for (v = 0; v < 4; v++) {
	    ctlpoints[u][v][0] = 2.0*((GLfloat)u - 1.5);
	    ctlpoints[u][v][1] = 2.0*((GLfloat)v - 1.5);
		
	    if ( (u == 1 || u == 2) && (v == 1 || v == 2))
		ctlpoints[u][v][2] = 10.0;
	    else
		ctlpoints[u][v][2] = 0.0;
	}
    }
	for(i=0;i<4;i++) {
      for(j=0;j<4;j++) {
	//cout << ctlpoints[i][j][0] << "," << ctlpoints[i][j][1]<< ","  << ctlpoints[i][j][2] << ";" ;
      }
	}*/
	    int u, v;
    for (u = 0; u < 16; u++) {
	for (v = 0; v < 16; v++) {
	    ctlpoints[u][v][0] = .50*((GLfloat)u - .5) - 3;
	    ctlpoints[u][v][1] = .50*((GLfloat)v - .5) -5;

	    if ( (u == 1 || u == 2) && (v == 1 || v == 2))
		ctlpoints[u][v][2] = 3.0;
	    else
		ctlpoints[u][v][2] = 3.0;
	}
    }	
	ctlpoints[2][2][2]= 4.0;
	ctlpoints[1][2][2]= 4.0;
	ctlpoints[2][1][2]= 4.0;
	ctlpoints[1][1][2]= 4.0;

	ctlpoints[6][2][2]= 0.0;
	ctlpoints[5][2][2]= 0.0;
	ctlpoints[6][1][2]= 0.0;
	ctlpoints[5][1][2]= 0.0;

	ctlpoints[2][6][2]= 0.0;
	ctlpoints[1][6][2]= -0.0;
	ctlpoints[2][5][2]= -0.0;
	ctlpoints[1][5][2]= -0.0;

	ctlpoints[6][6][2]= 10.0;
	ctlpoints[5][6][2]= 10.0;
	ctlpoints[6][5][2]= 10.0;
	ctlpoints[5][5][2]= 10.0;


	ctlpoints[14][2][2]= -0.0;
	ctlpoints[13][2][2]= -0.0;
	ctlpoints[14][1][2]= -0.0;
	ctlpoints[13][1][2]= -0.0;

	ctlpoints[10][2][2]= 6.0;
	ctlpoints[9][2][2]= 6.0;
	ctlpoints[10][1][2]= 6.0;
	ctlpoints[9][1][2]= 6.0;

	ctlpoints[10][6][2]= -0.0;
	ctlpoints[9][6][2]= -0.0;
	ctlpoints[10][5][2]= -0.0;
	ctlpoints[9][5][2]= -0.0;

	ctlpoints[14][6][2]= 6.0;
	ctlpoints[13][6][2]= 6.0;
	ctlpoints[14][5][2]= 6.0;
	ctlpoints[13][5][2]= 6.0;



	ctlpoints[14][14][2]= -0.0;
	ctlpoints[13][14][2]= -0.0;
	ctlpoints[14][13][2]= -0.0;
	ctlpoints[13][13][2]= -0.0;

	ctlpoints[10][10][2]= 6.0;
	ctlpoints[9][10][2]= 6.0;
	ctlpoints[10][9][2]= 6.0;
	ctlpoints[9][9][2]= 6.0;

	ctlpoints[10][14][2]= -0.0;
	ctlpoints[9][14][2]= -0.0;
	ctlpoints[10][13][2]= -0.0;
	ctlpoints[9][13][2]= -0.0;

	ctlpoints[14][14][2]= 4.0;
	ctlpoints[13][14][2]= 4.0;
	ctlpoints[14][13][2]= 4.0;
	ctlpoints[13][13][2]= 4.0;


	ctlpoints[6][14][2]= 6.0;
	ctlpoints[5][14][2]= 6.0;
	ctlpoints[6][13][2]= 6.0;
	ctlpoints[5][13][2]= 6.0;
}
void nation::fitness (gen &a)
{
    GLfloat knots[32] = {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
	float dest[3];
	SurfacePoint(a.getfx(),a.getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],dest);
	a.setfitness(dest[2]);
}

float nation::distpolicy (gen &a)
{
    GLfloat knots[32] = {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
	float dest[3],pdest[3];
	SurfacePoint(a.getfx(),a.getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],dest);
	SurfacePoint(policy.getfx(),policy.getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],pdest);
	return sqrt(((dest[0]-pdest[0])*(dest[0]-pdest[0]))+((dest[1]-pdest[1]))*((dest[1]-pdest[1])));
}


#define pm .10
#define pc .7

bool nation::initialize(int a)
{
	int i;
	srand((unsigned)time( NULL ));
	for (i=0;i<=a;i++){
	population.push_back(new gen);
	} //initialize population
	return true;
}
nation::nation(void)
{
	initsurface();
	color[0]=(float)rand()/RAND_MAX;
	color[1]=(float)rand()/RAND_MAX;
	color[2]=(float)rand()/RAND_MAX;
}

nation::~nation(void)
{
	population.clear();
	government.clear();
}
inline bool gless (gen *rhs,gen *lhs)
{
	return (lhs->getfitness() < rhs->getfitness());
}
inline bool gequal(gen *rhs,gen *lhs)
{
	return (lhs->getx()==rhs->getx() && lhs->gety()==rhs->gety());
}
void nation::merge(nation a)
{
	cout << "merging...";
	population.merge(a.getpopulation());
}
void nation::add(gen *a)
{
	population.push_back(a);
}
void nation::remove(gen * a)
{
	population.remove(a);
}
bool nation::is_government(gen *a)
{
	genList::iterator it;
	for (it=government.begin();it!=government.end();it++)
		if (*it==a) return true;
	return false;
}
gen *nation::WantToMigrate()
{
	genList::iterator it;
	if (population.size() <= 1) return (gen *)NULL;
	for (it=population.begin();it!=population.end();it++)
		if ( hill_valley(&policy,*it) ) {return *it;}//&& !is_government(*it)
		return (gen *)NULL;
}
bool nation::hill_valley(gen *a,gen *b)
{
	int i;
	GLfloat knots[32] = {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
	float desta[3],difx,dify,l1,l2;
	//cout << "afx:" << a->getfx() << " bfx:" << b->getfx();
	difx=(a->getfx()-b->getfx())/50.0;
	dify=(a->getfy()-b->getfy())/50.0;
	/*cout <<endl <<"-------------------------------------------"<< endl << "difx:" <<difx <<"dify:" <<dify <<endl;
	SurfacePoint(a->getfx(),a->getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],desta);
	cout <<"genx:" <<desta[0]<<"geny:" <<desta[1]<<"genz:" <<desta[2] <<endl;
	SurfacePoint(b->getfx(),b->getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],desta);
	 cout <<"genx:" <<desta[0]<<"geny:" <<desta[1]<<"genz:" <<desta[2] <<endl;
	for (i=0;i<=10;i++)
	{
		cout << (b->getfx()+((float)i * difx)) << endl;
		l1=b->getfx()+(float)i * difx;
		l2=b->getfy()+(float)i * dify;
		SurfacePoint(l1,l2,16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],desta);
		cout <<"x:" << desta[0] << " y:" << desta[1] << " z:" << desta[2] << endl;
	}*/
	for (i=1;i<50;i++)
	{
		l1=b->getfx()+(float)i * difx;
		l2=b->getfy()+(float)i * dify;
		SurfacePoint(l1,l2,16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],desta);
		//cout << a->getfitness() << b->getfitness() << desta[2];
		if (desta[2] < a->getfitness() && desta[2] < b->getfitness()) 
		{
			return true;
			//cout <<"true";
		}
		//cout << "false:" << i; 
	}
	return false;    
}

void nation::setgovernment()
{
	genList::iterator it;
	int i=0;
	government.clear();
	population.sort(gless);
	for (it=population.begin();it!=population.end() && i<=8 ;it++,i++){
		government.push_back(*it);
	}
}
void nation::setpolicy()
{
	genList::iterator it;
	unsigned long int tx=0,ty=0;
	float tx1=0,ty1=0,tf1=0;
	unsigned long int bx,by;
	int n =(int) government.size();
	if (n) {
		for (it=government.begin();it!=government.end();it++)
		{
			//tx+=(*it)->getx();
			//ty+=(*it)->gety();
			tx1+=(*it)->getfx();
			ty1+=(*it)->getfy();
			//tf1+=(*it)->getfitness();
			if (tf1 < (*it)->getfitness()) tf1=(*it)->getfitness();
		}
	}
	bx=(tx1/(float)n)*ULONG_MAX;
	by=(ty1/(float)n)*ULONG_MAX;
	policy.setx(bx);//(tx/n));
	policy.sety(by);//(ty/n));
	policy.setfitness(tf1);///(float)n);
}
gen *nation::RouletteSelection()
{
	genList::iterator it;
	int i;
	float t=0.0,r;
	//time_t d;
	population.sort(gless);
	//srand((unsigned)time( &d ));
	//random_shuffle(population.begin(),population.end());
	int n =(int) population.size();
	if (n) {
		for (it=population.begin();it!=population.end();it++)
		{
			t+=(*it)->getfitness();
		}
		r=(float)rand()/(float)RAND_MAX*t;
		t=0.0;
		for (it=population.begin();it!=population.end();it++)
		{
			t+=(*it)->getfitness();
			if (t>r) return (*it);
		}
	}
}
void nation::mutation()
{
	genList::iterator it;
	int i;
	float distopol=0.0;
	for (it=population.begin();it!=population.end();it++)
		{
			distopol = distpolicy(**it);
            if ((float)rand()/RAND_MAX < (pm / distopol)) (*it)->mutation();
		}
}
void nation::crossover()
{
}
void nation::newgeneration()
{
	gen *a1,*b1,*a,*b;
	int i,temp,l;
	int n=rand()%(sizeof(unsigned long int)*8);
	bitset<sizeof(unsigned long int)*8> c,s;
	float distopol=0.0;
	genList::iterator it;

	Ngeneration.clear();
	Ngeneration.insert(Ngeneration.begin(),government.begin(),government.end());
	while (Ngeneration.size() < population.size())
	{
		 a1=RouletteSelection();
		 b1=RouletteSelection();
		 a = new gen;
		 b= new gen;
		 *a = *a1;
		 *b = *b1;

		 if (gequal(a,b)) continue;
		
		distopol = distpolicy(*a);
		if ((float)rand()/(float)RAND_MAX < (pm * distopol))   //mutation
		{
			a->mutation();
			Ngeneration.push_back(a); 
			continue;
		}
		n=rand()%(sizeof(unsigned long int)*8);
		if ((float)rand()/(float)RAND_MAX < pc && Ngeneration.size() < population.size())//crossover
		{
			c=b->getx();
			s=a->getx();
			l=(sizeof(unsigned long int)*8);
			for (i=0;i<(sizeof(unsigned long int)*8)&&i<n;i++)
			{
				temp=c[l-i-1];
				c[l-i-1]=s[l-i-1];
				s[l-i-1]=temp;
			}
			b->setx(c.to_ulong());
			a->setx(s.to_ulong());
	
			c=b->gety();
			s=a->gety();
			for (i=0;i<(sizeof(unsigned long int)*8) && i<n;i++)
			{
				temp=c[l-i-1];
				c[l-i-1]=s[l-i-1];
				s[l-i-1]=temp;
			}
			b->sety(c.to_ulong());
			a->sety(s.to_ulong());
		//}
		Ngeneration.push_back(a);
		if (Ngeneration.size() < population.size()) Ngeneration.push_back(b);
		}
		Ngeneration.unique(gequal);
	}
	
	population.clear();
	population.insert(population.begin(),Ngeneration.begin(),Ngeneration.end());
	cout << " size:" << population.size() << " -" ;
}
void nation::setfitness()
{
	genList::iterator it;
	int i;
	float distopol=0.0;
	for (it=population.begin();it!=population.end();it++)
		fitness(**it);
	for (it=government.begin();it!=government.end();it++)
		fitness(**it);
			
}

GLfloat *nation::points()
{
    GLfloat knots[32] = {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
	float dest[3];
	genList::iterator it;
	int i=0;
	GLfloat *point = new GLfloat[population.size()*3];
	for (it=population.begin();it!=population.end();it++,i++)
	{	
		SurfacePoint((*it)->getfx(),(*it)->getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],dest);

		*(point+i*3)=dest[0];
		*(point+i*3+1)=dest[1];
		*(point+i*3+2)=dest[2];
	}
	return point;
}
GLfloat *nation::policypoint()
{
	GLfloat knots[32] = {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
	float dest[3];
	genList::iterator it;
	int i=0;
	GLfloat *point=new GLfloat[3];
	SurfacePoint(policy.getfx(),policy.getfy(),16,16,16,16,knots,knots,16*3,3,&ctlpoints[0][0][0],dest);

		*(point)=dest[0];
		*(point+1)=dest[1];
		*(point+2)=policy.getfitness();
	
	return point;
}

int nation::popsize()
{
	if (population.empty()) return 0;
	return population.size();
}





                
		


// con32.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"


// This is the main project file for VC++ application project 
// generated using an Application Wizard.

//#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
#include <time.h>

#include "gen.h"
#include "nation.h"
//#include "Nurbs.cpp"


using namespace std;

	list<nation> nations;


//#include "util.cpp"

	GLfloat ctlpoints[16][16][3];
	static int k = 0;
	int showPoints = 0;
	int policypoints = 0; 
	
	GLUnurbsObj *theNurb;



#define PopulationNo    200
#define GenerationNo	200 
typedef list<gen *> genList;



/*
 *  Initializes the control points of the surface to a small hill.
 *  The control points range from 0 to +10 in x, y, and z
 */
void init_surface(void)
{
    /*int u, v;
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
			
/*  Initialize material property and depth buffer.
 */
void myinit(void)
{
    GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glClearColor (0.0, 0.0, 0.0, 1.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    init_surface();

    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

void runga(void)
{
	list<nation>::iterator it,it1,it2,it3;
	nation *temp;
	gen *tg;
	int m=0;
	float td=0;
	bool v;
	
	//cout << k << "-";
	//for (k=1;k<=GenerationNo;k++)
	if (k<=GenerationNo){
		k++;
	for (it=nations.begin();it!=nations.end();it++) 
	{
		cout <<k << "-";
		
		it->setfitness();
		it->setgovernment();
		it->setpolicy();
		it->newgeneration();//new generation
	}
	glutPostRedisplay();
		//merging
	for (it=nations.begin();it!=nations.end();)
	{
		it++;
		for (it1=it;it1!=nations.end();it1++)
		{
			v=it1->hill_valley(it->getpolicy(),it1->getpolicy());
			if (!v && it!=it1)  
			{
				it1->merge(*it);
				it2=it;
				it++;
				nations.erase(it2);
				break;
			}
		}
	}

	//glutPostRedisplay();

	//migration
	for (it=nations.begin();it!=nations.end();it++)
	{
		//it->setgovernment();
		//it->setpolicy();
		while ((tg = it->WantToMigrate())!=NULL && it->popsize()>0)
		{
			m=0;
			v=true;
			it1=nations.begin();
			td=100.0;
			for (it1=nations.begin();it1!=nations.end();it1++)
			{
				v=it1->hill_valley(it1->getpolicy(),tg);
				if (!v && it!=it1) 
				{					
					if(it1->distpolicy(*tg)<=td)
					{
						td=it1->distpolicy(*tg);
                        it2=it1;
						m=1;
					}
				}
			}
			if (m)
			{
                it2->add(tg);
				it->remove(tg);				
				//cout << "migrate...";
			}
			if (!m && it!=it1 && nations.size()){
				temp = new nation;
				temp->add(tg);
				it->remove(tg);
				nations.push_back(*temp);
			}
			for (it3=nations.begin();it3!=nations.end();it3++) 
			{
                it->setfitness();
				it->setgovernment();
				it->setpolicy();
			}
		}
	}


	//it1=nations.end();

	

	/*	for (it=nations.begin();it!=nations.end();it++) 
	{
		//cout <<k << "-";
		
		it->setfitness();
		it->setgovernment();
		it->setpolicy();
	}*/

	/*for (it=nations.begin();it!=nations.end();)
	{
		it++;
		for (it1=it;it1!=nations.end();it1++)
		{
			v=it1->hill_valley(it->getpolicy(),it1->getpolicy());
			if (!v && it!=it1) 
			{
				it1->merge(*it);
				it2=it;
				it++;
				nations.erase(it2);
				break;
			}
		}
	}*/
	/*for (it=nations.begin();it!=nations.end();it++)
	{
		if (it->popsize()==0) nations.erase(it);
	}*/

	//glutPostRedisplay();
	}
}
void display(void)
{
	list<nation>::iterator it;
	GLfloat *point,*p;
    GLfloat knots[32] = {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 ,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    int i, j;
	float dest[3];
	float w=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(330.0, 1.,0.,0.);
    glScalef (0.25, 0.25, 0.25);
	glColor3f(0.0,0.0,1.0);
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 
	    32, knots,
	    32, knots,
	    16 * 3,
	    3,
	    &ctlpoints[0][0][0], 
	    16, 16,
	    GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);
	///////// ax=.5 bx=.55 ay=.5 by.55
	
	for (it=nations.begin();it!=nations.end();it++)
	{
		point=it->points();
		//cout << it->popsize();
		for (i=0;i<=it->popsize();i++) {
			glPointSize(5.0);
		    glDisable(GL_LIGHTING);
		    glColor3f(it->color[0],it->color[1],it->color[2]);
		    //glBegin(GL_POINTS);
			glPushMatrix();
		    //glVertex3f(*(point+i*3),*(point+i*3+1),*(point+i*3+2));
			glTranslatef (*(point+i*3),*(point+i*3+1),*(point+i*3+2));
			glutSolidSphere(.06, 20, 8);
			//cout <<endl <<dest[0] <<dest[1] <<dest[2];
			//glEnd();
			glEnable(GL_LIGHTING);
			glPopMatrix();	    
		}
	}
	if(policypoints) {
		for (it=nations.begin();it!=nations.end();it++)
		{
				p=it->policypoint();
				glPointSize(10.0);
			    glDisable(GL_LIGHTING);
			    glColor3f(it->color[0],it->color[1],it->color[2]);
			    glBegin(GL_POINTS);
			    glVertex3f(*p,*(p+1),*(p+2));
				//cout <<endl <<*p <<*(p+1) <<*(p+2);
				glEnd();
			    glEnable(GL_LIGHTING);
		}
	}
	///////
    if(showPoints) {
    glPointSize(5.0);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for(i=0;i<16;i++) {
      for(j=0;j<16;j++) {
	glVertex3f(ctlpoints[i][j][0], ctlpoints[i][j][1], ctlpoints[i][j][2]);
      }
    }
    glEnd();
    glEnable(GL_LIGHTING);
    }
        
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (GLdouble)w/(GLdouble)h, 3.0, 8.0);

    glMatrixMode(GL_MODELVIEW);
}

void
menu(int value)
{
    switch (value) {
    case 0:
    case 1:
        showPoints = value;
	break;
    case 2:
        gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
	break;
    case 3:
        gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
	break;
	case 4:
		runga();
	break;
	case 5:
		glutIdleFunc(runga);
	break;
	case 6:
		glutIdleFunc(NULL);
	break;
	case 7:
		policypoints = 1;
	break;
	case 8:
		policypoints = 0;
	break;

	
    }
    glutPostRedisplay();
}

int down = 0, lastx,lasty;

/* ARGSUSED1 */
void
motion(int x, int y)
{
    if (down) {
        glRotatef(-lastx + x, 0, 1, 0);
        lastx = x;
		glRotatef(-lasty + y, 1, 0, 0);
        lasty = y;
        glutPostRedisplay();
    }
}

/* ARGSUSED3 */
void
mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastx = x;
			lasty = y;
            down = 1;
        } else {
            down = 0;
        }
    }
}

/////////////////////////////////GA
// This is the main project file for VC++ application project 
// generated using an Application Wizard.


int _tmain(int argc, _TCHAR* argv[])
{

	nation init;
	init.initialize(PopulationNo);
	nations.clear();
	nations.push_back(init);
	// TODO: Please replace the sample code below with your own.


	//runga();

    // TODO: Please replace the sample code below with your own.
	
	char *s=" ";
//	char** argv=&s;
	    glutInit(&argc,argv);
 
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Multinational GA");
    myinit();
	//glutIdleFunc(runga); 
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Show control points", 1);
    glutAddMenuEntry("Hide control points", 0);
    glutAddMenuEntry("Solid", 2);
    glutAddMenuEntry("Wireframe", 3);
	glutAddMenuEntry("Next generation", 4);
	glutAddMenuEntry("Go!", 5);
	glutAddMenuEntry("Stop", 6);
	glutAddMenuEntry("Show Policy Points", 7);
	glutAddMenuEntry("Hide Policy Points", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();






//    Console::WriteLine(S"Hello World");
	
	return 0;
}



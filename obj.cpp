#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>

#include "obj.h"
using namespace std;

	//Costruttore
	Obj::Obj(){
		X=0; Y=0; Z=-10; rX=rY=rZ=vX=vY=vZ=0;
		randomizeDimension();
		cout << "costruttore 0 param";
	};

	//Costruttore a 3 parametri (posizione)
	Obj::Obj(float _X,float _Y,float _Z){
		X=_X; Y=_Y; Z=_Z; rX=rY=rZ=vX=vY=vZ=0;
		randomizeDimension();
	};

	//Costruttore a 6 parametri (posizione+rotazione)
	Obj::Obj(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ){
		X=_X; Y=_Y; Z=_Z; rX=_rX; rY=_rY; rZ=_rZ; vX=vY=vZ=0;
		randomizeDimension();
	};

	//Costruttore a 6 parametri (posizione+rotazione+velocita)
	Obj::Obj(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ,float _vX,float _vY,float _vZ){
		X=_X; Y=_Y; Z=_Z; rX=_rX; rY=_rY; rZ=_rZ; vX=_vX; vY=_vY; vZ=_vZ;
		randomizeDimension();
	};

	void Obj::randomizeDimension(){
		R = (rand()%150+15)/100.0f;
		cout << "R:" << R;

		L = (rand()%400+20)/100.0f;
		cout << "L:" << L;
	}

	void Obj::drawMe(){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		/*
	    GLfloat ambiente[4] = {0.8, 0.0, 0.8, 1};
	    GLfloat direttiva[4] = {0.8, 0.0, 0.8, 1};
	    GLfloat brillante[4] = {1.0, 1.0, 1.0, 1};
	    glMateriali(GL_FRONT, GL_SHININESS, 32 ); //brillantezza

	    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente); //faccia anteriore della primitiva (c'è quella posteriore anche...)
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
		*/
		glTranslatef(X,Y+L,Z);
		glRotatef(rX, 1, 0, 0);
		glRotatef(rY, 0, 1, 0);
		glRotatef(rZ, 0, 0, 1);

		glBegin(GL_QUADS);

			glColor3f(1, 0, 1);
			glVertex3f(R, L, R);
			glVertex3f(-R, L, R);
			glVertex3f(-R, -L, R);
			glVertex3f(R, -L, R);

			glColor3f(0, 0, 1);
			glVertex3f(-R, L, -R);
			glVertex3f(R, L, -R);
			glVertex3f(R, -L, -R);
			glVertex3f(-R, -L, -R);

			glColor3f(1, 1, 0);
			glVertex3f(R, L, -R);
			glVertex3f(R, L, R);
			glVertex3f(R, -L, R);
			glVertex3f(R, -L, -R);

			glColor3f(0.5f, 0, 1);
			glVertex3f(-R, L, R);
			glVertex3f(-R, L, -R);
			glVertex3f(-R, -L, -R);
			glVertex3f(-R, -L, R);

			glColor3f(0, 1, 1);
			glVertex3f(R, L, -R);
			glVertex3f(-R, L, -R);
			glVertex3f(-R, L, R);
			glVertex3f(R, L, R);

			glColor3f(1, 0, 0);
			glVertex3f(-R, -L, -R);
			glVertex3f(R, -L, -R);
			glVertex3f(R, -L, R);
			glVertex3f(-R, -L, R);

		glEnd();

		//Bordi neri
		/*
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP); //"prima faccia" del cubo
		glVertex3f(-1,-1,1);
		glVertex3f(1,-1,1);
		glVertex3f(1,1,1);
		glVertex3f(-1,1,1);
		glEnd();

		glBegin(GL_LINE_LOOP); //seconda faccia del cubo
		glVertex3f(-1,-1,-1);
		glVertex3f(1,-1,-1);
		glVertex3f(1,1,-1);
		glVertex3f(-1,1,-1);
		glEnd();

		glBegin(GL_LINES);//I 4 segmenti che collegano le facce
			glVertex3f(-1,-1,-1);
			glVertex3f(-1,-1,1);
			glVertex3f(1,-1,-1);
			glVertex3f(1,-1,1);
			glVertex3f(1,1,-1);
			glVertex3f(1,1,1);
			glVertex3f(-1,1,-1);
			glVertex3f(-1,1,1);
		glEnd();
		*/
		glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

	}



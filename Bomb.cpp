/*
 * Bomb.cpp
 *
 *  Created on: 16/apr/2010
 *      Author: ziby
 */

#include "Bomb.h"

Bomb::Bomb(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z, 0.5f,0.5f,0.5f), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, 0,1,0) {
	setL(1.0f);
}

void Bomb::move(long time){

	setY(getY()-getvY()*time/500);

};

void Bomb::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(getX(),getY(),getZ());
	glRotatef(getrX(), 1, 0, 0);
	glRotatef(getrY(), 0, 1, 0);
	glRotatef(getrZ(), 0, 0, 1);

	float R = getDimX();
	glColor3f((rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f);
	glutSolidSphere(getDimX(),50,50);
	/*glBegin(GL_QUADS);

		glColor3f(1, 0, 1);
		glVertex3f(R, getL(), R);
		glVertex3f(-R, getL(), R);
		glVertex3f(-R, -getL(), R);
		glVertex3f(R, -getL(), R);

		glColor3f(0, 0, 1);
		glVertex3f(-R, getL(), -R);
		glVertex3f(R, getL(), -R);
		glVertex3f(R, -getL(), -R);
		glVertex3f(-R, -getL(), -R);

		glColor3f(1, 1, 0);
		glVertex3f(R, getL(), -R);
		glVertex3f(R, getL(), R);
		glVertex3f(R, -getL(), R);
		glVertex3f(R, -getL(), -R);

		glColor3f(0.5f, 0, 1);
		glVertex3f(-R, getL(), R);
		glVertex3f(-R, getL(), -R);
		glVertex3f(-R, -getL(), -R);
		glVertex3f(-R, -getL(), R);

		glColor3f(0, 1, 1);
		glVertex3f(R, getL(), -R);
		glVertex3f(-R, getL(), -R);
		glVertex3f(-R, getL(), R);
		glVertex3f(R, getL(), R);

		glColor3f(1, 0, 0);
		glVertex3f(-R, -getL(), -R);
		glVertex3f(R, -getL(), -R);
		glVertex3f(R, -getL(), R);
		glVertex3f(-R, -getL(), R);

	glEnd();*/

	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};

Bomb::~Bomb() {
	// TODO Auto-generated destructor stub
};

/*
 * Projectile.cpp
 *
 *  Created on: 21/apr/2010
 *      Author: ziby
 */

#include "Projectile.h"

Projectile::Projectile(float _X,float _Y,float _Z, float _vX,float _vY,float _vZ) : Obj(_X,_Y,_Z, 0.4f,0.4f,0.4f), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, _vX,_vY,_vZ) {
	// TODO Auto-generated constructor stub

}

void Projectile::move(long time){

	setX(getX()-getvX()*time/speed);
	setY(getY()-getvY()*time/speed);
	setZ(getZ()-getvZ()*time/speed);
}

void Projectile::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(getX(),getY(),getZ());
	glRotatef(getrX(), 1, 0, 0);
	glRotatef(getrY(), 0, 1, 0);
	glRotatef(getrZ(), 0, 0, 1);

	float R = getDimX();
	//glColor3f((rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f);
	glColor3f(0.3f,0.3f,0.9f);
	glutSolidSphere(getDimX(),20,10);

	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};

Projectile::~Projectile() {
	cout << "Projectile deleted" << endl;
}

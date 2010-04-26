/*
 * Explosion.cpp
 *
 *  Created on: 26/apr/2010
 *      Author: ziby
 */

#include "Explosion.h"

Explosion::Explosion(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z)  {
radius=0.0f;

}

void Explosion::processExplosion(int delta){
radius+=0.1f;
}

bool Explosion::isFinished(){
if(radius>=2)return true;
return false;
}


void Explosion::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(getX(),getY(),getZ());
	glRotatef(getrX(), 1, 0, 0);
	glRotatef(getrY(), 0, 1, 0);
	glRotatef(getrZ(), 0, 0, 1);

	GLfloat ambiente[4] =  { radius/2, 0.1f, 0.1f, 1.0f };
	GLfloat direttiva[4] =  { radius/2, 0.1f, 0.1f, 1.0f };
	GLfloat brillante[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMateriali(GL_FRONT, GL_SHININESS, 32);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

	glutSolidSphere(radius,20,10);
	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};


Explosion::~Explosion() {
	// TODO Auto-generated destructor stub
}

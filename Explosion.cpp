/*
 * Explosion.cpp
 *
 *  Created on: 26/apr/2010
 *      Author: ziby
 */

#include "Explosion.h"

Explosion::Explosion(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z)  {
radius=1.5f;
spriteframe=0;
}

void Explosion::processExplosion(int delta){
//radius+=0.1f;
spriteframe++;
}

bool Explosion::isFinished(){
if(spriteframe>19)return true;
return false;
}


void Explosion::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(getX(),getY(),getZ());
	glRotatef(getrX(), 1, 0, 0);
	glRotatef(getrY(), 0, 1, 0);
	glRotatef(getrZ(), 0, 0, 1);


	float deltaY = 51.3f/256.0f;
	float deltaX = 64.0f/256.0f;
	int perline=4;

	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 13);

	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	glBegin(GL_QUADS);
		glTexCoord2f((spriteframe%perline)*deltaX,spriteframe/perline*deltaY);
		glVertex3f(-radius,radius,0);
		glTexCoord2f((spriteframe%perline+1)*deltaX,spriteframe/perline*deltaY);
		glVertex3f(radius,radius,0);
		glTexCoord2f((spriteframe%perline+1)*deltaX,(spriteframe/perline+1)*deltaY);
		glVertex3f(radius,-radius,0);
		glTexCoord2f((spriteframe%perline)*deltaX,(spriteframe/perline+1)*deltaY);
		glVertex3f(-radius,-radius,0);
	glEnd();
	//then draw your textured quad (which will be the mask)


	// SPRITE texture
	glTranslatef(0,0,0.1f);
	glBindTexture(GL_TEXTURE_2D, 12);
	glBlendFunc(GL_ONE,GL_ONE);

	glBegin(GL_QUADS);
	glTexCoord2f((spriteframe%perline)*deltaX,spriteframe/perline*deltaY);
	glVertex3f(-radius,radius,0);
	glTexCoord2f((spriteframe%perline+1)*deltaX,spriteframe/perline*deltaY);
	glVertex3f(radius,radius,0);
	glTexCoord2f((spriteframe%perline+1)*deltaX,(spriteframe/perline+1)*deltaY);
	glVertex3f(radius,-radius,0);
	glTexCoord2f((spriteframe%perline)*deltaX,(spriteframe/perline+1)*deltaY);
	glVertex3f(-radius,-radius,0);
	glEnd();

	glDisable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};


Explosion::~Explosion() {
	// TODO Auto-generated destructor stub
}

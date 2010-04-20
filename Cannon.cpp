/*
 * Cannon.cpp
 *
 *  Created on: 20/apr/2010
 *      Author: ziby
 */

#include "Cannon.h"

Cannon::Cannon() : Obj(0,10,-2, 1,1,2, -60,0,0) {
	targeting=0.0f;
}


void Cannon::targetingAnimation(){
	targeting += 0.05f;
	if(targeting>2.0f)targeting=0.0f;
}

void Cannon::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(getX(),getY(),getZ());
	glRotatef(getrX(), 1, 0, 0);
	glRotatef(getrY(), 0, 1, 0);
	glRotatef(getrZ(), 0, 0, 1);

	//glColor3f((rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f);
	 float alfa;
	     float s,c;
	     float step;

	     step=6.28f / 64.0f;
	     //Poco efficiente! Perchè quando disegno i rettangoli in sequenza, abbiamo sempre un lato in comune tra un rettangolo e quello che segue.
	     // meglio usare GL_QUAD_STRIP!!! (vedi sotto)

	     glColor3f(1.0f,0.1f,0.1f);
	     glBegin(GL_LINES);
			 for(register float i=targeting;i<100;i+=1){
				 glVertex3f(0, i*2, 0);
				 glVertex3f(0, i*2+1, 0);
			 }
	     glEnd();

	     glColor3f(0.2f,0.2f,0.2f);
	     glBegin(GL_QUAD_STRIP);
	      for(alfa = step; alfa < 6.29f; alfa += step) //messo di proposito 6.29f per esser sicuri di fare un giro completo (circa 2pigreco=360°)
	      {
	    	  s = sin(alfa - step) /2;
	    	  c = cos(alfa - step) /2;
	    	  //glNormal3f(c,0,s);
	    	  glVertex3f(c, -2, s);
	    	  glVertex3f(c,  2, s);
	      }
	     glEnd();

	  glPopMatrix();
}

Cannon::~Cannon() {
	// TODO Auto-generated destructor stub
}

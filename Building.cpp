
#include "Building.h"

Building::Building(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ) : Obj(_X,_Y,_Z,0,0,0,_rX,_rY,_rZ), DistructableObj(_X,_Y,_Z,0,0,0,_rX,_rY,_rZ) {
	cout << "##### Building creato! ######" << endl;
	randomizeDimension();
	texture_id = rand()%4;

}

void Building::randomizeDimension(){
	R = (rand()%150+40)/100.0f;
	cout << "R:" << R;
}

float Building::getR() const{
	return R;
}

void Building::drawMe(){
glMatrixMode(GL_MODELVIEW);
glPushMatrix();


glTranslatef(getX(),getY()+getL(),getZ());
glRotatef(getrX(), 1, 0, 0);
glRotatef(getrY(), 0, 1, 0);
glRotatef(getrZ(), 0, 0, 1);

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 6+texture_id);
GLfloat ambiente[4] = { 1, 1, 1, 1 };
GLfloat direttiva[4] = { 1, 1, 1, 1 };
GLfloat brillante[4] = { 1, 1, 1, 1 };

glMateriali(GL_FRONT, GL_SHININESS, 32);
glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
glBegin(GL_QUADS);

	//glColor3f(1, 0, 1);
	//faccia frontale
	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1-getL()/getStartingL());
	glVertex3f(R, getL(), R);
	glTexCoord2f(0, 1- getL()/getStartingL());
	glVertex3f(-R, getL(), R);
	glTexCoord2f(0, 1);
	glVertex3f(-R, -getL(), R);
	glTexCoord2f(1,1);
	glVertex3f(R, -getL(), R);

	//glColor3f(0, 0, 1);
	//faccia posteriore
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1-getL()/getStartingL());
	glVertex3f(-R, getL(), -R);
	glTexCoord2f(1, 1-getL()/getStartingL());
	glVertex3f(R, getL(), -R);
	glTexCoord2f(1,1);
	glVertex3f(R, -getL(), -R);
	glTexCoord2f(0, 1);
	glVertex3f(-R, -getL(), -R);

	//glColor3f(1, 1, 0);
	//Faccia laterale destra
	glNormal3f(1, 0, 0);
	glTexCoord2f(1, 1-getL()/getStartingL());
	glVertex3f(R, getL(), -R);
	glTexCoord2f(0, 1- getL()/getStartingL());
	glVertex3f(R, getL(), R);
	glTexCoord2f(0, 1);
	glVertex3f(R, -getL(), R);
	glTexCoord2f(1,1);
	glVertex3f(R, -getL(), -R);

	//glColor3f(0.5f, 0, 1);
	//Faccia laterale sx
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 1-getL()/getStartingL());
	glVertex3f(-R, getL(), R);
	glTexCoord2f(1, 1-getL()/getStartingL());
	glVertex3f(-R, getL(), -R);
	glTexCoord2f(1,1);
	glVertex3f(-R, -getL(), -R);
	glTexCoord2f(0, 1);
	glVertex3f(-R, -getL(), R);

	//glColor3f(0, 1, 1);
	//Up
	glNormal3f(0, 1, 0);
	glVertex3f(R, getL(), -R);
	glVertex3f(-R, getL(), -R);
	glVertex3f(-R, getL(), R);
	glVertex3f(R, getL(), R);

	//glColor3f(1, 0, 0);
	//Bottom
	glNormal3f(0, -1, 0);
	glVertex3f(-R, -getL(), -R);
	glVertex3f(R, -getL(), -R);
	glVertex3f(R, -getL(), R);
	glVertex3f(-R, -getL(), R);

glEnd();
glDisable(GL_TEXTURE_2D);

glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

}

Building::~Building() {
	cout << "##### Building cancellato ######" << endl;
}

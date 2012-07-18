/*########################## PROJECTILE ########################*/
/* Classe che rappresenta i proiettili sparati dal cannone.
 * è un oggetto MOBILE e DISTRUTTIBILE.
 */


#include "Projectile.h"

//Costruttore (pos,dim)
Projectile::Projectile(float _X,float _Y,float _Z, float _vX,float _vY,float _vZ) : Obj(_X,_Y,_Z, 0.3f,0.3f,0.3f), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, _vX,_vY,_vZ) {
	oldX = _X;
	oldY = _Y;
	oldZ = _Z;
}

//Ovverride del metodo di movimento
void Projectile::move(long time){
	oldX = getX();
	oldY = getY();
	oldZ = getZ();
	setX(getX()-getvX()*time/speed);
	setY(getY()-getvY()*time/speed);
	setZ(getZ()-getvZ()*time/speed);
}

//Ovverride del metodo di drawing
void Projectile::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(getX(),getY(),getZ());
		glRotatef(getrX(), 1, 0, 0);
		glRotatef(getrY(), 0, 1, 0);
		glRotatef(getrZ(), 0, 0, 1);

		GLfloat ambiente[4] =  { 0.2f, 0.7f, 0.2f, 1.0f };
		GLfloat direttiva[4] =  { 0.2f,0.7f, 0.2f, 1.0f };
		GLfloat brillante[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		//glMateriali(GL_FRONT, GL_SHININESS, 32);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

		glutSolidSphere(getDimX(),20,10);
	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};

//Set & Get
float Projectile::getOldX()const { return oldX; }
float Projectile::getOldY()const { return oldY; }
float Projectile::getOldZ()const { return oldZ; }


Projectile::~Projectile() {
	cout << "Projectile deleted" << endl;
}

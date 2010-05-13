/*####################################### CANNON ##########################################
 *###################    Classe che rappresenta il cannone antibombe     ##################
 */

#include "Cannon.h"

//Costruttore
Cannon::Cannon() : Obj(0,10,-2, 1,1,2, -90,0,0) {
	targeting=0.0f;
	targetingSystem=false;
	recoil=0.0f;
}

//gestione animazione mirino
void Cannon::targetingAnimation(){
	targeting += 0.05f;
	if(targeting>2.0f)targeting=0.0f;
}

//toggle sistema puntamento
void Cannon::swapTargetingEnabled(){
	//toggle
	targetingSystem = !targetingSystem;
}

//Ovverride del metodo di drawing
void Cannon::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(getX(),getY(),getZ());
		glRotatef(getrX(), 1, 0, 0);
		glRotatef(getrY(), 0, 1, 0);
		glRotatef(getrZ(), 0, 0, 1);
		glTranslatef(0.0f,getRecoil(),0.0f);

		//glColor3f((rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f);
		float alfa;
		float s,c;
		float step;

		step=6.3f / 64.0f;

		//Cannone (un cilindro)
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 1);
		glBegin(GL_QUAD_STRIP);
		for(alfa = 0; alfa < 6.3f; alfa += step) //messo di proposito 6.29f per esser sicuri di fare un giro completo (circa 2pigreco=360°)
		{
			s = sin(alfa - step) /2;
			c = cos(alfa - step) /2;
			glNormal3f(c,0,s);
			glTexCoord2f(0, alfa/6.3f);
			glVertex3f(c, -2, s);

			glNormal3f(c,0,s);
			glTexCoord2f(1, alfa/6.3f);
			glVertex3f(c,  2, s);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

		GLfloat ambiente[4] = { 0.3f, 0.3f, 0.3f, 1 };
		GLfloat direttiva[4] = { 0.3f, 0.3f, 0.3f, 1 };
		GLfloat brillante[4] = { 0.7f, 0.7f, 0.7f, 1 };

		glMateriali(GL_FRONT, GL_SHININESS, 32);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

		//Bocca del cannone
		glPushMatrix();
			glTranslatef(0,2,0);
			glRotatef(90, 1, 0, 0);
			glutSolidTorus(0.2f,0.5f,20,20);
		glPopMatrix();

		//Mirino
		if(targetingSystem){
			glBegin(GL_LINES);
			for(register float i=targeting; i<100; i+=1.0f){
				glVertex3f(0, i*2, 0);
				glVertex3f(0, i*2+0.5f, 0);
			}
			glEnd();
		}

	glPopMatrix();
}

//metodi per la gestione del recoil
void Cannon::setRecoil(float mv){
	recoil = mv;
}
float Cannon::getRecoil()const{
	return recoil;
}

Cannon::~Cannon() {

}

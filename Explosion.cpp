/*##########################        EXPLOSION       ########################*/
/* Classe prettamente grafica che rappresenta un'esplosione.
 * Utilizza la tecnica delle "Sprite Animation" per l'effetto grafico dell'esplosione.
 */

#include "Explosion.h"

//Inizializzo l'array statico che individue le "luci disponibili"
bool Explosion::availableLight[7] = {true,true,true,true,true,true,true};

//Costruttore(pos)
Explosion::Explosion(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z)  {
	radius=1.5f;
	spriteframe=0;
	lightPos=1;
	deltal=0.0f;

	//Cerco una LIGHT# libera
	for(int i=0;i<7;i++){
		if(Explosion::availableLight[i]){
			availableLight[i]=false;
			lightPos = i+1;
			i=8;
		}
	}

	if(lightPos==1)
		myLight=GL_LIGHT1;
	else if(lightPos==2)
		myLight=GL_LIGHT2;
	else if(lightPos==3)
		myLight=GL_LIGHT3;
	else if(lightPos==4)
		myLight=GL_LIGHT4;
	else if(lightPos==5)
		myLight=GL_LIGHT5;
	else if(lightPos==6)
		myLight=GL_LIGHT6;
	else if(lightPos==7)
		myLight=GL_LIGHT7;

	cout << "Luce scelta " << lightPos << endl;

	//Attivo una nuova Luce
	GLfloat aLite[4] = { 0.0f, 0.0f, 0.0f, 1 };
	GLfloat dLite[4] = { deltal, deltal, 0.1f, 1 };
	GLfloat sLite[4] = { deltal, deltal, 0.1f, 1 };
	GLfloat PosLite[4] = { _X, _Y, _Z, 1 };
	glLightfv(myLight, GL_AMBIENT, aLite);
	glLightfv(myLight, GL_DIFFUSE, dLite);
	glLightfv(myLight, GL_SPECULAR, sLite);
	glLightfv(myLight, GL_POSITION, PosLite);

	glEnable(myLight);
}

//metodo per far avanzare l'animazione
void Explosion::processExplosion(int delta){
	//radius+=0.1f;
	spriteframe++;

	if(spriteframe<10)
		deltal+=0.09f;
	else
		deltal-=0.09f;

	GLfloat aLite[4] = { 0.0f, 0.0f, 0.0f, 1 };
	GLfloat dLite[4] = { deltal, deltal, 0.1f, 1 };
	GLfloat sLite[4] = { deltal, deltal, 0.1f, 1 };
	glLightfv(myLight, GL_AMBIENT, aLite);
	glLightfv(myLight, GL_DIFFUSE, dLite);
	glLightfv(myLight, GL_SPECULAR, sLite);


}

//determina se l'animazione dell'esplosione è finita
bool Explosion::isFinished(){
	if(spriteframe>19)return true;
	return false;

}

//Override del metodo di drawing
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

		//Applico la maschera per la trasparenza
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

		// Disegno la sprite vera e propria
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
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

	glPopMatrix();
};


Explosion::~Explosion() {
	glDisable(myLight);
	availableLight[lightPos]=true;
}

/*
 * main.cpp
 * ESPERIMENTI VARI
 *  Created on: 06/apr/2010
 *      Author: ziby
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>



void CambiaDim(int, int);
void DisegnaTutto();
void TastoPremuto(unsigned char, int, int);

using namespace std;

/**Classe che rappresenta un generico oggetto grafico*/
class Obj{

private:
	float X,Y,Z;
	float rX,rY,rZ;
	float vX,vY,vZ;
	float R;
public:
	//Costruttore senza parametri
	Obj(){
		X=0; Y=0; Z=-10; rX=rY=rZ=vX=vY=vZ=0;
		randomizeDimension();
		cout << "costruttore 0 param";
	};

	//Costruttore a 3 parametri (posizione)
	Obj(float _X,float _Y,float _Z){
		X=_X; Y=_Y; Z=_Z; rX=rY=rZ=vX=vY=vZ=0;
		randomizeDimension();
	};

	//Costruttore a 6 parametri (posizione+rotazione)
	Obj(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ){
		X=_X; Y=_Y; Z=_Z; rX=_rX; rY=_rY; rZ=_rZ; vX=vY=vZ=0;
		randomizeDimension();
	};

	//Costruttore a 6 parametri (posizione+rotazione+velocita)
	Obj(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ,float _vX,float _vY,float _vZ){
		X=_X; Y=_Y; Z=_Z; rX=_rX; rY=_rY; rZ=_rZ; vX=_vX; vY=_vY; vZ=_vZ;
		randomizeDimension();
	};

	void randomizeDimension(){
		R = (rand()%200+1)/100.0f;
	}

	void drawMe(){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glTranslatef(X,Y+R,Z);
		glRotatef(rX, 1, 0, 0);
		glRotatef(rY, 0, 1, 0);
		glRotatef(rZ, 0, 0, 1);

		glBegin(GL_QUADS);

			glColor3f(1, 0, 1);
			glVertex3f(R, R, R);
			glVertex3f(-R, R, R);
			glVertex3f(-R, -R, R);
			glVertex3f(R, -R, R);

			glColor3f(0, 0, 1);
			glVertex3f(-R, R, -R);
			glVertex3f(R, R, -R);
			glVertex3f(R, -R, -R);
			glVertex3f(-R, -R, -R);

			glColor3f(1, 1, 0);
			glVertex3f(R, R, -R);
			glVertex3f(R, R, R);
			glVertex3f(R, -R, R);
			glVertex3f(R, -R, -R);

			glColor3f(0.5f, 0, 1);
			glVertex3f(-R, R, R);
			glVertex3f(-R, R, -R);
			glVertex3f(-R, -R, -R);
			glVertex3f(-R, -R, R);

			glColor3f(0, 1, 1);
			glVertex3f(R, R, -R);
			glVertex3f(-R, R, -R);
			glVertex3f(-R, R, R);
			glVertex3f(R, R, R);

			glColor3f(1, 0, 0);
			glVertex3f(-R, -R, -R);
			glVertex3f(R, -R, -R);
			glVertex3f(R, -R, R);
			glVertex3f(-R, -R, R);
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

};

class DestructableObj: public Obj{

private:
	int life;

};

/*Classe logica che rappresenta i settori(quartieri) della cittadella*/
class Sector{

private:

	int X,Y,Z;
	int dimX,dimY,dimZ;
	vector<Obj*> buildings;

	float r,g,b;

public:
	//Costruttore
	Sector(int _X,int _Y,int _Z,int _dimX,int _dimY,int _dimZ){
		X=_X; Y=_Y; Z=_Z; dimX=_dimX; dimY=_dimY; dimZ=_dimZ;
		randomColor();
	}

	void randomColor(){
		r = (rand()%100)/100.0f;
		g = (rand()%100)/100.0f;
		b = (rand()%100)/100.0f;
	}

	//Metodo che aggiunge un edificio(riferimento) al settore
	void addBuilding(Obj* _newBuilding){
		buildings.push_back(_newBuilding);
	}

	void drawMe(){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

	    glTranslatef(X,Y,Z);

		glBegin(GL_QUADS);

			glColor3f(r, g, b);

			/*
			glVertex3f(-dimX, 0.1, -dimZ);
			glVertex3f(dimX, 0.1, -dimZ);
			glVertex3f(dimX, 0.1, dimZ);
			glVertex3f(-dimX, 0.1, dimZ);
	*/
			glVertex3f(0, 0.1, 0);
			glVertex3f(dimX, 0.1, 0);
			glVertex3f(dimX, 0.1, dimZ);
			glVertex3f(0, 0.1, dimZ);


		glEnd();

		glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

	}


};

/* ################################## GLOBALI ################################## */
/*Introdotto osservatore*/
Obj* myObjs;
vector<Obj> myObjCitadel;
vector<Sector*> myCitadel;

int dim_cit = 20;

/*############################################################################*/


//Osservatore...
float ossX, ossY, ossZ;
float ossA, ossB;
float pNear=0.5;

class cubo3d {

public:
	cubo3d() {X=0; Y=0; Z=-10; rX=rY=rZ=0;}; //costruttore

	//controllo
	void Muoviti(unsigned char t)
	{
		if(t == 's') X += 0.5f;
		if(t == 'a') X -= 0.5f;
		if(t == 'w') Y += 0.5f;
		if(t == 'z') Y -= 0.5f;
		if(t == 'y') Z += 0.5f;//
		if(t == 't') Z -= 0.5f;

		if(t == 'c') rZ += 10.0f;
		if(t == 'x') rZ -= 10.0f;
		if(t == 'p') rX += 10.0f;
		if(t == 'o') rX -= 10.0f;
		if(t == 'l') rY += 10.0f;
		if(t == 'k') rY -= 10.0f;
	}

	//vista
	void Disegnati()
	{
		//Da DisegnaTutto...
		glMatrixMode(GL_MODELVIEW);// -> lavora sulla matrice del modello
		glPushMatrix(); //salvo matrice (così posso disegnare il cubo disaccoppiato dal mondo

		//glEnable(GL_CULL_FACE);
		glTranslatef(X,Y,Z);
		glRotatef(rX, 1, 0, 0);
		glRotatef(rY, 0, 1, 0);
		glRotatef(rZ, 0, 0, 1);

		glBegin(GL_QUADS);
			/*	//faccia posteriore
				glColor3f(1, 0, 1);
				glVertex3f(-1,-1,1);
				glVertex3f(1,-1,1);
				glVertex3f(1,1,1);
				glVertex3f(-1,1,1);

				//prima faccia (davanti)
				glColor3f(1, 1, 0);
				glVertex3f(1,-1,-1);
				glVertex3f(-1,-1,-1);
				glVertex3f(-1,1,-1);
				glVertex3f(1,1,-1);
*/
		int R=1;
		glColor3f(1, 0, 1);
		glVertex3f(R, R, R);
		glVertex3f(-R, R, R);
		glVertex3f(-R, -R, R);
		glVertex3f(R, -R, R);

		glColor3f(0, 0, 1);
		glVertex3f(-R, R, -R);
		glVertex3f(R, R, -R);
		glVertex3f(R, -R, -R);
		glVertex3f(-R, -R, -R);

		glColor3f(1, 1, 0);
		glVertex3f(R, R, -R);
		glVertex3f(R, R, R);
		glVertex3f(R, -R, R);
		glVertex3f(R, -R, -R);

		glColor3f(0.5f, 0, 1);
		glVertex3f(-R, R, R);
		glVertex3f(-R, R, -R);
		glVertex3f(-R, -R, -R);
		glVertex3f(-R, -R, R);

		glColor3f(0, 1, 1);
		glVertex3f(R, R, -R);
		glVertex3f(-R, R, -R);
		glVertex3f(-R, R, R);
		glVertex3f(R, R, R);

		glColor3f(1, 0, 0);
		glVertex3f(-R, -R, -R);
		glVertex3f(R, -R, -R);
		glVertex3f(R, -R, R);
		glVertex3f(-R, -R, R);

		glEnd();

		//Da disegnaQuadrato/cubo
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

		//mio: Gli assi del cubo
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex3f(-1.5f,0,0);
		glVertex3f(1.5f,0,0);

		glVertex3f(0,0,-1.5f);
		glVertex3f(0,0,1.5f);

		glVertex3f(0,-1.5f,0);
		glVertex3f(0,1.5f,0);
		glEnd();


		glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto
	}

	//private:
	//Modello
	float X;
	float Y;
	float Z;
	float rX,rY,rZ;

};

//Oggetto cubo
cubo3d Cubo;
cubo3d Cubo2;


//Linko le funzioni..
void TastoPremuto(unsigned char t, int, int)
{

	//Leggo eventuali CTRL,ALT..
	int mod = glutGetModifiers();

	if(t == 'm') ossZ -= 0.1f;
	if(t == 'n') ossZ += 0.1f;
	if(t == '.') ossX -= 0.1f;
	if(t == ',') ossX += 0.1f;
	if(t == '1') ossY -= 0.1f;
	if(t == '2') ossY += 0.1f;

	if(t == 'v') ossA -= 2;
	if(t == 'b') ossA += 2;

	if(t == 'g') ossB -= 2;
	if(t == 'h') ossB += 2;

	//cambiare angolo focale (piano near)
	/*  if(t == '1') pNear *= 1.1f;
    if(t == '2') pNear *= 0.9f;
	 */
	//Aggiunti al volo per gestire i due cubi..da fart meglio
	if(t == '4') Cubo.X -= 0.1f;
	if(t == '5') Cubo.X += 0.1f;
	if(t == '7') Cubo2.X -= 0.1f;
	if(t == '8') Cubo2.X += 0.1f;

	if(t == 27) exit(0);

	/*	if(t == 'q'){
		if(glutGetModifiers() == GLUT_ACTIVE_CTRL)
		exit(0);
	}
	 */
	Cubo.Muoviti(t);

	glutPostRedisplay();		//richiesta di ridisegnare la finestra
}



void CambiaDim(int w, int h)
{
	glViewport(0,0,w,h);
	//glViewport(0,100,w,h);
}

//void gira(int value=0){
void gira(){
	Cubo.rX -= 0.1f;
	Cubo.Disegnati();
	glutPostRedisplay();
	//glutTimerFunc(33,gira,1);
	glutIdleFunc(gira);
}

void DisegnaTutto()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); //-> lavora sulla matrice di proiezione
	glLoadIdentity();
	//glOrtho(-4,4,-4,4, -1,1); //non più questa, vogliamo una trasformazione PROSPETTICA!

	//glFrustum(-0.25f, 0.25f, -0.25f, 0.25f,  pNear,2000);
	glFrustum(-0.4f, 0.4f, -0.25f, 0.25f,  pNear,2000);
	//IMPORTANTE
	//i primi 4 parametri individuano l'apetura sul piano "near"
	//gli ultimi due sono: la distanza dal piano near, la distanza dal piano far

	/*Devo mantenere le "proporzioni" dello schermo, per evitare lo stretch delle immagini!!!!
	  Ad esempio con 1280x800 , x = 1.6 y
	 */


	//Carico la matrice identità,(blocca il pavimento)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Osservatore
	glRotatef(-ossB, 1, 0, 0); //imp per prima..
	glRotatef(-ossA, 0, 1, 0); //imp
	glTranslatef(-ossX,-ossY,-ossZ);
	//glPushMatrix();//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SALVO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//Pavimento..
	float a;
	glColor3f(0.0f, 0.8f, 0.0f);
	int ypos = 0;

	glBegin(GL_LINES);
		for(a=-100; a<100; a+= 0.5f)
		{
			glVertex3f(a,ypos,-100);
			glVertex3f(a,ypos,100);
		}
		for(a=-100; a<100; a+= 0.5f)
		{
			glVertex3f(-100,ypos,a);
			glVertex3f(100,ypos,a);
		}

		//limiti della cittadella
		glColor3f(0.6f, 0.8f, 0.5f);
		for(a=-16; a<16; a+= 0.2f)
		{
			glVertex3f(a,ypos,-60);
			glVertex3f(a,ypos,-20);
		}
		for(a=-20; a<-60; a-= 0.2f)
		{
			glVertex3f(-15,ypos,a);
			glVertex3f(15,ypos,a);
		}
	glEnd();


	glColor3f(1,0,0);
	Cubo.Disegnati();


	//Disegno settori

	for(int i=0; i< myCitadel.size();i++){
		myCitadel.at(i)->drawMe();

	}



	//Disegno cittadella (TMP)
	glColor3f(1,0,1);
	for(int i=0;i<dim_cit;i++)
		myObjCitadel.at(i).drawMe();

	//glutSolidOctahedron();
	//glutSolidTetrahedron();
	//glutSolidTeapot(0.2f);

	glutSwapBuffers();
	//disegnaBarra();

}


void MuoviMouse (int button, int state, int x, int y){
	//	buttons[button] = state;
	Cubo.X = x;
	Cubo.Y = y;

}

void processMouseActiveMotion(int x, int y){
	Cubo.X = (x-640)/80;
	Cubo.Y = (-y+400)/50;
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);		//inizializzo il sistema glut con gli stessi parametri del main
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	/* Per l'avvio in modalità finestra */
	/*
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(550, 550);
	glutCreateWindow("Difesa delle cittadella - Stefano Bonetta");
	 */
	//glutFullScreen();

	/*Avvio in fullscreen*/
	glutInitWindowSize(1280, 800);
	glutGameModeString("1280x800:16");
	glutEnterGameMode();



	glutReshapeFunc(CambiaDim);
	glutDisplayFunc(DisegnaTutto);
	glutKeyboardFunc(TastoPremuto);

	//Cattura movimenti mouse

	glutMouseFunc(MuoviMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMouseActiveMotion);

	glEnable(GL_DEPTH_TEST); //abilita zbuffer
	glEnable(GL_CULL_FACE);

	//Toglie il cursore
	glutSetCursor(GLUT_CURSOR_NONE);

	//glutTimerFunc(33,gira,1);
	glutIdleFunc(gira);

	/* initialize random seed: */
	srand ( time(NULL) );


	//myObjs = new Obj[dim_cit];



	/* Settori della città
	 *
	 * 1  2  3
	 * 4  5  6
	 *
	 */
	int maxX = 30;
/*
	for(int i=0;i<6;i++){
		int myX = rand() % 20 +1;

		Sector* newSect = new Sector();
		//myCitadel.push_back()
	}
*/
	myCitadel.push_back(new Sector(-15,0,-40, 20,0,-40));
	myCitadel.push_back(new Sector(  5,0,-40,  5,0,-20));
	myCitadel.push_back(new Sector( 10,0,-40,  5,0,-30));

	myCitadel.push_back(new Sector(-15,0,-20,  5,0,-20));
	myCitadel.push_back(new Sector(-10,0,-25, 15,0,-15));
	myCitadel.push_back(new Sector( 5,0,-30,   10,0,-10));


	//Crea la cittadella in modo casuale
	for(int i=0; i < dim_cit ;i++){

	  int meno;
	  if(rand()%2 == 0)meno=-1;
	  else meno=1;

	  int myX = (rand() % 15 + 1)*meno;
	  int myZ = rand() % 40 + 20;
	  int myrY = rand() % 360;

	  //myObjs[i] = Obj(myX,0,-1*myZ,0,myrY,0);
	  myObjCitadel.push_back(Obj(myX,0,-1*myZ,0,myrY,0));

	}

	//Posizione iniziale dell'osservatore
	ossY=10;
	ossZ=0;
	ossX=0;
	ossB=-16;

	glutMainLoop();
	return(0);
}

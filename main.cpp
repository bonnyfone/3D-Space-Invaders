/*
 * main.cpp
 * Difesa della Cittadella
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

#include "Obj.h"
#include "Sector.h"
#include "Building.h"
#include "Bomb.h"
#include "Cannon.h"

void CambiaDim(int, int);
void DisegnaTutto();
void TastoPremuto(unsigned char, int, int);

using namespace std;


/* ################################## GLOBALI ################################## */
/*Introdotto osservatore*/
Obj* myObjs;
vector<Obj> myObjCitadel;
vector<Sector*> myCitadel;
vector<Bomb*> myBombs;
Cannon* myCannon;
long delta_t;
int sectors=6;


//Array globale per le luce
GLfloat PosLite[4]={2,2,2,1};
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

//CALLBACK per l'evoluzione del gioco
void Progress(){
	Cubo.rX -= 0.1f;
	Cubo.Disegnati();

	//Check bombe
	for(register unsigned int i=0;i<myBombs.size();i++){
		myBombs.at(i)->move(glutGet(GLUT_ELAPSED_TIME)-delta_t);
		if(bool coll=myBombs.at(i)->checkCollision() || myBombs.at(i)->getY() <= 0){
			Bomb* check = myBombs.at(i);
			myBombs.erase(myBombs.begin()+i);

			check->clearRef();
			delete check;
			i--;
		}
	}

	/* Nuove bombe totalmente casuali */

	/*register int meno=1;
	if(rand()%2 ==0)meno=-1;
	register unsigned int newbombs = rand() % 35;
	if(newbombs >=30) myBombs.push_back(new Bomb(meno*rand()%15,20,-rand()%50));
	*/

	/* Nuove bombe su edifici casuali */
	register unsigned int newbombs = rand() % 30;
	if(newbombs >=27){
		register int quarter = rand()%6;
		//register int randomBuilding =
		Sector* tmpSector = myCitadel.at(quarter);
		Building* tmpBuilding = tmpSector->getRandomBuilding();
		if(tmpBuilding){
			Bomb* newBomb = new Bomb(tmpBuilding->getX(),20,tmpBuilding->getZ(),  tmpSector,tmpBuilding);
			myBombs.push_back(newBomb);
		}
	}

	//Aggiorno il tempo
	delta_t = glutGet(GLUT_ELAPSED_TIME);

	glutPostRedisplay();
	//glutTimerFunc(33,gira,1);
	//glutIdleFunc(gira);
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Illuminazione
	/*
		GLfloat aLite[4] = {0.2, 0.2, 0.2, 1};
		GLfloat dLite[4] = {0.8, 0.8, 0.8, 1};
		GLfloat sLite[4] = {0.8, 0.8, 0.8, 1};

		glLightfv(GL_LIGHT0, GL_AMBIENT, aLite);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dLite);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sLite);

	    glLightfv(GL_LIGHT0, GL_POSITION, PosLite);
	 */
	//Osservatore
	glRotatef(-ossB, 1, 0, 0); //imp per prima..
	glRotatef(-ossA, 0, 1, 0); //imp
	glTranslatef(-ossX,-ossY,-ossZ);
	//glPushMatrix();//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SALVO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//cannone
	myCannon->drawMe();

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
		/*
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
		*/
	glEnd();


	glColor3f(1,0,0);
	Cubo.Disegnati();

	//Disegno settori
	for(register unsigned int i=0; i< myCitadel.size();i++){
		if(i>2) myCitadel.at(i)->drawMe(1);
		else    myCitadel.at(i)->drawMe(0);
	}

	//Disegno cittadella
	glColor3f(1,0,1);
	for(register unsigned int i=0;i<myCitadel.size();i++){
		myCitadel.at(i)->drawBuildings();
	}

	//Disegna strade
	int halfSect = myCitadel.size()/2;

	int roadA = 0;
	int roadB = 0;
	float roadY = 0.06f;

	for(int j=0;j<halfSect;j++){
		roadA +=  myCitadel.at(j)->getDimX();
		roadB +=  myCitadel.at(j+halfSect)->getDimX();
		if(j<halfSect-1){
			int interRoadUp   = max( myCitadel.at(j)->getDimZ(),myCitadel.at(j+1)->getDimZ() );
			int interRoadDown = max( myCitadel.at(j+halfSect)->getDimZ(),myCitadel.at(j+halfSect+1)->getDimZ() );

			glPushMatrix();
			glTranslatef(myCitadel.at(j+1)->getX()-0.25f,0,-40);
			glBegin(GL_QUADS);
				//Quartieri alti
				glColor3f(0, 0, 0);
				glVertex3f(0, roadY, 0);
				glVertex3f(0.5f, roadY, 0);
				glVertex3f(0.5f, roadY, -1*interRoadUp);
				glVertex3f(0, roadY, -1*interRoadUp);
			glEnd();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(myCitadel.at(j+halfSect+1)->getX()-0.25f,0,-40);
			glBegin(GL_QUADS);
				//Quartieri bassi
				glColor3f(0, 0, 0);
				glVertex3f(0, roadY, 0);
				glVertex3f(0, roadY, interRoadDown);
				glVertex3f(0.5f, roadY, interRoadDown);
				glVertex3f(0.5f, roadY, 0);
			glEnd();
			glPopMatrix();
		}
	}
	int road = max(roadA,roadB);
	glPushMatrix();
	glTranslatef(-15,0,-39.5f);

	glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex3f(0, roadY, 0);
		glVertex3f(road, roadY, 0);
		glVertex3f(road, roadY, -0.5f);
		glVertex3f(0, roadY, -0.5f);
	glEnd();
	glPopMatrix();

	//Bombe (TMP)
	for(register unsigned int i=0; i< myBombs.size(); i++)
		myBombs.at(i)->drawMe();

	glutSwapBuffers();
}


void MuoviMouse (int button, int state, int x, int y){
	//	buttons[button] = state;
	Cubo.X = x;
	Cubo.Y = y;

}

void processTimedOperation(int i=0){
	myCannon->targetingAnimation();
	glutTimerFunc(30,processTimedOperation,1);
}

void processMouseActiveMotion(int x, int y){

	//Cubo.X = (x-640)/80;
	//Cubo.Y = (-y+400)/50;
	cout<< "Mouse pos (x,y):"<< x << "," <<y <<endl;

	register float halfScreen = 640.0f;
	register float myVal = ((x-halfScreen)/halfScreen);
	register float angle = acos(myVal)*180.0f/3.14f - 90.0f;
	angle=angle /100*80;
	cout << "Mouse acos in gradi = " << angle << endl;

	myCannon->setrZ(angle);



	halfScreen = 400.0f;
	myVal = ((y-halfScreen)/halfScreen);
	angle = acos(myVal)*180.0f/3.14f - 180.0f;
	angle=min(-30.0f,angle /100*70);
	cout << "Mouse acos in gradi = " << angle << endl;

	myCannon->setrX(angle);

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

	//Illuminazione
	/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat black[4]= {0,0,0,1};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	 */

	//Toglie il cursore
	glutSetCursor(GLUT_CURSOR_NONE);

	glutTimerFunc(50,processTimedOperation,1);
	glutIdleFunc(Progress);

	/* initialize random seed: */
	srand ( time(NULL) );


	/* Settori della città
	 *
	 * 1  2  3
	 * 4  5  6
	 *
	 */
	int maxX = 30;

	//coord x da cui partire a generare i settori
	int startX = -15;
	//asse centrale della citta
	int middle = -40;
	//estensione della città
	int citysize = 30;
	//max altezza settore
	int sectorH = 25;

	int sectorPerLine = 3;

	int xIterator = startX;
	int yIterator = citysize;


	/*
	 * Costruisco i quartieri con coordinate assolute, questo mi facilita la gestione di eventi
	 * che si verificano lungo i confini tra i vari quartieri e all'interno di essi
     */
	cout<< "## Building city... "<<endl;
	for(int j=0; j<sectorPerLine*2; j++){

		if(j==sectorPerLine){
			xIterator = startX;
			yIterator = citysize;
		}

		int myWidth;
		if(j==sectorPerLine-1 || j==sectorPerLine*2 -1)
			{
				myWidth  =  citysize/2 - xIterator;
				if(myWidth<=0)myWidth=7;
			}
		else
			 myWidth  =  min(11,max(rand() % max((yIterator-7),1),7));
			 //myWidth  =  min(10,max(rand() % max((yIterator-5) + 5,1),5));


		int myHeight =  max(rand() % max((sectorH-7),1),7);

		//Creo il settore
		Sector* newSector = new Sector(xIterator,0,middle, myWidth,0,myHeight);

		//Creo degli edifici nel settore (un numero casuale, scalato in base alle dimensioni del settore)
		int limiter = (myWidth * myHeight)/10;
		int toBuild = rand()%limiter + 1;

		int meno=1;
		if(j>2)
			meno=-1;

		for(int k=0; k < toBuild; k++){
			int relPosX = (rand() % max((myWidth-6),1))+3 + newSector->getX();
			int relPosZ = meno*((rand() % max((myHeight-6),1))+3) - newSector->getZ(); //<<<<<<<<<<<< DA AGGIUSTARE PER NON FAR SFORARE GLI EDIFICI
			int myrY = rand() % 360;

			Building* newBuilding = new Building(relPosX,0,-1*relPosZ, 0,myrY,0);
			newSector->addBuilding(newBuilding);
			//myObjCitadel.push_back(*newBuilding);
		}
		cout<< "\n Limiter   for sector " << j << " : " << limiter << endl;
		cout<< " Effective for sector " << j << " : " << toBuild << endl;


		//Aggiungo settore alla cittadella
		myCitadel.push_back(newSector);

		xIterator += myWidth;
		yIterator -= myWidth;
	}

	myCannon = new Cannon();


	/*
	//Bombe (TMP da modificare, devono crearsi dinamicamente mentre si gioca)
	for(int i = 0;i<10;i++){
		int meno=1;
		if(rand()%2 ==0)meno=-1;

		Bomb* myBomb = new Bomb(meno*rand()%15,20,-rand()%50);
		myBombs.push_back(myBomb);
		cout << " bomba " << myBomb->getX() << " " << myBomb->getY() << " " << myBomb->getZ() << endl;
	}*/

	//Posizione iniziale dell'osservatore
	ossY=14;
	ossZ=0;
	ossX=0;
	ossB=-24;

	delta_t= glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return(0);
}

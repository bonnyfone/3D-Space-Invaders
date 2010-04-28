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
#include <string.h>
#include <sstream>
#include "Obj.h"
#include "Sector.h"
#include "Building.h"
#include "Bomb.h"
#include "Cannon.h"
#include "Projectile.h"
#include "Explosion.h"


void CambiaDim(int, int);
void DrawScene();
void TastoPremuto(unsigned char, int, int);

using namespace std;


/* ################################## GLOBALI ################################## */
float recoil;
float recoilTime;
float life;
float initial;
int score;
char stringscore[32];
float gametime;
float timecoeff;
vector<Sector*> myCitadel;
vector<Bomb*> myBombs;
vector<Projectile*> myAmmo;
vector<Explosion*>myExplosions;
Cannon* myCannon;


const float PI = 3.14159265;
long delta_t;
int sectors=6;


//Array globale per le luce
//GLfloat PosLite[4]={2,2,2,1};
int dim_cit = 20;

/*  TEXTURE  */
vector<GLubyte*> Textures;

//Osservatore...
float ossX, ossY, ossZ;
float ossA, ossB;
float pNear=0.5;

/*############################################################################*/


//Linko le funzioni..
void TastoPremuto(unsigned char t, int, int)
{

	//Leggo eventuali CTRL,ALT..


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


	if(t == 27) exit(0);

	if(t == 'x') myCannon->swapTargetingEnabled();
	/*	if(t == 'q'){
		if(glutGetModifiers() == GLUT_ACTIVE_CTRL)
		exit(0);
	}
	 */

	glutPostRedisplay();		//richiesta di ridisegnare la finestra
}

void clearMaterial(){
	//Variabili per definire materiali
	GLfloat ambiente[4] =  { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat direttiva[4] =  { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat brillante[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//glMateriali(GL_FRONT, GL_SHININESS, 32);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
}

//Disegna una scritta (BitmapMode)
void printBitmapString(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

//Disegna una scritta (StrokeMode)
void printStrokeString(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(font, *s);
         s++;
      }
   }
}

void updateScore(int delta){
	score += delta;
	sprintf(stringscore,"%d",score); // string result '65' is stored in char array cVal
}


void CambiaDim(int w, int h)
{
	glViewport(0,0,w,h);
	//glViewport(0,100,w,h);
}

/*#################### CALLBACK progress del gioco #####################*/
void Progress(){

	//Life check
	life=0;
	for(register unsigned int i=0; i<myCitadel.size();i++){
		life+=myCitadel.at(i)->getBuildingsLife();
	}
	if(life==0){/* GAME OVER*/}

	//Ammo collision
	register float impactDistance = 1.2f;
	register float distance;
	for(register unsigned int i=0;i<myAmmo.size();i++){
		myAmmo.at(i)->move(glutGet(GLUT_ELAPSED_TIME)-delta_t);
		register bool die=false;
		for(register unsigned int j=0;j<myBombs.size();j++){
			distance = pow(myAmmo.at(i)->getX() - myBombs.at(j)->getX(),2) + pow(myAmmo.at(i)->getY() - myBombs.at(j)->getY(),2) + pow(myAmmo.at(i)->getZ() - myBombs.at(j)->getZ(),2);
			distance = sqrt(distance);
			if(distance <=impactDistance){
				myExplosions.push_back(new Explosion(myAmmo.at(i)->getX(),myAmmo.at(i)->getY(),myAmmo.at(i)->getZ()));
				delete myBombs.at(j);
				delete myAmmo.at(i);
				myBombs.erase(myBombs.begin()+j);
				myAmmo.erase(myAmmo.begin()+i);
				j = myBombs.size();
				i--;
				die=true;
				updateScore(5);
			}
		}

		if(!die && myAmmo.at(i)->getZ() <= -110){
			delete myAmmo.at(i);
			myAmmo.erase(myAmmo.begin()+i);
			i--;
		}
	}


	//Collision bombe->edifici
	for(register unsigned int i=0;i<myBombs.size();i++){
		myBombs.at(i)->move(glutGet(GLUT_ELAPSED_TIME)-delta_t);
		if(bool coll=myBombs.at(i)->checkCollision() || myBombs.at(i)->getY() <= 0){
			Bomb* check = myBombs.at(i);
			myBombs.erase(myBombs.begin()+i);

			//Aggiorno vita
			if(coll)life-=0.5f;

			//Aggiungo explosione
			myExplosions.push_back(new Explosion(check->getX(),check->getY()+check->getDimY(),check->getZ()));

			check->clearRef();
			delete check;
			i--;
		}
	}

	//Gestione esplosioni
	for(register unsigned int i=0;i<myExplosions.size();i++){
		myExplosions.at(i)->processExplosion(glutGet(GLUT_ELAPSED_TIME)-delta_t);
		if(myExplosions.at(i)->isFinished()){
			delete myExplosions.at(i);
			myExplosions.erase(myExplosions.begin()+i);
			i--;
		}

	}


	/* Nuove bombe su edifici casuali */
	register unsigned int newbombs = rand() % 100;
	if(myBombs.size()<=5 && newbombs >=95){
		register int quarter = rand()%6;
		//register int randomBuilding =
		Sector* tmpSector = myCitadel.at(quarter);
		Building* tmpBuilding = tmpSector->getRandomBuilding();
		if(tmpBuilding){
			Bomb* newBomb = new Bomb(tmpBuilding->getX(),25,tmpBuilding->getZ(),  tmpSector,tmpBuilding);
			myBombs.push_back(newBomb);
		}
	}

	//Aggiorno il tempo
	delta_t = glutGet(GLUT_ELAPSED_TIME);

	glutPostRedisplay();
}

/*################## CALLBACK di visualizzazione ##################*/
void DrawScene()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); //-> lavora sulla matrice di proiezione
	glLoadIdentity();

	glFrustum(-0.4f, 0.4f, -0.25f, 0.25f,  pNear,2000);
	//i primi 4 parametri individuano l'apetura sul piano "near"
	//gli ultimi due sono: la distanza dal piano near, la distanza dal piano far

	/*Devo mantenere le "proporzioni" dello schermo, per evitare lo stretch delle immagini!!!!
	  Ad esempio con 1280x800 , x = 1.6 y
	 */

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//Osservatore
	glRotatef(-ossB, 1, 0, 0); //imp per prima..
	glRotatef(-ossA, 0, 1, 0); //imp
	glTranslatef(-ossX,-ossY,-ossZ);
	//glPushMatrix();//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SALVO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//Luce
	GLfloat aLite[4] = { 0.3f, 0.3f, 0.3f, 1 };
	GLfloat dLite[4] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat sLite[4] = { 1.0f, 1.0f, 1.0f, 1 };

	//Fonte di luce in alto a dx (simula la luna?)
	GLfloat PosLite[4] = { 30.0f, 15.0f, -50.0f, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, aLite);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dLite);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sLite);
	glLightfv(GL_LIGHT0, GL_POSITION, PosLite);


	//Variabili per definire materiali
	GLfloat ambiente[4] = { 0.8f, 0.8f, 0.6f, 1 };
	GLfloat direttiva[4] = { 0.7f, 0.7f, 0.7f, 1 };
	GLfloat brillante[4] = { 0.8f, 0.8f, 0.8f, 1 };

	//Luna
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
		glPushMatrix();

		glMateriali(GL_FRONT, GL_SHININESS, 32);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

		glTranslatef(45,20,-80);
		glColor3f(0.8f,0.8f,0.7f);
		glutSolidSphere(5,50,50);
		glPopMatrix();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//cannone
	clearMaterial();
	myCannon->drawMe();

	//Pavimento..
	register float a,z,delta;
	delta=7.0f;
	register int c;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 3);

	//Terreno
	clearMaterial();
	for(a=-80; a<80; a+=delta)
	{
		glBegin(GL_QUAD_STRIP);
		for(c=0, z=5; z> -110; z-=delta,c++){

				if(c%2 == 0)glTexCoord2f(0,0);
				else glTexCoord2f(0,1);

				glVertex3f(a,0,z);

				if(c%2 == 0)glTexCoord2f(1,0);
				else glTexCoord2f(1,1);

				glVertex3f(a+delta,0,z);
		}
		glEnd();
	}

	//Cielo
	glBindTexture(GL_TEXTURE_2D, 5);
	glBegin(GL_QUADS);
	 for(int i=0;i<3;i++){
			glTexCoord2f(0,1);
			glVertex3f(-120+i*80,0,-100);

			glTexCoord2f(1,1);
			glVertex3f(-120+(i+1)*80,0,-100);

			glTexCoord2f(1,0);
			glVertex3f(-120+(i+1)*80,40,-100);

			glTexCoord2f(0,0);
			glVertex3f(-120+i*80,40,-100);
	 }
	glEnd();
	glDisable(GL_TEXTURE_2D);


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

	//Proiettili (TMP)
	for(register unsigned int i=0; i< myAmmo.size(); i++)
		myAmmo.at(i)->drawMe();

	//Esplosioni
	for(register unsigned int i=0; i< myExplosions.size(); i++){
		myExplosions.at(i)->drawMe();
	}


    /* ###############  2D WIDGET  ################# */
	//glPushMatrix();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400,400, -300,300, -1,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	register float posX  =-360.0f;
	register float posY  =-290.0f;
	register float size = 100.0f;

	//Contenitori
	clearMaterial();
	//Sx
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef (posX, posY, -0.1);
		glBindTexture(GL_TEXTURE_2D, 11);
		glBegin(GL_QUADS);
				glNormal3f(1,0,0);
				glTexCoord2f(0,1);
				glVertex2f(-45.0f, -20.0f);
				glTexCoord2f(0,0);
				glVertex2f(-45.0f, 85.0f);
				glTexCoord2f(0.7f,0);
				glVertex2f(size+55, 85.0f);
				glTexCoord2f(1,1);
				glVertex2f(size+155, -20.0f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, 10);
		glBegin(GL_QUADS);
				glNormal3f(1,0,0);
				glTexCoord2f(0,1);
				glVertex2f(-45.0f, -20.0f);
				glTexCoord2f(0,0);
				glVertex2f(-45.0f, 80.0f);
				glTexCoord2f(0.7f,0);
				glVertex2f(size+50, 80.0f);
				glTexCoord2f(1,1);
				glVertex2f(size+150, -20.0f);
		glEnd();
	glPopMatrix();

	//Dx
	posX=360.0f;
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef (posX, posY, -0.1);
		glBindTexture(GL_TEXTURE_2D, 11);
		glBegin(GL_QUADS);
				glNormal3f(-1,0,0);
				glTexCoord2f(0,1);
				glVertex2f(45.0f, -20.0f);
				glTexCoord2f(0,0);
				glVertex2f(45.0f, 85.0f);
				glTexCoord2f(0.7f,0);
				glVertex2f(-size-55, 85.0f);
				glTexCoord2f(1,1);
				glVertex2f(-size-155, -20.0f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, 10);
		glBegin(GL_QUADS);
				glNormal3f(-1,0,0);
				glTexCoord2f(0,1);
				glVertex2f(45.0f, -20.0f);
				glTexCoord2f(0,0);
				glVertex2f(45.0f, 80.0f);
				glTexCoord2f(0.7f,0);
				glVertex2f(-size-50, 80.0f);
				glTexCoord2f(1,1);
				glVertex2f(-size-150, -20.0f);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	//Vita
	posX=-360.0f;
	size=80.0f;
	glPushMatrix();
		glTranslatef (posX, posY, 0.0);
		glBegin(GL_QUADS);
			glColor3f(0.1f,0.1f,0.1f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.0f, 20.0f);
			glVertex2f(size, 20.0f);
			glVertex2f(size, 0.0f);

			glColor3f(0.1f,0.9f,0.1f);
			glVertex2f(5.0f, 3.0f);
			glVertex2f(5.0f, 17.0f);
			glVertex2f(5.0f+(size-10.0f)*life/initial, 17.0f);
			glVertex2f(5.0f+(size-10.0f)*life/initial, 3.0f);
		glEnd();

		glRasterPos2f(-30,5);
		printBitmapString(GLUT_BITMAP_HELVETICA_18,"LIFE");
	glPopMatrix();

	//Tempo
	posY = -250.0f;
	glPushMatrix();
		glTranslatef (posX, posY, 0.0);
		glBegin(GL_QUADS);

			glColor3f(0.1f,0.1f,0.1f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.0f, 20.0f);
			glVertex2f(size, 20.0f);
			glVertex2f(size, 0.0f);

			glColor3f(0.2f,0.7f,0.7f);
			glVertex2f(5.0f, 3.0f);
			glVertex2f(5.0f, 17.0f);
			glVertex2f(5.0f+(size-10.0f)*gametime/(initial*timecoeff), 17.0f);
			glVertex2f(5.0f+(size-10.0f)*gametime/(initial*timecoeff), 3.0f);
		glEnd();

		glRasterPos2f(-32,5);
		printBitmapString(GLUT_BITMAP_HELVETICA_18,"TIME");
	glPopMatrix();

	//Score
	posX=-260.0f;
	glPushMatrix();
		glTranslatef (posX, posY, 0.0);
		glColor3f(0.7f,0.7f,0.1f);
		glRasterPos2f(0,5);
		printBitmapString(GLUT_BITMAP_HELVETICA_18,"SCORE");
		glRasterPos2f(6,-20);
		printBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,stringscore);
	glPopMatrix();

	//InfoCannone
	/*
	 posX=260.0f;
	glPushMatrix();
		glTranslatef (posX, posY, 0.1);
		glColor3f(0.7f,0.7f,0.1f);
		glutWireSphere(10,40,40);
		glutSolidSphere(10,40,40);

	glPopMatrix();
	 */

	//Recoil
	posX=320.0f;
	posY=-240.0f;
	size=50;
	glPushMatrix();
		glTranslatef (posX, posY, 0.1);
		glBegin(GL_QUADS);
			glColor3f(0.1f,0.1f,0.1f);
			glVertex2f(15.0f, 0.0f);
			glVertex2f(15.0f, -size);
			glVertex2f(45.0f, -size);
			glVertex2f(45.0f, 0.0f);

			//glColor3f(1/recoil,1-(1/recoil),0.1f);
			glColor3f(1/recoil,0.1f,0.1f);
			glVertex2f(20.0f, -5.0f);
			glVertex2f(20.0f, -size+5);
			glVertex2f(40.0f, -size+5);
			glVertex2f(40.0f, -5.0f);
		glEnd();

		glColor3f(0.8f,0.1f,0.1f);
		glRasterPos2f(10,13);
		printBitmapString(GLUT_BITMAP_HELVETICA_18,"RECOIL");

	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//glPopMatrix();

	glutSwapBuffers();
}


//CALLBACK gestione azioni del mouse
void processMouseAction (int button, int state, int x, int y){
	//	buttons[button] = state;

	if(recoil >=10.0f && button==0 && state ==0){//singolo mouseClickDown
		recoil=0.0f;
		cout << "Sparato!!"<<endl;

		//Fattore di spostamento trasversale (vX)
		register float cosZ = -cos((myCannon->getrZ()+90.0f) /180.0f*PI);

		//Velocità di movimento lungo asse z (vZ)
		register float sinZ =  sin((myCannon->getrZ()+90.0f) /180.0f*PI);

		//Fattore di spostamento verticale (vY)

		register float sinX = sin((myCannon->getrX()+90.0f) /180.0f*PI);
		register float cosX = cos((myCannon->getrX()) /180.0f*PI);

		//cout << "Debug: angolo=" <<  myCannon->getrX()+90.0f << "  rad= " << ((myCannon->getrX()+90.0f) /180.0f*PI)<< "  sin=" << sinX << endl;
		//cout << "Projectile angle,cos:" <<myCannon->getrZ()+90.0f <<" "<< cosZ << endl;
		//myAmmo.push_back(new Projectile(myCannon->getX(),myCannon->getY(),myCannon->getZ(), cosZ+(1-senZ)/2,cosX+(1-senX)/2,senZ));
		//cout << "Debug sinZ " << senZ << endl;
		register float vZ = (sinX>=0) ? sinX : -sinX; //max(sinX,-sinX);
		//cout << "Debug VZ " << vZ << "   asasd " << sinZ-vZ << endl;
		//cout << "Debug cosX " << vZ << "   cosX " << cosX << endl;

		//myAmmo.push_back(new Projectile(myCannon->getX(),myCannon->getY(),myCannon->getZ(),  cosZ,-sinX, senZ-vZ));
		//myAmmo.push_back(new Projectile(myCannon->getX(),myCannon->getY(),myCannon->getZ(),  cosZ,-sinX, sqrt(pow(1-pow(sinX,2),2) - pow(cosZ,2)) ));
		//cout << "Debug zzz " << sqrt( pow(sinZ,2)-pow(sinX,2) ) << endl;
		//myAmmo.push_back(new Projectile(myCannon->getX(),myCannon->getY(),myCannon->getZ(),  cosZ,-sinX, sqrt( pow(sinZ,2)-pow(sinX*(1-cosZ),2) ) ));
		myAmmo.push_back(new Projectile(myCannon->getX(),myCannon->getY(),myCannon->getZ(),  cosZ,-sinX, sinZ ));
		/* Volendo, si dovrebbe migliorare le precisione del calcolo della vZ*/
	}

}

void processTimedOperation(int i=0){
	gametime -= 0.1f;
	myCannon->targetingAnimation();
	if(recoil < recoilTime)recoil += 1.0f;

	glutTimerFunc(30,processTimedOperation,1);
}

void processMouseActiveMotion(int x, int y){

	//Cubo.X = (x-640)/80;
	//Cubo.Y = (-y+400)/50;
	//Muove il cannone
	cout<< "Mouse pos (x,y):"<< x << "," <<y <<endl;

	register float halfScreen = 640.0f;
	register float myVal = ((x-halfScreen)/halfScreen);
	register float angle = acos(myVal)*180.0f/PI - 90.0f;
	//angle=angle /100*80;
	cout << "Mouse acos in gradi = " << angle << endl;

	myCannon->setrZ(angle);



	halfScreen = 400.0f;
	myVal = ((y-halfScreen)/halfScreen);
	angle = acos(myVal)*180.0f/PI - 180.0f;
	//angle=min(-30.0f,angle /100*70);
	//angle=angle /100*80;

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
	glutDisplayFunc(DrawScene);
	glutKeyboardFunc(TastoPremuto);

	//Cattura movimenti mouse

	glutMouseFunc(processMouseAction);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMouseActiveMotion);


	/* Zbuffer ed smartdrawing */
	glEnable(GL_DEPTH_TEST); //abilita zbuffer
	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	GLfloat black[4] = { 0.0f, 0.0f, 0.0f, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);


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

	//Inizializzazioni varie

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

	life=0;
	score=0;
	updateScore(0);
	gametime=0;
	timecoeff=20.0f;
	recoil=0.0f;
	recoilTime=20.0f;

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
			life+=newBuilding->getL();
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
	initial=life;
	gametime=life*timecoeff;

	myCannon = new Cannon();

	//Carica le texture
	{
			int randFloor = rand()%3;
			GLubyte Texture1[256 * 256 * 3];
			FILE *fHan = fopen("img/metal4.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture1, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture2[256 * 256 * 3];
			fHan = fopen("img/sector2.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture2, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture3[256 * 256 * 3];
			fHan = fopen("img/rock.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture3, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture4[256 * 256 * 3];
			fHan = fopen("img/sky1.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture4, 256 * 256, 3, fHan);
			fclose(fHan);


			GLubyte Texture5[1024 * 512 * 3];
			fHan = fopen("img/univ3.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture5, 1024 * 512, 3, fHan);
			fclose(fHan);

			GLubyte Texture6[256 * 256 * 3];
			fHan = fopen("img/wall4.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture6, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture7[256 * 256 * 3];
			fHan = fopen("img/wall3.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture7, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture8[256 * 256 * 3];
			fHan = fopen("img/wall7.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture8, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture9[256 * 256 * 3];
			fHan = fopen("img/wall6.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture9, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture10[256 * 256 * 3];
			fHan = fopen("img/metal3.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture10, 256 * 256, 3, fHan);
			fclose(fHan);

			GLubyte Texture11[256 * 256 * 3];
			fHan = fopen("img/metal.raw", "rb");
			if(fHan == NULL) return(0);
			fread(Texture11, 256 * 256, 3, fHan);
			fclose(fHan);



			Textures.push_back(Texture1);
			Textures.push_back(Texture2);
			Textures.push_back(Texture3);
			Textures.push_back(Texture4);
			Textures.push_back(Texture5);
			Textures.push_back(Texture6);
			Textures.push_back(Texture7);
			Textures.push_back(Texture8);
			Textures.push_back(Texture9);
			Textures.push_back(Texture10);
			Textures.push_back(Texture11);

	}

	for(unsigned int i=0; i<Textures.size(); i++){
		glBindTexture(GL_TEXTURE_2D, i+1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE); //GL_REPLACE//GL_MODULATE se vogliamo le luci

		if(i==4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, Textures.at(i));
		else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, Textures.at(i));
	}

	//Posizione iniziale dell'osservatore
	ossY=13.3f;
	ossZ=1;
	ossX=0;
	ossB=-17;

	delta_t= glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return(0);
}

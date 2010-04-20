/*
 * Bomb.cpp
 *
 *  Created on: 16/apr/2010
 *      Author: ziby
 */

#include "Bomb.h"

Bomb::Bomb(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z, 0.5f,0.5f,0.5f), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, 0,1,0) {
	setL(1.0f);
	cout << "New bomb created at (" << _X << "," << _Y << "," << _Z << ")" << endl;
}

Bomb::Bomb(float _X,float _Y,float _Z, Sector* mySector, Building* myBuilding) : Obj(_X,_Y,_Z, 0.5f,0.5f,0.5f), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, 0,1,0) {
	setL(1.0f);
	currentSector = mySector;
	//possibileTarget.push_back(myBuilding);
	autodetectBuildings(myBuilding);
	cout << "New bomb created at (" << _X << "," << _Y << "," << _Z << ")" << endl;
}

void Bomb::move(long time){
	//Cinematica della bomba
	setY(getY()-getvY()*time/50);

};

void Bomb::autodetectBuildings(Building* myBuilding){
	vector<Building*> others = currentSector->getBuildings();
	for(unsigned int i=0; i< others.size(); i++){
		if(others.at(i)->getX() == myBuilding->getX() && others.at(i)->getZ() == myBuilding->getZ()){
			possibileTarget.push_back(others.at(i));
			others.at(i)->addRefer();
		}
	}
	cout << "Possibile target estimated: " << possibileTarget.size() << endl;

};

bool Bomb::checkCollision(){
	bool ris=false;
	for(unsigned register int i = 0; i< possibileTarget.size(); i++){
		if(possibileTarget.at(i)){
			if(getY()-getDimY()/2 <= possibileTarget.at(i)->getL()){
				possibileTarget.at(i)->setL(possibileTarget.at(i)->getL()-0.5f);

				Building* toRemove = possibileTarget.at(i);
				//toRemove->removeRefer();


				if(possibileTarget.at(i)->getL() <= 0.0f){
					cout << "checkCollisione,dentro if" << endl;
					currentSector->removeBuilding(toRemove);
				}

				//this->removePossibleTarget(toRemove);
				//i--;
				ris=true;

				//MI FERMO SUBITO?
				//return ris;
			}
		}
	}
	return ris;
};

void Bomb::clearRef(){
	for(unsigned int j=0; j< possibileTarget.size(); j++){
		possibileTarget.at(j)->removeRefer();
		if(possibileTarget.at(j)->isAlone() && possibileTarget.at(j)->getL()<=0.0f){
			delete possibileTarget.at(j);
			cout << "removed asddasd"<<endl;
		}
	}
};

void Bomb::addPossibleTarget(Building* newBuilding){
 possibileTarget.push_back(newBuilding);
};


void Bomb::removePossibleTarget(Building* newBuilding){

	for(unsigned int j=0; j< possibileTarget.size(); j++){
		if(newBuilding == possibileTarget.at(j)){
			possibileTarget.erase(possibileTarget.begin()+j);
			return;
		}
	}
};

void Bomb::setSector(Sector* mySector){
 currentSector = mySector;
};

Bomb::~Bomb(){
	//clearRef();
	cout << "Deleted bomb" << endl;
}

void Bomb::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(getX(),getY(),getZ());
	glRotatef(getrX(), 1, 0, 0);
	glRotatef(getrY(), 0, 1, 0);
	glRotatef(getrZ(), 0, 0, 1);

	float R = getDimX();
	//glColor3f((rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f);
	glColor3f(0.3f,0.3f,0.3f);
	glutSolidSphere(getDimX(),20,10);
	/*glBegin(GL_QUADS);

		glColor3f(1, 0, 1);
		glVertex3f(R, getL(), R);
		glVertex3f(-R, getL(), R);
		glVertex3f(-R, -getL(), R);
		glVertex3f(R, -getL(), R);

		glColor3f(0, 0, 1);
		glVertex3f(-R, getL(), -R);
		glVertex3f(R, getL(), -R);
		glVertex3f(R, -getL(), -R);
		glVertex3f(-R, -getL(), -R);

		glColor3f(1, 1, 0);
		glVertex3f(R, getL(), -R);
		glVertex3f(R, getL(), R);
		glVertex3f(R, -getL(), R);
		glVertex3f(R, -getL(), -R);

		glColor3f(0.5f, 0, 1);
		glVertex3f(-R, getL(), R);
		glVertex3f(-R, getL(), -R);
		glVertex3f(-R, -getL(), -R);
		glVertex3f(-R, -getL(), R);

		glColor3f(0, 1, 1);
		glVertex3f(R, getL(), -R);
		glVertex3f(-R, getL(), -R);
		glVertex3f(-R, getL(), R);
		glVertex3f(R, getL(), R);

		glColor3f(1, 0, 0);
		glVertex3f(-R, -getL(), -R);
		glVertex3f(R, -getL(), -R);
		glVertex3f(R, -getL(), R);
		glVertex3f(-R, -getL(), R);

	glEnd();*/

	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};

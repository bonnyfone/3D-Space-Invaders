/* ################################# Bomb #######################################
 * ######## Classe che rappresenta la bomba che viene sparata sulla città #######
 * è un oggeto MOBILE e DISTRUTTIBILE
 */

#include "Bomb.h"

//Costruttore (pos)
Bomb::Bomb(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z, 0.4f,0.4f,0.4f,rand()%360,rand()%360,rand()%360), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, 0,1,0) {
	setL(1.0f);
	cout << "New bomb created at (" << _X << "," << _Y << "," << _Z << ")" << endl;
}

//Costruttore speciale per bombe lanciate sopra uno specifico edificio
Bomb::Bomb(float _X,float _Y,float _Z, Sector* mySector, Building* myBuilding) : Obj(_X,_Y,_Z, 0.4f,0.4f,0.4f), DistructableObj(_X,_Y,_Z), MobileObj(_X,_Y,_Z, 0,1,0) {
	setL(1.0f);
	currentSector = mySector;
	//possibileTarget.push_back(myBuilding);
	autodetectBuildings(myBuilding);
	cout << "New bomb created at (" << _X << "," << _Y << "," << _Z << ")" << endl;
}

//Override del metodo di movimento di MobileObj
void Bomb::move(long time){
	//Cinematica della bomba
	setY(getY()-getvY()*time/speed);
	setrZ(getrZ()+1.0f);
	setrY(getrY()+1.0f);
	setrX(getrX()+1.0f);
};

//Metodo che individua automaticamente i possibili target di collisione
void Bomb::autodetectBuildings(Building* myBuilding){
	vector<Building*> others = currentSector->getBuildings();
	for(unsigned int i=0; i< others.size(); i++){
		/*
		 if(others.at(i)->getX() == myBuilding->getX() && others.at(i)->getZ() == myBuilding->getZ()){
			possibileTarget.push_back(others.at(i));
			others.at(i)->addRefer();
		}
		*/
		//La mia distanza massima di collisione (raggio+semi-diagonale dell'edificio)-> APPROSSIMAZIONE accettabile
		float impactDistance = this->getDimX() + others.at(i)->getR()*sqrt(2);
		float effectiveDistance = sqrt(
								  pow(this->getX()-others.at(i)->getX() ,2) +
								  //pow(this->getY()-others.at(i)->getY() ,2) +
								  pow(this->getZ()-others.at(i)->getZ() ,2));
		if(effectiveDistance <= impactDistance){
			possibileTarget.push_back(others.at(i));
			others.at(i)->addRefer();
		}
		//(x1 − x0)2 + (y1 − y0)2 + (z1 − z0)2.
	}
	cout << "Possibile target estimated: " << possibileTarget.size() << endl;

};

//Metodo che controlla se è avvenuta una collisione tra la bomba e i possibili target
bool Bomb::checkCollision(){
	register bool ris=false;
	register float max=0;
	register int maxIndex=-1;

	//individua i target condidati alla collisione
	for(unsigned register int i = 0; i< possibileTarget.size(); i++){
		if(getY() <= possibileTarget.at(i)->getL()*2){
			if(possibileTarget.at(i)->getL()>max){
				max = possibileTarget.at(i)->getL();
				maxIndex = i;
			}
		}
	}

	//tra i candidati alla collisione, prende quello ad altezza maggiore, quindi più vicino alla bomba
	if(maxIndex != -1){
		possibileTarget.at(maxIndex)->setL(possibileTarget.at(maxIndex)->getL()-0.5f);
		Building* toRemove = possibileTarget.at(maxIndex);

		if(possibileTarget.at(maxIndex)->getL() <= 0.0f){
			cout << "checkCollisione,dentro if" << endl;
			currentSector->removeBuilding(toRemove);
		}
		ris=true;
	}

	/*
	for(unsigned register int i = 0; i< possibileTarget.size(); i++){
		//if(possibileTarget.at(i)){
			if(getY()-getDimY() <= possibileTarget.at(i)->getL()){
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
		//}
	}
	*/
	return ris;
};

//metodo per la gestione della memoria condivisa (elimina i riferimenti a questa bomba)
void Bomb::clearRef(){
	for(unsigned int j=0; j< possibileTarget.size(); j++){
		possibileTarget.at(j)->removeRefer();
		if(possibileTarget.at(j)->isAlone() && possibileTarget.at(j)->getL()<=0.0f){
			delete possibileTarget.at(j);
			cout << "removed asddasd"<<endl;
		}
	}
};

//Metodo per l'aggiunta di un possibile target di collisione
void Bomb::addPossibleTarget(Building* newBuilding){
 possibileTarget.push_back(newBuilding);
};

//Metodo per la rimozione di un possibile target di collisione
void Bomb::removePossibleTarget(Building* newBuilding){

	for(unsigned int j=0; j< possibileTarget.size(); j++){
		if(newBuilding == possibileTarget.at(j)){
			possibileTarget.erase(possibileTarget.begin()+j);
			return;
		}
	}
};

//Metodo per impostare il settore di interesse
void Bomb::setSector(Sector* mySector){
 currentSector = mySector;
};

//Override del metodo di drawing
void Bomb::drawMe(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(getX(),getY(),getZ());
		glRotatef(getrX(), 1, 0, 0);
		glRotatef(getrY(), 0, 1, 0);
		glRotatef(getrZ(), 0, 0, 1);

		GLfloat ambiente[4] =  { 0.3f, 0.3f, 0.6f, 1.0f };
		GLfloat direttiva[4] =  { 0.3f,0.3f, 0.6f, 1.0f };
		GLfloat brillante[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		//glMateriali(GL_FRONT, GL_SHININESS, 32);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

		glutSolidSphere(getDimX(),10,10);

		glTranslatef(getDimX(),0,0);
		glutSolidSphere(0.1f,10,10);

	glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

};

Bomb::~Bomb(){
	cout << "Deleted bomb" << endl;
}

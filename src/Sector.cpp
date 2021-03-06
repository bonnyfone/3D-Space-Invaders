/*################################### SECTOR ######################################*/
/* Classe grafica-spaziale che rappresenta un quartiere della cittadella. Viene popolato
 * con degli edifici posizionati in modo casuale.
 */

#include "Sector.h"

	//Costruttore (pos,dim)
	Sector::Sector(int _X,int _Y,int _Z,int _dimX,int _dimY,int _dimZ) : Obj(_X,_Y,_Z,_dimX,_dimY,_dimZ) {
	};

	//Metodo che aggiunge un edificio(un riferimento ad un edificio) al settore
	void Sector::addBuilding(Building* _newBuilding){
		buildings.push_back(_newBuilding);
	};

	//Disegna tutti gli edifici presenti nel settore
	void Sector::drawBuildings(){
		for(int i=0;i<buildings.size();i++){
			buildings.at(i)->drawMe();
		}
	};

	//ottiene il vettore di riferimenti agli edifici
	vector<Building*> Sector::getBuildings(){return buildings;};

	//ottiene un riferimento ad un edificio casuale
	Building* Sector::getRandomBuilding(){
		register int range = buildings.size();
		if(range>0)
			return buildings.at(rand()%range);
		else return NULL;
	};

	//Metodo che rimuove un edificio dal settore
	void Sector::removeBuilding(Building* myBuilding){
		for(register unsigned int i=0;i<buildings.size();i++){
			if( myBuilding == buildings.at(i) ){
				buildings.erase(buildings.begin()+i);
				if(myBuilding->isAlone()){
					cout << "Building autodelete ";
					//delete myBuilding;
				}
				return;
			}
		}
	};

	//ritorna la "vita" residua degli edifici in questo settore
	float Sector::getBuildingsLife()const{
		float tmp=0.0f;
		for(register unsigned int i=0;i<buildings.size();i++){
			tmp+=buildings.at(i)->getL();
		}
		return tmp;
	};

	//Disegna il settore
	void Sector::drawMe(int cull){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

			glTranslatef(getX(),getY(),getZ());
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 2);
			glBegin(GL_QUADS);

			GLfloat ambiente[4] =  { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat direttiva[4] =  { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat brillante[4] = { 0.0f, 0.0f,0.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
			glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);


				if(cull==0){//antiorario
					glNormal3f(0,1,0);
					glTexCoord2f(0, 0);
					glVertex3f(0, 0.04, 0);

					glNormal3f(0,1,0);
					glTexCoord2f(1, 0);
					glVertex3f(getDimX(), 0.04, 0);

					glNormal3f(0,1,0);
					glTexCoord2f(1, 1);
					glVertex3f(getDimX(), 0.04, -getDimZ());

					glNormal3f(0,1,0);
					glTexCoord2f(0, 1);
					glVertex3f(0, 0.04, -getDimZ());
				}
				else{//orario

					glNormal3f(0,1,0);
					glTexCoord2f(0, 0);
					glVertex3f(0, 0.04, 0);

					glNormal3f(0,1,0);
					glTexCoord2f(0, 1);
					glVertex3f(0, 0.04,getDimZ());

					glNormal3f(0,1,0);
					glTexCoord2f(1, 0);
					glVertex3f(getDimX(), 0.04, getDimZ());

					glNormal3f(0,1,0);
					glTexCoord2f(1, 1);
					glVertex3f(getDimX(), 0.04, 0);
				}

			glEnd();
			glDisable(GL_TEXTURE_2D);

		glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

	};

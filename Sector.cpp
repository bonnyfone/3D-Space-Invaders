
#include "Sector.h"

	//Costruttore
	Sector::Sector(int _X,int _Y,int _Z,int _dimX,int _dimY,int _dimZ) : Obj(_X,_Y,_Z,_dimX,_dimY,_dimZ) {
		randomColor();
	};

	void Sector::randomColor(){
		r = (rand()%100)/100.0f;
		g = (rand()%100)/100.0f;
		b = (rand()%100)/100.0f;
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

	//Disegna il settore
	void Sector::drawMe(int cull){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

	    glTranslatef(getX(),getY(),getZ());

		glBegin(GL_QUADS);

			glColor3f(r, g, b);

			if(cull==0){//antiorario
				glVertex3f(0, 0.04, 0);
				glVertex3f(getDimX(), 0.04, 0);
				glVertex3f(getDimX(), 0.04, -getDimZ());
				glVertex3f(0, 0.04, -getDimZ());
			}
			else{//orario
				glVertex3f(0, 0.04, 0);
				glVertex3f(0, 0.04,getDimZ());
				glVertex3f(getDimX(), 0.04, getDimZ());
				glVertex3f(getDimX(), 0.04, 0);
			}

		glEnd();

		glPopMatrix(); //Con push e pop disaccoppio il disegno corrente dal resto del contesto

	};


	vector<Building*> Sector::getBuildings(){return buildings;};


#include "Obj.h"
#include "Building.h"


#ifndef SECTOR_H
#define SECTOR_H
using namespace std;

/*Classe logica che rappresenta i settori(quartieri) della cittadella*/
class Sector: public Obj{

private:
	vector<Building*> buildings;
	float r,g,b;

public:
	//Costruttore
	Sector(int,int,int,int,int,int);

	void randomColor();

	//Metodo che aggiunge un edificio(un riferimento ad un edificio) al settore
	void addBuilding(Building*);

	void removeBuilding(Building*);

	float getBuildingsLife()const;

	//Disegna tutti gli edifici presenti nel settore
	void drawBuildings();

	//Disegna il settore
	void drawMe(int);


	vector<Building*> getBuildings();

	Building* getRandomBuilding();

};

#endif

#include <vector>
#include "obj.h"

#ifndef SECTOR_H
#define SECTOR_H
using namespace std;

/*Classe logica che rappresenta i settori(quartieri) della cittadella*/
class Sector: public Obj{

private:
	vector<Obj*> buildings;
	float r,g,b;

public:
	//Costruttore
	Sector(int,int,int,int,int,int);

	void randomColor();

	//Metodo che aggiunge un edificio(un riferimento ad un edificio) al settore
	void addBuilding(Obj*);


	//Disegna tutti gli edifici presenti nel settore
	void drawBuildings();

	//Disegna il settore
	void drawMe(int);


	vector<Obj*> getBuildings();

};

#endif

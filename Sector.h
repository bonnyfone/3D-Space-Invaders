/*################################### SECTOR ######################################*/
/* Classe logico-grafica che rappresenta un quartiere della cittadella. Viene popolato
 * con degli edifici posizionati in modo casuale.
 */

#include "Obj.h"
#include "Building.h"
using namespace std;

#ifndef SECTOR_H
#define SECTOR_H

class Sector: public Obj{

private:
	//vettore contenente i riferimenti agli edifici presenti nel settore
	vector<Building*> buildings;

public:
	//Costruttore (pos,dim)
	Sector(int,int,int, int,int,int);

	//Metodo che aggiunge un edificio(un riferimento ad un edificio) al settore
	void addBuilding(Building*);

	//Metodo che rimuove un edificio dal settore
	void removeBuilding(Building*);

	//ritorna la "vita" residua degli edifici in questo settore
	float getBuildingsLife()const;

	//Disegna tutti gli edifici presenti nel settore
	void drawBuildings();

	//Disegna il settore
	void drawMe(int);

	//ottiene il vettore di riferimenti agli edifici
	vector<Building*> getBuildings();

	//ottiene un riferimento ad un edificio casuale
	Building* getRandomBuilding();
};

#endif

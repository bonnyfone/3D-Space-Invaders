/* ################################# Bomb #######################################
 * ######## Classe che rappresenta la bomba che viene sparata sulla città #######
 * è un oggeto MOBILE e DISTRUTTIBILE
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "MobileObj.h"
#include "DistructableObj.h"
#include "Sector.h"


class Bomb: public MobileObj, public DistructableObj {

private:
	//Velocità delle bombe (inverso)
	static const int speed = 300;

	//Settore su cui viene lanciata la bomba
	Sector* currentSector;

	//Indice dei possibili target di collisione (ottimazzazione!)
	vector<Building*> possibileTarget;

public:
	//Costruttori
	Bomb(float,float,float);
	Bomb(float,float,float,Sector*,Building*);

	//Metodo per l'aggiunta di un possibile target di collisione
	void addPossibleTarget(Building*);

	//Metodo per la rimozione di un possibile target di collisione
	void removePossibleTarget(Building*);

	//Metodo per impostare il settore di interesse
	void setSector(Sector*);

	//Metodo che individua automaticamente i possibili target di collisione
	void autodetectBuildings(Building*);

	//Metodo che controlla se è avvenuta una collisione tra la bomba e i possibili target
	bool checkCollision();

	//metodo per la gestione della memoria condivisa (elimina i riferimenti a questa bomba)
	void clearRef();

	//Override del metodo di drawing di Obj
	void drawMe();

	//Override del metodo di movimento di MobileObj
	void move(long);

	virtual ~Bomb();
};

#endif /* BOMB_H_ */

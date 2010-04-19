/*
 * Bomb.h
 *
 *  Created on: 16/apr/2010
 *      Author: ziby
 */

#ifndef BOMB_H_
#define BOMB_H_


#include "MobileObj.h"
#include "DistructableObj.h"
#include "Sector.h"

class Bomb: public MobileObj, public DistructableObj {

private:
	Sector* currentSector;
	vector<Building*> possibileTarget;


public:
	Bomb(float,float,float);
	Bomb(float,float,float,Sector*,Building*);

	void addPossibleTarget(Building*);

	void removePossibleTarget(Building*);

	void setSector(Sector*);

	void autodetectBuildings(Building*);

	bool checkCollision();

	void clearRef();

	void drawMe();

	void move(long);

	virtual ~Bomb();
};

#endif /* BOMB_H_ */

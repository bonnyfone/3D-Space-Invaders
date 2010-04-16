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

class Bomb: public MobileObj, public DistructableObj {
public:
	Bomb(float,float,float);

	void drawMe();

	void move(long);

	virtual ~Bomb();
};

#endif /* BOMB_H_ */

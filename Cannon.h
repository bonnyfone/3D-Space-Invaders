/*
 * Cannon.h
 *
 *  Created on: 20/apr/2010
 *      Author: ziby
 */

#ifndef CANNON_H_
#define CANNON_H_

#include "Obj.h"

class Cannon: public Obj {
public:
	float targeting;

	Cannon();

	void drawMe();

	void targetingAnimation();

	virtual ~Cannon();
};

#endif /* CANNON_H_ */

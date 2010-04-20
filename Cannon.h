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

private:
	bool targetingSystem;
	float targeting;

public:


	Cannon();

	void drawMe();

	void targetingAnimation();

	void swapTargetingEnabled();

	virtual ~Cannon();
};

#endif /* CANNON_H_ */

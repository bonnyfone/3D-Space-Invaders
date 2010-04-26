/*
 * Explosion.h
 *
 *  Created on: 26/apr/2010
 *      Author: ziby
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Obj.h"

class Explosion: public Obj {

private:
	float radius;

public:
	Explosion(float,float,float);

	void processExplosion(int);
	bool isFinished();

	void drawMe();



	virtual ~Explosion();
};

#endif /* EXPLOSION_H_ */

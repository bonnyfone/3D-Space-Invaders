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
	float deltal;
	int spriteframe;
	unsigned int myLight;
	int lightPos;
	static bool availableLight[7];

public:
	Explosion(float,float,float);

	void processExplosion(int);
	bool isFinished();

	void drawMe();



	virtual ~Explosion();
};

#endif /* EXPLOSION_H_ */

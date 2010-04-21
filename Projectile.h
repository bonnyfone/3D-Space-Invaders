/*
 * Projectile.h
 *
 *  Created on: 21/apr/2010
 *      Author: ziby
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "MobileObj.h"
#include "DistructableObj.h"

class Projectile: public MobileObj, public DistructableObj {

private:
	static const int speed = 10;

public:
	Projectile(float,float,float, float,float,float);

	void drawMe();

	void move(long);

	virtual ~Projectile();
};

#endif /* PROJECTILE_H_ */

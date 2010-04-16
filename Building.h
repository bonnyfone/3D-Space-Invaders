
#include "DistructableObj.h"

#ifndef BUILDING_H_
#define BUILDING_H_

class Building: public DistructableObj {

private:
	//Ingombro dell'edificio
	float R;

public:
	Building(float,float,float,float,float,float);

	void randomizeDimension();
	virtual void drawMe();

	virtual ~Building();
};

#endif

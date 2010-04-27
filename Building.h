
#include "DistructableObj.h"

#ifndef BUILDING_H_
#define BUILDING_H_

class Building: public DistructableObj {

private:
	//Ingombro dell'edificio
	float R;
	int texture_id;

public:
	Building(float,float,float,float,float,float);

	void randomizeDimension();
	float getR() const;
	virtual void drawMe();


	virtual ~Building();
};

#endif

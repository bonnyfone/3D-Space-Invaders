#include "Obj.h"

#ifndef MOBILEOBJ_H_
#define MOBILEOBJ_H_


class MobileObj: public virtual Obj {

private:
	float vX,vY,vZ;

public:
	//Costruttore a 6 parametri (posizione,velocità)
	MobileObj(float,float,float, float,float,float);

	//Costruttore a 9 parametri (posizione,dimensione,velocità)
	MobileObj(float,float,float, float,float,float, float,float,float);

	virtual void move(long);

	float getvX() const;
	float getvY() const;
	float getvZ() const;


	virtual ~MobileObj();
};

#endif /* MOBILEOBJ_H_ */

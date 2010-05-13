/*########################## MOBILEOBJ ########################*/
/* Classe fondamentale che rappresenta un generico oggetto grafico MOBILE.
 * Tale classe rappresenta la base di tutti gli oggetti che si muovono nello spazio.
 */

#include "Obj.h"

#ifndef MOBILEOBJ_H_
#define MOBILEOBJ_H_


class MobileObj: public virtual Obj {

private:
	//velocità dell'oggetto lungo i 3 assi
	float vX,vY,vZ;

public:
	//Costruttore a 6 parametri (posizione,velocità)
	MobileObj(float,float,float, float,float,float);

	//Costruttore a 9 parametri (posizione,dimensione,velocità)
	MobileObj(float,float,float, float,float,float, float,float,float);

	//metodo che descrive il moto dell'oggetto
	virtual void move(long);

	//Set & Get
	float getvX() const;
	float getvY() const;
	float getvZ() const;


	virtual ~MobileObj();
};

#endif /* MOBILEOBJ_H_ */

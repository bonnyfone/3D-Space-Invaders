/*########################## PROJECTILE ########################*/
/* Classe che rappresenta i proiettili sparati dal cannone.
 * è un oggetto MOBILE e DISTRUTTIBILE.
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "MobileObj.h"
#include "DistructableObj.h"

class Projectile: public MobileObj, public DistructableObj {

private:
	//velocità dei proiettili
	static const int speed = 10;

	//vecchia posizione del proiettile (serve per il metodo di collision-detection)
	float oldX,oldY,oldZ;

public:
	//Costruttore (pos,dim)
	Projectile(float,float,float, float,float,float);

	//Ovverride del metodo di drawing
	void drawMe();

	//Ovverride del metodo di movimento
	void move(long);

	//Set & Get
	float getOldX() const;
	float getOldY() const;
	float getOldZ() const;

	virtual ~Projectile();
};

#endif /* PROJECTILE_H_ */

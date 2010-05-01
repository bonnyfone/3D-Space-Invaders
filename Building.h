/*####################################### BUILDING #########################################
 *################### Classe che rappresenta un edificio della cittadella ##################
 * è un oggeto DISTRUTTIBILE
 */
#include "DistructableObj.h"

#ifndef BUILDING_H_
#define BUILDING_H_


class Building: public DistructableObj {

private:
	//Ingombro dell'edificio
	float R;

	//Texture da applicare
	int texture_id;

public:
	//Costruttore
	Building(float,float,float,float,float,float);

	//Metodo per attribuire un ingombro casuale all'edificio
	void randomizeDimension();

	//Metodo che ritorna l'ingombro dell'edificio
	float getR() const;

	//Override del metodo di drawing di Obj
	virtual void drawMe();

	virtual ~Building();
};

#endif

/*####################################### CANNON ##########################################
 *###################    Classe che rappresenta il cannone antibombe     ##################
 */

#ifndef CANNON_H_
#define CANNON_H_

#include "Obj.h"

class Cannon: public Obj {

private:

	//stato di attivazione del sistema di puntamento
	bool targetingSystem;

	//variabile di supporto per gestione targeting
	float targeting;

	//stato del recoil
	float recoil;

public:
	//Costruttore
	Cannon();

	//Ovverride del metodo di drawing
	void drawMe();

	//gestione animazione mirino
	void targetingAnimation();

	//toggle sistema puntamento
	void swapTargetingEnabled();

	//metodi per la gestione del recoil
	void setRecoil(float);
	float getRecoil() const;

	virtual ~Cannon();
};

#endif /* CANNON_H_ */

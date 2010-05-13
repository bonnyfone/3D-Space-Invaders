/*##########################        EXPLOSION       ########################*/
/* Classe prettamente grafica che rappresenta un'esplosione.
 * Utilizza la tecnica delle "Sprite Animation" per l'effetto grafico dell'esplosione.
 */


#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Obj.h"

class Explosion: public Obj {

private:
	//raggio dell'esplosione
	float radius;

	//valore che altera la colorazione della luce dell'esplosione all'avanzare dell'animazione
	float deltal;

	//frame attuale (ovvero, a che punto siamo dell'animazione)
	int spriteframe;

	//quale GL_LIGHT# si utilizza l'illuminazione dell'esplosione
	unsigned int myLight;
	int lightPos;

	//Array booleano statico che rappresenta la disponibilità di GL_LIGHT#
	static bool availableLight[7];

public:
	//Costruttore(pos)
	Explosion(float,float,float);

	//metodo per far avanzare l'animazione
	void processExplosion(int);

	//determina se l'animazione dell'esplosione è finita
	bool isFinished();

	//Override del metodo di drawing
	void drawMe();


	virtual ~Explosion();
};

#endif /* EXPLOSION_H_ */

/*########################## OBJ ########################*/
/* Classe fondamentale che rappresenta un generico oggetto grafico nello spazio
 * Si prevede che tale oggetto possa essere usato in modo condiviso, pertanto vengono forniti
 * i metodi per la gestione della memoria condivisa in stile SmartPointer
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

#ifndef OBJ_H
#define OBJ_H

class Obj{

private:
	//Coordinate grafiche
	float X,Y,Z;

	//Rotazione
	float rX,rY,rZ;

	//Dimensioni
	float dimX,dimY,dimZ;

	//Numero di puntatori che riferiscono l'oggetto (SmartPointing)
	int refering;

public:
	//Costruttore senza parametri
	Obj();

	//Costruttore a 3 parametri (posizione)
	Obj(float,float,float);

	//Costruttore a 6 parametri (posizione+dimensione)
	Obj(float,float,float,float,float,float);

	//Costruttore a 6 parametri (posizione+dimensione+rotaz)
	Obj(float,float,float,float,float,float,float,float,float);

	//Metodo virtuale per il drawing dell'oggetto
	virtual void drawMe();

	/* Set & get */
	float getDimX() const;
	float getDimY() const;
	float getDimZ() const;
	float getX() const;
	float getY() const;
	float getZ() const;
	float getrX() const;
	float getrY() const;
	float getrZ() const;
	void setX(float);
	void setY(float);
	void setZ(float);
	void setrX(float);
	void setrY(float);
	void setrZ(float);

	//Metodi per la gestione in stile SmartPointer
	void addRefer(); //aggiunta di un refer
	void removeRefer();//rimozione di un refer
	bool isAlone();//controlla se l'oggetto è cancellabile


	virtual ~Obj(){};
};


#endif


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
	float X,Y,Z;
	float rX,rY,rZ;
	float dimX,dimY,dimZ;

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

	void addRefer();
	void removeRefer();
	bool isAlone();


	virtual ~Obj(){};
};


#endif


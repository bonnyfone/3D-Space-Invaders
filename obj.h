#ifndef OBJ_H
#define OBJ_H

class Obj{

private:
	float X,Y,Z;
	float rX,rY,rZ;
	float vX,vY,vZ;
	float R,L;
public:
	//Costruttore senza parametri
	Obj();

	//Costruttore a 3 parametri (posizione)
	Obj(float,float,float);

	//Costruttore a 6 parametri (posizione+rotazione)
	Obj(float,float,float,float,float,float);

	//Costruttore a 6 parametri (posizione+rotazione+velocita)
	Obj(float,float,float,float,float,float,float,float,float);

	void randomizeDimension();
	void drawMe();
};


#endif


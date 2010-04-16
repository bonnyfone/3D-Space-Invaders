using namespace std;

#ifndef OBJ_H
#define OBJ_H

class Obj{

private:
	float X,Y,Z;
	float rX,rY,rZ;
	float dimX,dimY,dimZ;
	float R,L;
public:
	//Costruttore senza parametri
	Obj();

	//Costruttore a 3 parametri (posizione)
	Obj(float,float,float);

	//Costruttore a 6 parametri (posizione+dimensione)
	Obj(float,float,float,float,float,float);

	//Costruttore a 6 parametri (posizione+dimensione+rotaz)
	Obj(float,float,float,float,float,float,float,float,float);

	void randomizeDimension();
	virtual void drawMe();

	/* Set & get */
	float getDimX();
	float getDimY();
	float getDimZ();
	float getX();
	float getY();
	float getZ();

	virtual ~Obj(){};
};


#endif


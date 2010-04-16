#include "DistructableObj.h"
#include "Obj.h"
#include <math.h>

using namespace std;
//Costruttore a 3 parametri (posizione)
DistructableObj::DistructableObj(float _X,float _Y,float _Z) : Obj(_X,_Y,_Z){
	randomizeLife();
};

//Costruttore a 6 parametri (posizione+dimensione)
DistructableObj::DistructableObj(float _X,float _Y,float _Z,float _dimX,float _dimY,float _dimZ) : Obj(_X,_Y,_Z,_dimX,_dimY,_dimZ){
	randomizeLife();
};

//Costruttore a 6 parametri (posizione+dimensione+rotaz)
DistructableObj::DistructableObj(float _X,float _Y,float _Z,float _dimX,float _dimY,float _dimZ,float _rX,float _rY,float _rZ) : Obj(_X,_Y,_Z,_dimX,_dimY,_dimZ,_rX,_rY,_rZ){
	randomizeLife();
};

float DistructableObj::getL() const{ return L;
}

void DistructableObj::randomizeLife(){
	L = (rand()%400+20)/100.0f;
	cout << "L:" << L;
};

DistructableObj::~DistructableObj() {
	// TODO Auto-generated destructor stub
}

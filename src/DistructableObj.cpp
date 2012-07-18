/*########################## DISTRUCTABLEOBJ ########################*/
/* Classe fondamentale che rappresenta un generico oggetto grafico DISTRUTTIBILE.
 * Tale classe rappresenta la base di tutti gli oggetti che possono distruggersi.
 */

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

//metodo per generare casualmente la vita dell'oggetto
void DistructableObj::randomizeLife(){
	startingL= L = (rand()%400+20)/100.0f;
	cout << "L:" << L << endl;
};


//Set & Get
float DistructableObj::getL() const{ return L;}
float DistructableObj::getStartingL() const{ return startingL;}
void DistructableObj::setL(float _L){
	if(_L < 0.0f) _L=0.0f;
	L=_L;
}

DistructableObj::~DistructableObj() {

}

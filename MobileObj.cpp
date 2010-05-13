/*########################## MOBILEOBJ ########################*/
/* Classe fondamentale che rappresenta un generico oggetto grafico MOBILE.
 * Tale classe rappresenta la base di tutti gli oggetti che si muovono nello spazio.
 */

#include "MobileObj.h"

//Costruttore a 6 parametri (posizione,velocità)
MobileObj::MobileObj(float _X,float _Y,float _Z, float _vX,float _vY,float _vZ) : Obj(_X,_Y,_Z){
	vX = _vX; vY = _vY; vZ = _vZ;
};

//Costruttore a 9 parametri (posizione,dimensione,velocità)
MobileObj::MobileObj(float _X,float _Y,float _Z, float _dimX, float _dimY, float _dimZ, float _vX,float _vY,float _vZ) : Obj(_X,_Y,_Z,_dimX,_dimY,_dimZ){
	vX = _vX; vY = _vY; vZ = _vZ;
};

//metodo che descrive il moto dell'oggetto
void MobileObj::move(long time){/*da overridare*/};

//Set & Get
float MobileObj::getvX()const {return vX;};
float MobileObj::getvY()const {return vY;};
float MobileObj::getvZ()const {return vZ;};

MobileObj::~MobileObj() {
}


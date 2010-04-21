#include "MobileObj.h"

MobileObj::MobileObj(float _X,float _Y,float _Z, float _vX,float _vY,float _vZ) : Obj(_X,_Y,_Z){
	vX = _vX; vY = _vY; vZ = _vZ;
};

MobileObj::MobileObj(float _X,float _Y,float _Z, float _dimX, float _dimY, float _dimZ, float _vX,float _vY,float _vZ) : Obj(_X,_Y,_Z,_dimX,_dimY,_dimZ){
	vX = _vX; vY = _vY; vZ = _vZ;
};

float MobileObj::getvX()const {return vX;};
float MobileObj::getvY()const {return vY;};
float MobileObj::getvZ()const {return vZ;};

void MobileObj::move(long time){/*overridare*/};


MobileObj::~MobileObj() {
	// TODO Auto-generated destructor stub
}


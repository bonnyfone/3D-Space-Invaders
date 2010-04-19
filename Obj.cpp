
#include "Obj.h"
using namespace std;

	//Costruttore
	Obj::Obj(){
		refering=0;
		X=0; Y=0; Z=-10; rX=rY=rZ=dimX=dimY=dimZ=0;
		cout << "costruttore 0 param";
	};

	//Costruttore a 3 parametri (posizione)
	Obj::Obj(float _X,float _Y,float _Z){
		refering=0;
		X=_X; Y=_Y; Z=_Z; rX=rY=rZ=dimX=dimY=dimZ=0;
	};

	//Costruttore a 6 parametri (posizione+dimensione)
	Obj::Obj(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ){
		refering=0;
		X=_X; Y=_Y; Z=_Z; rX=rY=rZ=0; dimX=_rX; dimY=_rY; dimZ=_rZ;
	};

	//Costruttore a 6 parametri (posizione+dimensione+rotazione)
	Obj::Obj(float _X,float _Y,float _Z,float _rX,float _rY,float _rZ,float _vX,float _vY,float _vZ){
		refering=0;
		X=_X; Y=_Y; Z=_Z; rX=_vX; rY=_vY; rZ=_vZ; dimX=_rX; dimY=_rY; dimZ=_rZ;
	};


	void Obj::drawMe(){
		/* da overridare*/
	};

	/* Set & get */
	float Obj::getDimX() const {return dimX;};
	float Obj::getDimY() const {return dimY;};
	float Obj::getDimZ() const {return dimZ;};
	float Obj::getX() const {return X;};
	float Obj::getY() const {return Y;};
	float Obj::getZ() const {return Z;};
	float Obj::getrX() const {return rX;};
	float Obj::getrY() const {return rY;};
	float Obj::getrZ() const {return rZ;};
	void Obj::setX(float _X){ X = _X;};
	void Obj::setY(float _Y){ Y = _Y;};
	void Obj::setZ(float _Z){ Z = _Z;};

	void Obj::addRefer(){
		refering++;
	};

	void Obj::removeRefer(){
		refering--;
	};

	bool Obj::isAlone(){
		cout << "Checkato isAlone() = " << refering << endl;
		if(refering>0) return false;
		return true;
	}


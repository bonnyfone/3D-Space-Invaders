
#include "Obj.h"
using namespace std;

#ifndef DISTRUCTABLEOBJ_H_
#define DISTRUCTABLEOBJ_H_

/* Classe che rappresenta il tipo base di tutti gli oggetti distruggibili*/
class DistructableObj: public Obj
{
private:
    float L;

public:
    //Costruttore a 3 parametri (posizione)
    DistructableObj(float, float, float);
    //Costruttore a 6 parametri (posizione+dimensione)
    DistructableObj(float, float, float, float, float, float);
    //Costruttore a 6 parametri (posizione+dimensione+rotaz)
    DistructableObj(float, float, float, float, float, float, float, float, float);


    //metodo per generare casualmente la vita dell'oggetto
    void randomizeLife();

    //ritorna quanta vita ha l'oggetto
    float getL() const;

    virtual ~DistructableObj();


};

#endif /* DISTRUCTABLEOBJ_H_ */

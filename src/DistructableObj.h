/*########################## DISTRUCTABLEOBJ ########################*/
/* Classe fondamentale che rappresenta un generico oggetto grafico DISTRUTTIBILE.
 * Tale classe rappresenta la base di tutti gli oggetti che possono distruggersi.
 */

#include "Obj.h"
using namespace std;

#ifndef DISTRUCTABLEOBJ_H_
#define DISTRUCTABLEOBJ_H_

/* Classe che rappresenta il tipo base di tutti gli oggetti distruggibili*/
class DistructableObj: public virtual Obj
{
private:
	//la "vita" attuale dell'oggetto. L'oggetto è completamente distrutto quando L <= 0
    float L;

    //la "vita" iniziale
    float startingL;

public:
    //Costruttore a 3 parametri (posizione)
    DistructableObj(float, float, float);

    //Costruttore a 6 parametri (posizione+dimensione)
    DistructableObj(float, float, float, float, float, float);

    //Costruttore a 6 parametri (posizione+dimensione+rotaz)
    DistructableObj(float, float, float, float, float, float, float, float, float);

    //metodo per generare casualmente la vita dell'oggetto
    void randomizeLife();

    //Set & Get
    float getL() const;
    float getStartingL() const;
    void setL(float);

    virtual ~DistructableObj();
};

#endif /* DISTRUCTABLEOBJ_H_ */

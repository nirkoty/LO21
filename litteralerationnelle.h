#ifndef LITTERALERATIONNELLE_H
#define LITTERALERATIONNELLE_H

#include "litteralenumerique.h"
#include "litteraleentiere.h"

class LitteraleRationnelle : public LitteraleNumerique
{
private:
    LitteraleEntiere nominateur;
    LitteraleEntiere denominateur;

public:
    LitteraleRationnelle(int s, LitteraleEntiere nom, LitteraleEntiere denom);
    LitteraleRationnelle(QString input);
    LitteraleEntiere getNominateur(){return nominateur;}
    LitteraleEntiere getDenominateur(){return denominateur;}
    QString toString();
    static bool estLitteraleRationnelle(QString bloc);
    Litterale* operator+(Litterale& lit2){return this;}
    Litterale* operator*(Litterale& lit2){return this;}
    Litterale* operator/(Litterale& lit2){return this;}
    Litterale* operator-(Litterale& lit2){return this;}

};

#endif // LITTERALERATIONNELLE_H

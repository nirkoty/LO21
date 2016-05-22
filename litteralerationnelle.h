#ifndef LITTERALERATIONNELLE_H
#define LITTERALERATIONNELLE_H

#include "litterale.h"
#include "litteraleentiere.h"

class LitteraleRationnelle : public Litterale
{
public:
    LitteraleRationnelle(bool neg, LitteraleEntiere nom, LitteraleEntiere denom);
    LitteraleEntiere getNominateur(){return nominateur;}
    LitteraleEntiere getDenominateur(){return denominateur;}
    QString toString();
    static bool estLitteraleRationnelle(QString bloc);

private:
    LitteraleEntiere nominateur;
    LitteraleEntiere denominateur;
};

#endif // LITTERALERATIONNELLE_H

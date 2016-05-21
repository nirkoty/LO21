#ifndef LITTERALEREELLE_H
#define LITTERALEREELLE_H

#include "litterale.h"

class LitteraleReelle : public Litterale
{
public:
    LitteraleReelle(bool neg, double nom, double denom);
    double getNominateur(){return nominateur;}
    double getDenominateur(){return denominateur;}
    QString toString();
    static bool estLitteraleReelle(QString bloc);

private:
    double nominateur;
    double denominateur;
};

#endif // LITTERALEREELLE_H

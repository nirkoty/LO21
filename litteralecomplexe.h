#ifndef LITTERALECOMPLEXE_H
#define LITTERALECOMPLEXE_H


#include "litteralereelle.h"
#include "litterale.h"

class LitteraleComplexe : public Litterale
{
public:
    LitteraleComplexe(int s, LitteraleReelle re, LitteraleReelle im);
    LitteraleReelle getReelle() const {return partieRelle;}
    LitteraleReelle getImaginaire() const {return partieImaginaire;}
    QString toString();
    static bool estLitteraleComplexe(QString bloc);
    Litterale* operator+(Litterale& lit2){}
    Litterale* operator*(Litterale& lit2){}
    Litterale* operator/(Litterale& lit2){}
    Litterale* operator-(Litterale& lit2){}

private :
    LitteraleReelle partieRelle;
    LitteraleReelle partieImaginaire;
};

#endif // LITTERALECOMPLEXE_H

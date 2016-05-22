#ifndef LITTERALECOMPLEXE_H
#define LITTERALECOMPLEXE_H


#include "litteralereelle.h"
#include "litterale.h"

class LitteraleComplexe : public Litterale
{
public:
    LitteraleComplexe(bool neg, Litterale re, Litterale im);
    Litterale getReelle() const {return partieRelle;}
    Litterale getImaginaire() const {return partieImaginaire;}
    static bool estLitteraleComplexe(QString bloc);

private :
    Litterale partieRelle;
    Litterale partieImaginaire;
};

#endif // LITTERALECOMPLEXE_H

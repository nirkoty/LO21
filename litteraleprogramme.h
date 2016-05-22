#ifndef LITTERALEPROGRAMME_H
#define LITTERALEPROGRAMME_H


#include "QString"
#include "operande.h"

class LitteraleProgramme
{
public:
    LitteraleProgramme(QString programme);
    bool static estLitteraleProgramme(QString bloc);

private:
    Operande operandes[];
    int nbOperandes;

};

#endif // LITTERALEPROGRAMME_H

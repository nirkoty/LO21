#ifndef LITTERALEPROGRAMME_H
#define LITTERALEPROGRAMME_H


#include "QString"
#include "operande.h"
#include <vector>
#include "litterale.h"

class LitteraleProgramme : public Litterale
{
public:
    LitteraleProgramme(QString programme);
    bool static estLitteraleProgramme(QString bloc);
    QString toString();
    Litterale* operator+(Litterale& lit2){}
    Litterale* operator*(Litterale& lit2){}
    Litterale* operator/(Litterale& lit2){}
    Litterale* operator-(Litterale& lit2){}

private:
    std::vector<Operande*> operandes;
    int nbOperandes;

};

#endif // LITTERALEPROGRAMME_H

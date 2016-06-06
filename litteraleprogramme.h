#ifndef LITTERALEPROGRAMME_H
#define LITTERALEPROGRAMME_H


#include "QString"
#include <vector>
#include "litterale.h"

class LitteraleProgramme : public Litterale
{
private:
    QString programme;

public:
    LitteraleProgramme(QString programme);
    bool static estLitteraleProgramme(QString bloc);
    QString toString();
    QString getStrProgramme();
    Litterale* evaluer();

    Litterale* operator+(Litterale& lit2){return this;}
    Litterale* operator*(Litterale& lit2){return this;}
    Litterale* operator/(Litterale& lit2){return this;}
    Litterale* operator-(Litterale& lit2){return this;}




};

#endif // LITTERALEPROGRAMME_H

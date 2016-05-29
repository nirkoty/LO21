#ifndef LITTERALENUMERIQUE_H
#define LITTERALENUMERIQUE_H

#include "litterale.h"

class LitteraleNumerique : public Litterale
{
public:
    LitteraleNumerique();
    LitteraleNumerique(int s);
    int getSigne(){return signe;}
    virtual Litterale* operator+(Litterale& lit2) = 0;
    virtual Litterale* operator*(Litterale& lit2) = 0;
    virtual Litterale* operator-(Litterale& lit2) = 0;
    virtual Litterale* operator/(Litterale& lit2) = 0;
    //virtual QString toString()=0;

protected:
    int signe;
};

#endif // LITTERALENUMERIQUE_H

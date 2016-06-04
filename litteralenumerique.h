#ifndef LITTERALENUMERIQUE_H
#define LITTERALENUMERIQUE_H

#include "litterale.h"

class LitteraleNumerique : public Litterale
{
protected:
    int signe;

public:
    LitteraleNumerique();
    LitteraleNumerique(int s);
    int getSigne(){return signe;}


    //virtual QString toString()=0;
};


#endif // LITTERALENUMERIQUE_H

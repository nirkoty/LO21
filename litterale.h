#ifndef LITTERALE_H
#define LITTERALE_H

#include <QString>

class Litterale
{
public:
    Litterale();
    virtual QString toString()=0;
    virtual Litterale* operator+(Litterale& lit2) = 0;
    virtual Litterale* operator*(Litterale& lit2) = 0;
    virtual Litterale* operator-(Litterale& lit2) = 0;
    virtual Litterale* operator/(Litterale& lit2) = 0;
};

#endif // LITTERALE_H

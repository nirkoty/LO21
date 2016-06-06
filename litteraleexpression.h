#ifndef LITTERALEEXPRESSION_H
#define LITTERALEEXPRESSION_H


#include "litterale.h"
#include "QString"
#include <vector>
#include "manager.h"

class LitteraleExpression : public Litterale
{
public:
    LitteraleExpression(QString exp, Manager* man);
    static bool estLitteraleExpression(QString exp);
    QString toString() {return expression;}
    QString toStringAvecGuillemets();
    Litterale* evaluer();
    Litterale* evaluerRec(QString exp);
    virtual Litterale* operator+(Litterale& lit2){return this;}
    virtual Litterale* operator*(Litterale& lit2){return this;}
    virtual Litterale* operator-(Litterale& lit2){return this;}
    virtual Litterale* operator/(Litterale& lit2){return this;}


private:
    QString expression;
    Manager* manager;
};

#endif // LITTERALEEXPRESSION_H

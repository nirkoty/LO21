#ifndef LITTERALEEXPRESSION_H
#define LITTERALEEXPRESSION_H


#include "litterale.h"
#include "operande.h"
#include "QString"
#include <vector>

class LitteraleExpression : public Litterale
{
public:
    LitteraleExpression(QString exp);
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
    std::vector<Operande*> operandes;
};

#endif // LITTERALEEXPRESSION_H

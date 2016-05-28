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
    QString toString() const {return expression;}
    void evaluer();

private:
    QString expression;
    std::vector<Operande*> operandes;
};

#endif // LITTERALEEXPRESSION_H

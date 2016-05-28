#include "litteraleexpression.h"

LitteraleExpression::LitteraleExpression(QString exp)
{
    exp = exp.remove(0,1); // enlève les ''
    expression= exp.remove(exp.length()-1, 1);
}


bool LitteraleExpression::estLitteraleExpression(QString exp){
    return (exp.left(1)=="'"  && exp.right(1)=="'");
}

void LitteraleExpression::evaluer(){

    bool neg=false;
    bool newOp=true;
    QString tmp="";


    while(expression.length()>0){

        if(expression.left(1)=="-" && newOp){
            neg=true;
            expression=expression.remove(0,1);
        }

        while(expression.left(1)!= "*" || expression.left(1)!= "-" || expression.left(1)!= "+")
            tmp=tmp.append(expression.at(0));



    }
}

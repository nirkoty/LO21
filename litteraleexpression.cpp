#include "litteraleexpression.h"
#include "litteraleentiere.h"
#include "litteralereelle.h"
#include <QDebug>
#include <typeinfo>


LitteraleExpression::LitteraleExpression(QString exp)
{
    exp = exp.remove(0,1); // enlève les ''
    expression= exp.remove(exp.length()-1, 1);
}


bool LitteraleExpression::estLitteraleExpression(QString exp){
    return (exp.left(1)=="'"  && exp.right(1)=="'");
}

Litterale* LitteraleExpression::evaluer(){
    return evaluerRec(expression);
}

Litterale* LitteraleExpression::evaluerRec(QString exp){

    qDebug()<<exp;
    bool neg=false;
    bool newOp=true;
    QString tmp="";

    if(exp.left(1)=="(" && exp.right(1)==")"){
        exp=exp.remove(0,1);
        exp=exp.remove(exp.length()-1,1);
    }


    int indexPlus = exp.indexOf("+");
    bool okFin=true;
    bool okDebut=true;
    if(indexPlus!=-1){
        for(unsigned int i=exp.indexOf("+"); i<exp.length(); i++){
            if(exp.at(i)=='(')
                break;
            else if(exp.at(i)==')')
                okFin=false;
        }

        for(unsigned int i=0; i<exp.indexOf("+"); i++){
            if(exp.at(i)==')')
                break;
            else if(exp.at(i)=='(')
                okDebut=false;
        }
    }
    if(indexPlus!=-1 && okDebut && okFin){
        Litterale *gauche=evaluerRec(exp.left(exp.indexOf("+")));
        Litterale *droite = evaluerRec(exp.right(exp.length()-exp.indexOf("+")-1));
        Litterale *newLit = *gauche+*droite;

        qDebug()<<newLit->toString();

        delete gauche;
        delete droite;

        return newLit;
    }
    else if(exp.contains('*')){
        Litterale *gauche=evaluerRec(exp.left(exp.indexOf("*")));
        Litterale *droite = evaluerRec(exp.right(exp.length()-exp.indexOf("*")-1));
        Litterale *newLit = *gauche*(*droite);

        qDebug()<<newLit->toString();

        delete gauche;
        delete droite;

        return newLit;
    }

    else if(exp.contains('/')){
        Litterale *gauche=evaluerRec(exp.left(exp.indexOf("/")));
        Litterale *droite = evaluerRec(exp.right(exp.length()-exp.indexOf("/")-1));
        Litterale *newLit = *gauche/ *droite;
        //Litterale *newLit = *droite/(*gauche);
        qDebug()<<"coucou"<<newLit->toString();

        delete gauche;
        delete droite;

        return newLit;
    }


    else
    {
        if(LitteraleEntiere::estLitteraleEntiere(exp))
            return new LitteraleEntiere(exp);
        if(LitteraleReelle::estLitteraleReelle(exp))
            return new LitteraleReelle(exp);
    }


}

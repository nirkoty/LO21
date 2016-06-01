#include "litteralereelle.h"
#include "litteraleentiere.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include <QtDebug>

LitteraleReelle::LitteraleReelle(int s, double val) : LitteraleNumerique(s), valeur(val)
{

}

LitteraleReelle::LitteraleReelle(QString exp){
    if(exp.at(0)==QChar('-')){
        signe=-1;
        exp.remove(0, 1);
    }
    valeur=exp.toDouble();
}

QString LitteraleReelle::toString(){

      return QString::number(valeur);
}

bool LitteraleReelle::estLitteraleReelle(QString bloc){
    if(!bloc.contains("."))
        return false;

    QString strEntiere =  bloc.section('.', 0, 0);
    QString strDecimale =  bloc.section('.', 1, 1);


    if((LitteraleEntiere::estLitteraleEntiere(strEntiere) || (strEntiere.length()==0 && strDecimale.length()>0)) &&
            (LitteraleEntiere::estLitteraleEntiere(strDecimale)  || (strDecimale.length()==0 && strEntiere.length()>0)))
        return true;
    else
        return false;
}


Litterale* LitteraleReelle::operator+(Litterale& lit2){
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        double somme = this->signe*valeur+lit2E->getSigne()*lit2E->getValeur();
        int neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleReelle(neg, somme);
    }

    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {
        double somme =this->signe*valeur+lit2E->getSigne()*lit2E->getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleReelle(neg, somme);
    }
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {
        double somme = signe*valeur+lit2E->getSigne()*(lit2E->getNominateur().getValeur()/lit2E->getDenominateur().getValeur());
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleRationnelle(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        double somme =this->signe*valeur+lit2E->getSigne()*lit2E->getReelle().getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleComplexe(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getImaginaire().getValeur()));
    }

}

Litterale* LitteraleReelle::operator-(Litterale& lit2){
    qDebug()<<"testCast";
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        qDebug()<<"ENT";
        qDebug()<<this->signe <<" "<<valeur<<" "<<lit2E->getSigne()<<" "<<lit2E->getValeur();
        int somme = this->signe*valeur-lit2E->getSigne()*lit2E->getValeur();
        int neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleReelle(neg, somme);
    }
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {
        qDebug()<<"REE";

        qDebug()<<this->signe <<" "<<valeur<<" "<<lit2E->getSigne()<<" "<<lit2E->getValeur();
        double somme =this->signe*valeur-lit2E->getSigne()*lit2E->getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        qDebug()<<"somme" <<somme;
        return new LitteraleReelle(neg, somme);
    }
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {
        double somme = signe*valeur+lit2E->getSigne()*(lit2E->getNominateur().getValeur()/lit2E->getDenominateur().getValeur());
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleRationnelle(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        double somme =this->signe*valeur-lit2E->getSigne()*lit2E->getReelle().getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleComplexe(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getImaginaire().getValeur()));
    }

}


Litterale* LitteraleReelle::operator*(Litterale& lit2){

    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {

        int somme = this->signe*valeur*lit2E->getSigne()*lit2E->getValeur();
        int neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;
        return new LitteraleEntiere(neg, somme);
    }
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {


        double somme =this->signe*valeur*lit2E->getSigne()*lit2E->getValeur();
        bool neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;

        return new LitteraleReelle(neg, somme);
    }
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {
        double somme =this->signe*valeur*lit2E->getSigne()*lit2E->getNominateur().getValeur();
        bool neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;
        return new LitteraleRationnelle(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {
        double sommeR =this->signe*valeur*lit2E->getReelle().getSigne()*lit2E->getReelle().getValeur();
        bool negR;
        if(sommeR>=0)
            negR=1;
        else
            negR=-1;
        double sommeI =this->signe*valeur*lit2E->getImaginaire().getSigne()*lit2E->getImaginaire().getValeur();
        bool negI;
        if(sommeI>=0)
            negI=1;
        else
            negI=-1;

        return new LitteraleComplexe(1, LitteraleEntiere(negR, sommeR), LitteraleEntiere(negI, sommeI));
    }

}

Litterale* LitteraleReelle::operator/(Litterale& lit2){

    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {

        qDebug()<<"div1"<<lit2E->getValeur()<<" "<<valeur;
        double div = (this->signe*valeur)/(lit2E->getSigne()*lit2E->getValeur());

        int neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;

        qDebug()<<"div"<<div;
        return new LitteraleEntiere(neg, div);
    }
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {


        double div =(this->signe*valeur)/(lit2E->getSigne()*lit2E->getValeur());
        bool neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;

        return new LitteraleReelle(neg, div);
    }

    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {
        double somme =this->signe*valeur*lit2E->getSigne() / lit2E->getNominateur().getValeur();
        bool neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;
        return new LitteraleRationnelle(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {
        double sommeR =this->signe*valeur/lit2E->getReelle().getSigne()*lit2E->getReelle().getValeur();
        bool negR;
        if(sommeR>=0)
            negR=1;
        else
            negR=-1;
        double sommeI =this->signe*valeur/lit2E->getImaginaire().getSigne()*lit2E->getImaginaire().getValeur();
        bool negI;
        if(sommeI>=0)
            negI=1;
        else
            negI=-1;

        return new LitteraleComplexe(1, LitteraleEntiere(negR, sommeR), LitteraleEntiere(negI, sommeI));
    }

}

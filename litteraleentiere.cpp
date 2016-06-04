#include "litteraleentiere.h"
#include "litteralereelle.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include <typeinfo>
#include <QDebug>

LitteraleEntiere::LitteraleEntiere(int s, int val) : LitteraleNumerique(s), valeur(val){}

LitteraleEntiere::LitteraleEntiere(QString exp){
    if(exp.at(0)=='-'){
        signe=-1;
        exp.remove(0,1);
    }
    valeur=exp.toInt();
}

LitteraleEntiere::LitteraleEntiere(){}

QString LitteraleEntiere::toString(){
    return QString::number(valeur);
}


bool LitteraleEntiere::estLitteraleEntiere(QString bloc){
     return bloc.toInt() || bloc=="0";
}

Litterale* LitteraleEntiere::operator+(Litterale& lit2){
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        int somme = this->signe*valeur+lit2E->signe*lit2E->valeur;
        int neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleEntiere(neg, somme);
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
        double somme =this->signe*valeur*lit2E->getDenominateur().getValeur() +lit2E->getSigne()*lit2E->getNominateur().getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleRationnelle(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }
    /*else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        double somme = this->signe * valeur + lit2E->getReelle()->getSigne() * lit2E->getReelle()->getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleComplexe(new LitteraleEntiere(neg, somme), new LitteraleEntiere(1, lit2E->getImaginaire()->getValeur()));
    }*/

}

Litterale* LitteraleEntiere::operator-(Litterale& lit2){
    qDebug()<<"testCast Litterale entiere " << typeid(&lit2).name();
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        qDebug()<<"ENT";
        qDebug()<<this->signe <<" "<<valeur<<" "<<lit2E->signe<<" "<<lit2E->valeur;
        int somme = this->signe*valeur-lit2E->signe*lit2E->valeur;
        int neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleEntiere(neg, somme);
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
        double somme =this->signe*valeur*lit2E->getDenominateur().getValeur() -lit2E->getSigne()*lit2E->getNominateur().getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        return new LitteraleRationnelle(neg, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        /*double somme = this->signe*valeur-lit2E->getSigne()*lit2E->getReelle()->getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;*/

        qDebug() << "LittEnt operateur- avec complexe ";

        LitteraleNumerique* lit22 = lit2E->getReelle();
        qDebug() << "LittEnt operateur- avec complexe 2";
        return new LitteraleComplexe(dynamic_cast<LitteraleNumerique*>(*this-*lit22), lit2E->getImaginaire());
    }

}


Litterale* LitteraleEntiere::operator*(Litterale& lit2){

    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {

        int somme = this->signe*valeur*lit2E->signe*lit2E->valeur;
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
   /* else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {
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
    }*/

}

Litterale* LitteraleEntiere::operator/(Litterale& lit2){

    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {

        int neg;
        if((signe==1 && lit2E->getSigne()==1) || (signe==-1 && lit2E->getSigne()==-1))
            neg=1;
        else
            neg=-1;

        if((lit2E->signe*lit2E->valeur)%(this->signe*valeur)==0)
            return new LitteraleEntiere(neg, (lit2E->signe*lit2E->valeur)/(this->signe*valeur));
        else
            return new LitteraleRationnelle(neg, LitteraleEntiere(1, lit2E->valeur), LitteraleEntiere(1, valeur));
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
    /*else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {
        double sommeR =this->signe*valeur/lit2E->getReelle().getSigne()*lit2E->getReelle()->getValeur();
        bool negR;
        if(sommeR>=0)
            negR=1;
        else
            negR=-1;
        double sommeI =this->signe*valeur/lit2E->getImaginaire().getSigne()*lit2E->getImaginaire()->getValeur();
        bool negI;
        if(sommeI>=0)
            negI=1;
        else
            negI=-1;

        return new LitteraleComplexe(1, LitteraleEntiere(negR, sommeR), LitteraleEntiere(negI, sommeI));
    }*/

}



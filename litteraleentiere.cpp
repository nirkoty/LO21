#include "litteraleentiere.h"
#include "litteralereelle.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include <typeinfo>
#include <QDebug>

LitteraleEntiere::LitteraleEntiere(int s, int val) : LitteraleNumerique(s), valeur(val)
{

}

LitteraleEntiere::LitteraleEntiere(QString exp){
    if(exp.at(0)=='-'){
        signe=-1;
        exp.remove(0,1);
    }
    valeur=exp.toInt();
}

QString LitteraleEntiere::toString(){
    return QString::number(valeur);
}


bool LitteraleEntiere::estLitteraleEntiere(QString bloc){
     return bloc.toInt() || bloc=="0";
}

Litterale* LitteraleEntiere::operator+(Litterale& lit2){
    qDebug()<<"testCast";
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        qDebug()<<"ENT";
        qDebug()<<this->signe <<" "<<valeur<<" "<<lit2E->signe<<" "<<lit2E->valeur;
        int somme = this->signe*valeur+lit2E->signe*lit2E->valeur;
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
        double somme =this->signe*valeur+lit2E->getSigne()*lit2E->getValeur();
        bool neg;
        if(somme>=0)
            neg=1;
        else
            neg=-1;
        qDebug()<<"somme" <<somme;
        return new LitteraleReelle(neg, somme);
    }

}

Litterale* LitteraleEntiere::operator-(Litterale& lit2){
    qDebug()<<"testCast";
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

}

Litterale* LitteraleEntiere::operator/(Litterale& lit2){

    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {

        qDebug()<<"div1"<<lit2E->valeur<<" "<<valeur;
        double div = (this->signe*valeur)/(lit2E->signe*lit2E->valeur);

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

}



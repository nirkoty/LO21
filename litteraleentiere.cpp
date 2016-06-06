#include "litteraleentiere.h"
#include "litteralereelle.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include <typeinfo>
#include <QDebug>


LitteraleEntiere::LitteraleEntiere(int s, unsigned int val) : LitteraleNumerique(s), valeur(val){}

LitteraleEntiere::LitteraleEntiere(QString exp){
    if(exp.at(0)=='-'){
        signe=-1;
        exp.remove(0,1);
    }
    valeur=exp.toInt();
}

LitteraleEntiere::LitteraleEntiere(){}

QString LitteraleEntiere::toString(){
    qDebug() << "toString entier" << endl;
    if (signe==-1) return("-"+QString::number(valeur));
    else return QString::number(valeur);
}


bool LitteraleEntiere::estLitteraleEntiere(QString bloc){
     return bloc.toInt() || bloc=="0";
}


// OPERATEUR + pour un premier terme entier -- OK
Litterale* LitteraleEntiere::operator+(Litterale& lit2){

    // Si le second terme est un entier
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        unsigned int somme = valeur + lit2E->valeur;
        int s = signe * lit2E->getSigne();
        return new LitteraleEntiere(s, somme);
    }

    // Si le second terme est un reel
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {
        double somme =this->signe*valeur+lit2E->getSigne()*lit2E->getValeur();
        int s;
        if(somme>=0)
            s = 1;
        else
            s = -1;
        return new LitteraleReelle(s, somme);
    }

    // Si le second terme est un rationnel
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {

        double somme = this->signe*valeur*lit2E->getDenominateur().getValeur() + lit2E->getSigne()*lit2E->getNumerateur().getValeur();
        int s;
        if(somme>=0)
            s = 1;
        else
            s = -1;
        return new LitteraleRationnelle(s, LitteraleEntiere(1, somme), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }

    // Si le second terme est un complexe
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        LitteraleNumerique* litResultat = lit2E->getReelle();
        return new LitteraleComplexe(dynamic_cast<LitteraleNumerique*>(*litResultat + *this), lit2E->getImaginaire());
    }

}


// OPERATEUR - pour un premier terme entier -- OK
Litterale* LitteraleEntiere::operator-(Litterale& lit2){

    // Si le second terme est entier
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        qDebug() << "LitEnt - LitEnt";
        int somme = this->signe*valeur - lit2E->signe*lit2E->valeur;
        int s;
        if(somme >= 0)
            s = 1;
        else
            s = -1;
        return new LitteraleEntiere(s, abs(somme));
    }

    // Si le secon terme est réel
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {
        double somme = this->signe*valeur - lit2E->getSigne()*lit2E->getValeur();

        int s;
        if(somme>=0)
            s = 1;
        else
            s = -1;
        return new LitteraleReelle(s, abs(somme));
    }

    // Si le second terme est rationnel
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)){
        double somme =  this->signe*valeur * lit2E->getDenominateur().getValeur() - lit2E->getSigne() * lit2E->getNumerateur().getValeur();
        int s;
        if(somme >= 0)
            s = 1;
        else
            s = -1;
        return new LitteraleRationnelle(s, LitteraleEntiere(1, abs(somme)), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
    }

    // Si le second terme est complexe
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        LitteraleNumerique* partRe = lit2E->getReelle(); // IL FAUT UTILISER LE CONSTRUCTEUR PAR RECOPIE POUR NE PAS POINTER DEUX FOIS VERS LE MEME OBJET
        LitteraleNumerique* partIm = lit2E->getImaginaire(); // IDEM
        partIm->inverseSigne();
        return new LitteraleComplexe(dynamic_cast<LitteraleNumerique*>(*this - *partRe), lit2E->getImaginaire());
    }

}


// OPERATEUR * pour un premier terme entier
Litterale* LitteraleEntiere::operator*(Litterale& lit2){
    qDebug() << "ICI";

    // Si le second terme est entier
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {
        int res = valeur*lit2E->valeur;
        int s = signe * lit2E->getSigne();
        return new LitteraleEntiere(s, res);
    }

    // si le second terme est rationnel
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {
        unsigned int res = valeur * lit2E->getNumerateur().getValeur();
        int s = signe * lit2E->getSigne();
        return new LitteraleRationnelle(s, LitteraleEntiere(1, res), LitteraleEntiere(1, lit2E->getDenominateur().getValeur()));
        // appeler la methode simplifier simplifier
    }

    // Si le second terme est reel
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {
        double res = valeur * lit2E->getValeur();
        int s = signe * lit2E->getSigne();
        return new LitteraleReelle(s, res);
    }

   else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        int sR = signe * lit2E->getReelle()->getSigne();
        int sI = signe * lit2E->getImaginaire()->getSigne();

        //LitteraleNumerique* partR = *this * lit2E->getReelle(); IN PROGRESS :)

        //unsigned int valR = valeur * lit2E->getReelle()->getValeur(); -> Pas possible car pas de fonction getValeur pour litNumerique
        //unsigned int valI = valeur * lit2E->getImaginaire()->getValeur();

        //return new LitteraleComplexe(1, LitteraleEntiere(sR, valR), LitteraleEntiere(sI, valI));
    }

}


// OPERATEUR / pour un premier terme entier
Litterale* LitteraleEntiere::operator/(Litterale& lit2){
    // this/lit2

    // Si le second terme est un entier
    if(LitteraleEntiere *lit2E = dynamic_cast<LitteraleEntiere*>(&lit2)) {

       int s = this->signe * lit2E->getSigne();

       if (valeur % lit2E->valeur == 0)
            return new LitteraleEntiere(s, valeur/lit2E->valeur);
        else
            return new LitteraleRationnelle(s, LitteraleEntiere(1, valeur), LitteraleEntiere(1, lit2E->valeur));
    }

    // Si le second terme est réel
    else if(LitteraleReelle *lit2E = dynamic_cast<LitteraleReelle*>(&lit2)) {

        double div =valeur/lit2E->getValeur();
        int s = this->signe * lit2E->getSigne();
        return new LitteraleReelle(s, div);
    }

    // Si le second terme est rationnel
    else if(LitteraleRationnelle *lit2E = dynamic_cast<LitteraleRationnelle*>(&lit2)) {

        unsigned int nomi = valeur * lit2E->getDenominateur().getValeur();
        unsigned int deno = lit2E->getNumerateur().getValeur();

        int s = this->signe * lit2E->getSigne();

        if (nomi % deno == 0)
             return new LitteraleEntiere(s, nomi/deno);
         else
             return new LitteraleRationnelle(s, LitteraleEntiere(1, nomi), LitteraleEntiere(1, deno));
    }

    // Si le second terme est complexe
    else if(LitteraleComplexe *lit2E = dynamic_cast<LitteraleComplexe*>(&lit2)) {

        /*double sommeR = this->signe*valeur / lit2E->getReelle().getSigne() * lit2E->getReelle()->getValeur();
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

        return new LitteraleComplexe(1, LitteraleEntiere(negR, sommeR), LitteraleEntiere(negI, sommeI));*/
    }

}



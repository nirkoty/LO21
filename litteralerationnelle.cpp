#include "litteralerationnelle.h"
#include "litteralereelle.h"
#include "litteraleentiere.h"
#include "QDebug"


LitteraleRationnelle::LitteraleRationnelle(int s, LitteraleEntiere nom, LitteraleEntiere denom) : LitteraleNumerique(s), numerateur(nom), denominateur(denom)
{

}

LitteraleRationnelle::LitteraleRationnelle(QString input){
    if(input.left(1)=="-"){
        signe=1;
        input=input.remove(0,1);
    }
    QStringList reels = input.split("/");
    qDebug()<<reels.at(0);
    qDebug()<<reels.at(1);
    numerateur=LitteraleEntiere(reels.at(0));
    denominateur=LitteraleEntiere(reels.at(1));
}

void LitteraleRationnelle::simplifier(){


}

QString LitteraleRationnelle::toString(){
    if(signe==1)
        return QString(numerateur.toString()+"/"+denominateur.toString());
    else
        return QString("-"+numerateur.toString()+"/"+denominateur.toString());
 }


bool LitteraleRationnelle::estLitteraleRationnelle(QString bloc){

    if(bloc.indexOf('/')!=-1){
        if(bloc.indexOf('-')!=-1)
            bloc = bloc.remove('-');

        QString strNominateur =  bloc.section('/', 0, 0);
        QString strDenominateur =  bloc.section('/', 1, 1);


        qDebug() <<bloc << strNominateur << strDenominateur;
        return (LitteraleEntiere::estLitteraleEntiere(strNominateur) && LitteraleEntiere::estLitteraleEntiere(strDenominateur));

    }
    else
        return false;

}





Litterale* LitteraleRationnelle::operator+(Litterale& lit2){

    // Si le second terme est un entier
    if(LitteraleEntiere *lit2cast = dynamic_cast<LitteraleEntiere*>(&lit2)) {

        int s = signe * lit2cast->getSigne();
        unsigned int newNumerateur = denominateur.getValeur() * lit2cast->getValeur() + numerateur.getValeur();
        unsigned int newDenominateur = denominateur.getValeur();
        return new LitteraleRationnelle(s, LitteraleEntiere(1, newNumerateur), LitteraleEntiere(1, newDenominateur));
    }

    // Si le second terme est un rationnel
    else if(LitteraleRationnelle *lit2cast = dynamic_cast<LitteraleRationnelle*>(&lit2)) {

        int s = signe * lit2cast->getSigne();
        unsigned int newNumerateur = denominateur.getValeur() * lit2cast->getNumerateur().getValeur() + numerateur.getValeur() * lit2cast->getDenominateur().getValeur();
        unsigned int newDenominateur = denominateur.getValeur() * lit2cast->getDenominateur().getValeur();
        return new LitteraleRationnelle(s, LitteraleEntiere(1, newNumerateur), LitteraleEntiere(1, newDenominateur));
    }

    // Si le second terme est un réel
    else if(LitteraleReelle *lit2cast = dynamic_cast<LitteraleReelle*>(&lit2)) {

        int s = signe * lit2cast->getSigne();
        double res = numerateur.getValeur() / denominateur.getValeur(); // + lit2cast->getValeur();
        return new LitteraleReelle(s, res);
    }

}



Litterale* LitteraleRationnelle::operator*(Litterale& lit2){return this;}
Litterale* LitteraleRationnelle::operator/(Litterale& lit2){return this;}
Litterale* LitteraleRationnelle::operator-(Litterale& lit2){return this;}

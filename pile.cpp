#include "pile.h"
#include <typeinfo>
#include "litteraleentiere.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include "litteralecomplexe.h"
#include "litteraleprogramme.h"
#include "litteraleexpression.h"

Pile::Pile() : modeleProgrammes(new QStringListModel)
{

}


void Pile::empiler(Litterale *lit){

    vecteur.push_back(lit);
    qDebug()<<"test";
    //qDebug()<<typeid(*lit).name();

    //LitteraleEntiere* t = dynamic_cast<LitteraleEntiere*> (lit);

    //qDebug()<<lit;
    //qDebug()<<typeid(*t).name();
    //qDebug()<<t->getValeur();
    qDebug()<<lit->toString();

    modeleProgrammes->insertRow(modeleProgrammes->rowCount());
    QModelIndex index = modeleProgrammes->index(modeleProgrammes->rowCount()-1);
    modeleProgrammes->setData(index, lit->toString());

}

void Pile::setView(QListView *viewPile){
    view=viewPile;
    view->setModel(modeleProgrammes);


}

Litterale* Pile::depiler(){
    modeleProgrammes->removeRow(vecteur.size()-1);
    Litterale* tmp = vecteur.at(vecteur.size()-1);
    vecteur.pop_back();
    return tmp;
}

void Pile::dupliquer(){
    Litterale* last = vecteur.at(vecteur.size()-1);

    if(dynamic_cast<LitteraleEntiere*>(last)){
        LitteraleEntiere* dup= dynamic_cast<LitteraleEntiere*>(last);
        empiler(new LitteraleEntiere(dup->getSigne(), dup->getValeur()));
    }
    else if(dynamic_cast<LitteraleReelle*>(last)){
        LitteraleReelle* dup= dynamic_cast<LitteraleReelle*>(last);
        empiler(new LitteraleReelle(dup->getSigne(), dup->getValeur()));
    }
    if(dynamic_cast<LitteraleRationnelle*>(last)){
        LitteraleRationnelle* dup= dynamic_cast<LitteraleRationnelle*>(last);
        empiler(new LitteraleRationnelle(dup->getSigne(), dup->getNominateur(), dup->getDenominateur()));
    }
    if(dynamic_cast<LitteraleComplexe*>(last)){
        LitteraleComplexe* dup= dynamic_cast<LitteraleComplexe*>(last);
        empiler(new LitteraleComplexe(dup->getSigne(), dup->getReelle(), dup->getImaginaire()));
    }
    if(dynamic_cast<LitteraleProgramme*>(last)){
        LitteraleProgramme* dup= dynamic_cast<LitteraleProgramme*>(last);
        empiler(new LitteraleProgramme(dup->getStrProgramme()));
    }
    if(dynamic_cast<LitteraleExpression*>(last)){
        LitteraleExpression* dup= dynamic_cast<LitteraleExpression*>(last);
        empiler(new LitteraleExpression(dup->toString()));
    }

}

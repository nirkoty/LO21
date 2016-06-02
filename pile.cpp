#include "pile.h"
#include <typeinfo>
#include "litteraleentiere.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include "litteralecomplexe.h"
#include "litteraleprogramme.h"
#include "litteraleexpression.h"

Pile::Pile() : modeleProgrammes(new QStringListModel), indicePiles(0)
{
    savedStates.push_back(vecteur);
}


void Pile::empiler(Litterale *lit){

    qDebug()<<"empiler";
    vecteur.push_back(lit);

    modeleProgrammes->insertRow(modeleProgrammes->rowCount());
    QModelIndex index = modeleProgrammes->index(modeleProgrammes->rowCount()-1);
    modeleProgrammes->setData(index, lit->toString());
    qDebug()<<"empiler2 "<<taille();
    savePile();

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

    qDebug()<<last->toString();

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


void Pile::swap(){
    Litterale* lit1 = depiler();
    Litterale* lit2 = depiler();
    empiler(lit1);
    empiler(lit2);
}

void Pile::clear(){
    while(vecteur.size()>0){
        delete depiler();
    }
}

void Pile::savePile(){
    qDebug()<<indicePiles;
    if(indicePiles<savedStates.size()-1){
        unsigned int taille=savedStates.size();
        for(unsigned int i=indicePiles+1 ; i<taille; i++){
            qDebug()<<"pop_back";
            savedStates.pop_back();
        }
    }



    savedStates.push_back(vecteur);
    indicePiles++;
      qDebug()<<indicePiles<<"   "<<savedStates.size();
    qDebug()<<"taille save "<<savedStates.size();
}

void Pile::undo(){
    qDebug()<<"indicepiles  "<<indicePiles;
    vecteur = savedStates.at(--indicePiles);
    qDebug()<<"taille undo "<<vecteur.size();
    afficherPile();

}

void Pile::redo(){
    vecteur = savedStates.at(++indicePiles);
    qDebug()<<"taille redo "<<vecteur.size();
    afficherPile();
}

void Pile::afficherPile(){

    delete modeleProgrammes;
    modeleProgrammes = new QStringListModel();
    Litterale* tmp;

    for(int i=0; i<vecteur.size(); i++){
        tmp = vecteur.at(i);
        modeleProgrammes->insertRow(modeleProgrammes->rowCount());
        QModelIndex index = modeleProgrammes->index(modeleProgrammes->rowCount()-1);
        modeleProgrammes->setData(index, tmp->toString());
    }

    view->setModel(modeleProgrammes);

}

void Pile::empilerLastArgs(){
    for(unsigned int i=0; i<lastArgs.size(); i++)
    {
        empiler(lastArgs.at(i));
    }
    savePile();
}

void Pile::setLastArgs(std::vector<Litterale *> args){
    lastArgs=args;
}

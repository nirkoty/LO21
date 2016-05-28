#include "pile.h"
#include <typeinfo>
#include "litteraleentiere.h"

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

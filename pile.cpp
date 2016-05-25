#include "pile.h"
#include <typeinfo>
#include "litteraleentiere.h"

Pile::Pile()
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

    view->append(lit->toString());
}

void Pile::setView(QTextEdit *viewPile){
    view=viewPile;

}

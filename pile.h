#ifndef PILE_H
#define PILE_H


#include "litterale.h"
#include <vector>
#include <QTextEdit>
#include <QDebug>
#include <QListView>
#include <QStringListModel>

class Pile
{
public:
    Pile();
    void empiler(Litterale* lit);
    void setView(QListView* viewPile);
    Litterale* depiler();
    int taille() const {return vecteur.size();}
    void dupliquer();

private:
    std::vector<Litterale*>vecteur;
    QListView* view;
    QStringListModel *modeleProgrammes;

};

#endif // PILE_H

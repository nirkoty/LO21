#ifndef PILE_H
#define PILE_H


#include "litterale.h"
#include <vector>
#include <QTextEdit>
#include <QDebug>

class Pile
{
public:
    Pile();
    void empiler(Litterale* lit);
    void setView(QTextEdit* viewPile);
    int taille() const {return vecteur.size();}

private:
    std::vector<Litterale*>vecteur;
    QTextEdit* view;

};

#endif // PILE_H

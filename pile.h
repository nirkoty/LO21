#ifndef PILE_H
#define PILE_H


#include "litterale.h"
#include <vector>
#include <QTextEdit>
#include <QDebug>
#include <QListView>
#include <QStringListModel>


class Pile;
class Manager; // il faut prédéclarer les classes ici pour qu'elles puissent s'appeller entre elles
#include "manager.h"

class Pile
{
public:
    Pile(Manager *man);
    void empiler(Litterale* lit);
    void setView(QListView* viewPile);
    Litterale* depiler();
    int taille() const {return vecteur.size();}
    void dupliquer();
    void swap();
    void clear();
    void savePile();
    void undo();
    void redo();
    void afficherPile();
    void empilerLastArgs();
    void setLastArgs(std::vector<QString> args);


private:
    std::vector<Litterale*>vecteur;
    std::vector<std::vector<Litterale*> > savedStates;
    std::vector<QString> lastArgs;
    int indicePiles;
    QListView* view;
    QStringListModel *modeleProgrammes;
    Manager* manager;


};

#endif // PILE_H

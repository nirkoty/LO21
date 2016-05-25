#include "manager.h"

Manager::Manager(Pile &p) : pile(p)
{

}


bool Manager::interpreter(QString input){

    //qDebug()<<input;
    int nbAEmpiler;


    if(input.length()>0){
        QString lastChar = input.at(input.length()-1);
        qDebug()<<lastChar;

         QStringList operandes = input.split(" ");
         if(Operateur::estOperateur(operandes.last()))
             nbAEmpiler = operandes.length()-1;
         else
             nbAEmpiler = operandes.length();
         for(int i=0; i<nbAEmpiler; i++)
         {
             if(LitteraleReelle::estLitteraleReelle(operandes.at(i)))
                 pile.empiler(new LitteraleReelle(operandes.at(i)));
             else if(LitteraleProgramme::estLitteraleProgramme(operandes.at(i)))
                 pile.empiler(new LitteraleProgramme(operandes.at(i)));
              if(LitteraleEntiere::estLitteraleEntiere(operandes.at(i)))
                 pile.empiler(new LitteraleEntiere(operandes.at(i)));
             else
                 qDebug()<<"erreur empilement";
             qDebug()<<pile.taille();
         }

         if(nbAEmpiler==operandes.length())
             return true;
         else{
            executer(Operateur(operandes.last()));
         }

    }
    else
        return false;
}

void Manager::executer(Operateur operateur){
    std::vector<Litterale*> litterales;
    for(unsigned int i=0; i<operateur.getArite(); i++){

    }
}

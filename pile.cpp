#include "pile.h"
#include <typeinfo>
#include "litteraleentiere.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include "litteralecomplexe.h"
#include "litteraleprogramme.h"
#include "litteraleexpression.h"

Pile::Pile(Manager *man) : modeleProgrammes(new QStringListModel), indicePiles(0), manager(man)
{
    QXmlStreamReader xmlReader;
    QFile filePile("pile.xml");
    filePile.open(QFile::ReadOnly);
    xmlReader.setDevice(&filePile);



    xmlReader.readNext();
    QString tmp;

    while(!xmlReader.atEnd() && !xmlReader.hasError()) {

            QXmlStreamReader::TokenType token = xmlReader.readNext();

            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }
            if(token == QXmlStreamReader::StartElement) {

                    if(xmlReader.name() == "string") {
                         tmp= xmlReader.readElementText();
                         if(LitteraleReelle::estLitteraleReelle(tmp))
                             empiler(new LitteraleReelle(tmp));
                         else if (LitteraleEntiere::estLitteraleEntiere(tmp))
                             empiler(new LitteraleEntiere(tmp));
                         else if(LitteraleRationnelle::estLitteraleRationnelle(tmp)){
                             empiler(new LitteraleRationnelle(tmp));
                         }
                         else if (LitteraleProgramme::estLitteraleProgramme(tmp))
                             empiler(new LitteraleProgramme(tmp));
                         else if (LitteraleExpression::estLitteraleExpression(tmp))
                            empiler(new LitteraleExpression(tmp, manager));
                    }
            }
    }
    filePile.close();
    savedStates.push_back(vecteur);
}


void Pile::empiler(Litterale *lit){

    vecteur.push_back(lit);

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
        empiler(new LitteraleComplexe(dup->getReelle(), dup->getImaginaire()));
    }
    if(dynamic_cast<LitteraleProgramme*>(last)){
        LitteraleProgramme* dup= dynamic_cast<LitteraleProgramme*>(last);
        empiler(new LitteraleProgramme(dup->getStrProgramme()));
    }
    if(dynamic_cast<LitteraleExpression*>(last)){
        LitteraleExpression* dup= dynamic_cast<LitteraleExpression*>(last);
        empiler(new LitteraleExpression(dup->toString(), manager));
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

    if(indicePiles<savedStates.size()-1){
        unsigned int taille=savedStates.size();
        for(unsigned int i=indicePiles+1 ; i<taille; i++){
            savedStates.pop_back();
        }
    }

    savedStates.push_back(vecteur);
    qDebug()<<"savePiles";
    indicePiles++;


    QString path("pile.xml");
    QFile file(path);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("litterales");
    Litterale* tmp;
    for(unsigned int i=0; i<vecteur.size(); i++){

        tmp=vecteur.at(i);
        xmlWriter.writeStartElement("litterale");
        xmlWriter.writeTextElement("string", tmp->toString());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();

}

void Pile::undo(){

    vecteur = savedStates.at(--indicePiles);
    afficherPile();

}

void Pile::redo(){
    vecteur = savedStates.at(++indicePiles);

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

        if(LitteraleEntiere::estLitteraleEntiere(lastArgs.at(i)))
            empiler(new LitteraleEntiere(lastArgs.at(i)));

        if(LitteraleReelle::estLitteraleReelle(lastArgs.at(i)))
            empiler(new LitteraleReelle(lastArgs.at(i)));

        if(LitteraleRationnelle::estLitteraleRationnelle(lastArgs.at(i)))
            empiler(new LitteraleRationnelle(lastArgs.at(i)));

        if(LitteraleComplexe::estLitteraleComplexe(lastArgs.at(i)))
            empiler(new LitteraleComplexe(lastArgs.at(i)));

        if(LitteraleExpression::estLitteraleExpression(lastArgs.at(i)))
            empiler(new LitteraleExpression(lastArgs.at(i), manager));
        if(LitteraleProgramme::estLitteraleProgramme(lastArgs.at(i)))
            empiler(new LitteraleProgramme(lastArgs.at(i)));
    }
}

void Pile::setLastArgs(std::vector<QString> args){
    lastArgs=args;
}

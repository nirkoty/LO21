#include "computerexception.h"



const void ComputerException::what() const throw(){
    QMessageBox boiteErreur;
    boiteErreur.setText(QString(info));
    boiteErreur.exec();
}

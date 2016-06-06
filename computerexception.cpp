#include "computerexception.h"



const void ComputerException::what() const throw(){
    qDebug()<<"test "<<info;
    QMessageBox boiteErreur;
    boiteErreur.setText(QString(info));
    boiteErreur.exec();
}

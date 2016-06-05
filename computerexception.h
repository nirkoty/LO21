#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H


#include <stdexcept>
#include <QDebug>
#include <QMessageBox>
#include <QString>

using namespace std;
class ComputerException
{
public:
    char* info;
    public:
    ComputerException(char* i) throw():info(i){}
    virtual ~ComputerException() throw(){}
    const void what() const throw();
};

#endif // COMPUTEREXCEPTION_H

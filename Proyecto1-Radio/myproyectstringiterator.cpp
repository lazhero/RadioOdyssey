#include "myproyectstringiterator.h"

MyProyectStringIterator::MyProyectStringIterator()
{

}

std::string MyProyectStringIterator::iterateString(std::string data)
{
    std::string returnString;
    while(returnString.length()<BeforeDigits-1){
        returnString.append(before);
    }
    returnString.append(data);
    returnString.append(after);
    return returnString;

}

std::string MyProyectStringIterator::getBefore()
{
    return this->before;

}
std::string MyProyectStringIterator::getAfter(){
    return this->after;
}
void MyProyectStringIterator::setAfter(std::string data){
    this->after=data;

}
void MyProyectStringIterator::setBefore(std::string data){
    this->before=data;
}

int MyProyectStringIterator::getBeforeDigits()
{
    return this->BeforeDigits;
}
void MyProyectStringIterator::setBeforeDigits(int data){
    this->BeforeDigits=data;
}


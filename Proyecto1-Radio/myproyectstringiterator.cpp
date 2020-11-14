#include "myproyectstringiterator.h"
/**
 * @brief MyProyectStringIterator::MyProyectStringIterator
 */
MyProyectStringIterator::MyProyectStringIterator()
{

}
/**
 * @brief MyProyectStringIterator::iterateString
 * @param data
 * @return
 */
std::string MyProyectStringIterator::iterateString(std::string data)
{
    std::string returnString;
    int algo=data.length();
    if (algo<=BeforeDigits){
        while(returnString.length()<BeforeDigits-data.length()){
            returnString.append(before);
        }
    }
   returnString.append(data);
    returnString.append(after);
    return returnString;

}
/**
 * @brief MyProyectStringIterator::getBefore
 * @return
 */
std::string MyProyectStringIterator::getBefore()
{
    return this->before;

}
/**
 * @brief MyProyectStringIterator::getAfter
 * @return
 */
std::string MyProyectStringIterator::getAfter(){
    return this->after;
}
/**
 * @brief MyProyectStringIterator::setAfter
 * @param data
 */
void MyProyectStringIterator::setAfter(std::string data){
    this->after=data;

}
/**
 * @brief MyProyectStringIterator::setBefore
 * @param data
 */
void MyProyectStringIterator::setBefore(std::string data){
    this->before=data;
}
/**
 * @brief MyProyectStringIterator::getBeforeDigits
 * @return
 */

int MyProyectStringIterator::getBeforeDigits()
{
    return this->BeforeDigits;
}
/**
 * @brief MyProyectStringIterator::setBeforeDigits
 * @param data
 */
void MyProyectStringIterator::setBeforeDigits(int data){
    this->BeforeDigits=data;
}


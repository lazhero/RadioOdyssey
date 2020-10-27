#include "pages.h"
int minLen;
Pages::Pages(int len)
{
    setListLen(len);
}
int Pages::getListLen(){
    return ListLen;
}
void Pages::setListLen(int len){

    if(lenVerification((len)))ListLen=len;
    else ListLen=minLen;
}

bool Pages::isFull()
{
    bool condition=Prev->getLen()==ListLen;
    condition&=Next->getLen()==ListLen;
    condition&=Actual->getLen()==ListLen;
    return condition;
}
void Pages::AddToBack(Song song){
    Prev->add(*new Song(song));
    iterateFront();
    if(this->Next->getLen()>ListLen)Next->erase(ListLen-1);


}
void Pages::AddToFront(Song song){
    Next->add(*new Song(song));
    iterateBack();
    if(this->Prev->getLen()>ListLen)Prev->erase(minIndex);
}
void Pages::iterateBack(){
    if(Next->getLen()>minLen){
        Actual->add(*Next->get(minIndex));
        Next->erase(minIndex);
    }
    if(Actual->getLen()>ListLen){
        Prev->add(*Actual->get(minIndex));
        Actual->erase(minIndex);
    }
}
void Pages::iterateFront(){
    if(Prev->getLen()>minLen){
        Actual->add(*Prev->get(Prev->getLen()-1));
        Prev->erase(Prev->getLen()-1);
    }
    if(Actual->getLen()>ListLen){
        Next->add(*Actual->get(Actual->getLen()-1));
        Actual->erase(Actual->getLen()-1);
    }
}
bool Pages::lenVerification(int data){
    return true;
}

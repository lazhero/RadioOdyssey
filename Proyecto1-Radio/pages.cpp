#include "pages.h"
int minLen;
Pages::Pages(int len)
{
    Actual=new DoubleList<Song>;
    Prev=new DoubleList<Song>;
    Next=new DoubleList<Song>;
    setListLen(len);
}
int Pages::getListLen(){
    return ListLen;
}
void Pages::setListLen(int len){

    if(!lenVerification((len)))return;
    int temp=ListLen;
    ListLen=len;
    if(temp>ListLen)DeleteLeftOver();
}

DoubleList<Song> *Pages::getActual()
{
    return this->Actual;
}

bool Pages::isFull()
{
    bool condition=Prev->getLen()==ListLen;
    condition&=Next->getLen()==ListLen;
    condition&=Actual->getLen()==ListLen;
    return condition;
}

void Pages::swap(int a, int b)
{
    if(a<0 || a>2 ||b <0 || b>2)return;
    int addition=a+b;
    DoubleList<Song>* temp;
    switch (addition) {
    case 1:
        temp=Prev;
        Prev=Actual;
        Actual=temp;
        break;
     case 2:
        temp=Prev;
        Prev=Next;
        Next=temp;

        break;
    case 3:
        temp=Actual;
        Actual=Next;
        Next=temp;
        break;
    }
}
void Pages::AddToBack(Song song){
    Prev->addFront(*new Song(song));
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

void Pages::DeleteLeftOver()
{
    bool iterador=true;
    Song* temp;
    while(Actual->getLen()>ListLen){
        if(iterador){
            temp=Actual->get(minIndex);
            Actual->erase(minIndex);
            Prev->add(*temp);

        }
        else{
            temp=Actual->get(Actual->getLen()-1);
            Actual->erase(Actual->getLen()-1);
            Next->addFront(*temp);

        }
        iterador= !iterador;
    }

    while(Prev->getLen()>ListLen){
        Prev->erase(minLen);
    }
    while (Next->getLen()>ListLen) {
        Next->erase(Next->getLen()-1);
    }
}
void Pages::iterateFront(){
    if(Prev->getLen()>minLen){
        Actual->addFront(*Prev->get(Prev->getLen()-1));
        Prev->erase(Prev->getLen()-1);
    }
    if(Actual->getLen()>ListLen){
        Next->addFront(*Actual->get(Actual->getLen()-1));
        Actual->erase(Actual->getLen()-1);
    }
}
bool Pages::lenVerification(int data){
    if(data<0)return false;
    return true;
}


#include "clikable_item.h"
#include <QListWidget>
Clikable_Item::Clikable_Item()
{

}

QString Clikable_Item::returnInfo(){
    return informacion;
}
QString Clikable_Item::getRname(){
    return realName;
}
void Clikable_Item::setInfo(QString valor){
    informacion=valor;

}
void Clikable_Item::setRname(QString valor){
    realName=valor;

}

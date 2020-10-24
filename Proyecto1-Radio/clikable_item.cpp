#include "clikable_item.h"
#include <QListWidget>
Clikable_Item::Clikable_Item()
{

}

QString Clikable_Item::returnInfo(){
    return informacion;
}
void Clikable_Item::setInfo(QString valor){
    informacion=valor;

}

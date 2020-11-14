#include "clikable_item.h"
#include <QListWidget>
/**
 * @brief Clikable_Item::Clikable_Item
 */
Clikable_Item::Clikable_Item()
{

}
/**
 * @brief Clikable_Item::returnInfo
 * @return
 */
QString Clikable_Item::returnInfo(){
    return informacion;
}
/**
 * @brief Clikable_Item::getRname
 * @return
 */
QString Clikable_Item::getRname(){
    return realName;
}
/**
 * @brief Clikable_Item::setInfo
 * @param valor
 */
void Clikable_Item::setInfo(QString valor){
    informacion=valor;

}
/**
 * @brief Clikable_Item::setRname
 * @param valor
 */
void Clikable_Item::setRname(QString valor){
    realName=valor;

}

#ifndef CLIKABLE_ITEM_H
#define CLIKABLE_ITEM_H

#include <QWidget>
#include <QListWidget>
class Clikable_Item :public QListWidgetItem
{
public:
    Clikable_Item();
    QString returnInfo();
    void setInfo(QString valor);
private:
    QString informacion;


};

#endif // CLIKABLE_ITEM_H

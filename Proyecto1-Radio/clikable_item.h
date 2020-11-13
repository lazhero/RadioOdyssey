#ifndef CLIKABLE_ITEM_H
#define CLIKABLE_ITEM_H

#include <QWidget>
#include <QListWidget>
class Clikable_Item :public QListWidgetItem
{
public:
    Clikable_Item();
    QString returnInfo();
    QString getRname();
    void setInfo(QString valor);
    void setRname(QString valor);

private:
    QString informacion;
    QString realName;


};

#endif // CLIKABLE_ITEM_H

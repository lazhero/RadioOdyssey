#ifndef WIDGET_H
#define WIDGET_H
#include <QMediaPlayer>
#include"musicplayer.h"
#include "clikable_item.h"
#include <QTimer>
#include<localfilegetter.h>
#include<cassettegallery.h>
#include"csvhandler.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_PlayB_clicked();
    void on_PlayB_2_clicked();
    void on_timeBar_valueChanged(int value);
    void on_timeBar_sliderMoved(int position);
    void on_directorios_itemClicked( QListWidgetItem *item);
    void on_vol_valueChanged(int value);
    void on_canciones_itemClicked(QListWidgetItem *item);
    void on_checkBox_stateChanged(int arg1);
    void reportScrollPosition();
    void on_canciones_activated(const QModelIndex &index);

private:

    bool playing;
    bool paginationMode;
    void updateScenario();
    void  updateTimebarMinMax();
    void addThingTo(QString listView,QString value ,QString name,QString realName);
    void insertListToListView( DoubleList<std::string> listilla,QString listView,DoubleList<QString>* DirList=NULL);
    AudioPlayer *player;
    Ui::Widget *ui;
    QTimer* timer;
    QString returnPointer(QString direction);
    QString convToMinutes(int miliseconds);
    QString calculateRealName(QString ruta);

    DoubleList<std::string> FixSongsNames(DoubleList<std::string> List);

    void setPaginationMode(bool state);
    CSVHandler* csv;
    CassetteGallery * gallery;
    stringIterator *iterator;
};
#endif

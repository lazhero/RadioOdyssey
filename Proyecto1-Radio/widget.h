#ifndef WIDGET_H
#define WIDGET_H
#include <QMediaPlayer>
#include"musicplayer.h"
#include <QWidget>
#include <QTimer>
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

private:
    bool playing;
    AudioPlayer *player;
    Ui::Widget *ui;
    void updateScenario();
    QTimer* timer;
    void  updateTimebarMinMax();
};
#endif

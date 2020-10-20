#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QDir>
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{

    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QDir().absoluteFilePath("../RadioOdyssey/Proyecto1-Radio/Resources/Music/testBach.mp3")));
    player->setVolume(50);

    playing=false;
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_PlayB_clicked()
{


    if(playing)
        {
         ui->PlayB->setText("Stop");
         player->stop();
        }
    else
        {
         ui->PlayB->setText("Play");
         player->play();
         //player->play();

        }
    playing=!playing;
}

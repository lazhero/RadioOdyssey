#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QDir>
#include<string>
QString PlayText="Play";
QString PauseText="Pause";
int starting_Vol=50;

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{

    player = new  MusicPlayer;
    player->setVolumen(starting_Vol);
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
         ui->PlayB->setText(PlayText);
         player->Pause();
        }
    else
        {
         ui->PlayB->setText(PauseText);
         player->Play();

        }
     playing=!playing;

}

void Widget::on_PlayB_2_clicked()
{
    player->Stop();
}

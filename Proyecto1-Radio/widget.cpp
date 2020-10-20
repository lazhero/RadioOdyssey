#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QDir>
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    QMediaPlayer *player;
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QDir().absoluteFilePath("../Proyecto1-Radio/Resources/Music/testBach.mp3")));
    player->setVolume(50);
    player->play();

    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include<localfilegetter.h>
#include <QDir>
#include<string>
#include<iostream>
QString PlayText="Play";
QString PauseText="Pause";
QString route="/home/lazh/QTproyects/Resources/fma/fma_small";
LocalfileGetter getter;
int starting_Vol=50;
int updateFramingConstant=150;
namespace s = std;
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{

    player = new  MusicPlayer;
    player->setVolumen(starting_Vol);
    playing=false;
    getter.setSource(route);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    timer = new QTimer(this); /// calls after X MILIseconds updateScenario who updates the slideBar and timeCount Label
      connect(timer, &QTimer::timeout,[&]
             {
                 if(playing){
                     updateScenario();
                 }
                 else{
                     timer->stop();
                 }
             });
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        player->addToPlayList(getter.getSong(ui->input->text()));
         player->Play();
         //empieza a actualizar el escenario
         updateTimebarMinMax();
         timer->start(updateFramingConstant);
         //////////////////////////////////
        }
     playing=!playing;

}

void Widget::on_PlayB_2_clicked()
{
    player->Stop();
    ui->timeBar->setValue(0);
    timer->stop();
}

/**
 * this updates some QObjects in gui after "UpdateFramingConstant"  time , like the time bar, the time counter label, ect
 * @brief Widget::updateScenario
 * @author Adrian Gonzalez
 * @return nothing
 *
 */

void Widget :: updateScenario(){
    QSlider* barra = ui->timeBar;
    float value =  barra->value();
    barra->setValue(value+updateFramingConstant);

}

/**
 * this updates the time bar min and maximun for matemathical movement of the slide
 * @brief Widget::updateTimebarMinMax
 * @author Adrian Gonzalez
 * @return nothing
 *
 */

void Widget ::updateTimebarMinMax(){
    QSlider* barra = ui->timeBar;
    /////////////////////////////////////////////// ESTO ES PARA CUANDO SELECCIONE LA CANCION
    barra->setMinimum(0);
    barra->setMaximum(player->currentMediaDuration());
    ///////////////////////////////////////////////
}

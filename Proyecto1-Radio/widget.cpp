#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QDir>
#include<string>
QString PlayText="Play";
QString PauseText="Pause";
int starting_Vol=50;
int updateFramingConstant=150;
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{

    player = new  MusicPlayer;
    player->setVolumen(starting_Vol);
    playing=false;


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

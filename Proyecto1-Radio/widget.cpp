#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include<localfilegetter.h>
#include <QDir>
#include<string>
#include<iostream>

#include "sys/types.h"
#include "sys/sysinfo.h"

QString PlayText="Play";
QString PauseText="Pause";
QString route="/home/lazh/QTproyects/Resources/fma/fma_small";
//QString route="/home/adrian/Escritorio/musica";
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

             });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ui->setupUi(this);

    ui->vol->setValue(starting_Vol);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_PlayB_clicked(){

    if(playing)// if audio is being playing right now
        {
             ui->PlayB->setText(PlayText);
             player->Pause();
             playing=!playing;

        }
    else    //if there is no audio
        {

         ui->PlayB->setText(PauseText);

         player->addToPlayList(getter.getSong(ui->input->text()));
         player->Play();


         //empieza a actualizar el escenario///////

             playing=!playing;
             timer->start(updateFramingConstant);
         //////////////////////////////////////////
        }


}
/**
 * Dettects button clicked and stop the song
 * @brief Widget::on_PlayB_2_clicked
 */
void Widget::on_PlayB_2_clicked(){
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
    barra->setMaximum(player->currentMediaDuration());



    /////////////Calculo de memoria en uso
    /*
    struct sysinfo memInfo;
    sysinfo (&memInfo);
    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    //Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
    s::cout<<virtualMemUsed<< s::endl;
    ui->MemoryBar->setValue(virtualMemUsed);
    */
    /////////////Calculo de memoria en uso

    //s::cout<<"hola"<< s::endl;
}

/**
 * this updates the time bar min and maximun for matemathical movement of the slide
 * @brief Widget::updateTimebarMinMax
 * @author Adrian Gonzalez
 * @return nothing
 *
 */

void Widget::on_timeBar_valueChanged(int value){
        QString dur=  convToMinutes(ui->timeBar->maximum());
                dur.append("/");
        ui->Duration->setText(dur);
        ui->currentTIME->setText(convToMinutes(ui->timeBar->maximum()-value));

        //adelanta o atrasa la cancion



}

/**
 * convert miliseconds to minutes
 * @brief  Widget:: convToMinutes
 * @author Adrian Gonzalez
 * @return nothing
 * @param int
 */
QString Widget:: convToMinutes(int miliseconds){
            int seconds= miliseconds/1000;
            int minutes= seconds/60;
            seconds-= minutes*60;
            QString result= QString::number(minutes).append(":").append(QString::number(seconds));
            return result;
    }
/**
 * Dettecs any on purpose movement of the timebar and update the current position of the song
 * @brief Widget::on_timeBar_sliderMoved
 * @param position
 */
void Widget::on_timeBar_sliderMoved(int position)
{
            player->setTime(position);
}

/**
 * Dettecs any on purpose movement of the volumebar and update the current volume
 * @brief Widget::on_vol_valueChanged
 * @param value
 */

void Widget::on_vol_valueChanged(int value)
{
    player->setVolumen(value);

    //std::cout<<"hola "<<value<< std::endl;
}

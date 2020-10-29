#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include<localfilegetter.h>
#include <QDir>
#include<string>
#include<iostream>
#include<myproyectstringiterator.h>
#include"csvhandler.h"
#include<localfilegetter.h>
#include<csvsorting.h>
#include<myproyectstringiterator.h>


#include "sys/types.h"
#include "sys/sysinfo.h"
#include "clikable_item.h"
#include<DoubleList/InsertionSort.hpp>


QString PlayText="Play";
QString PauseText="Pause";
QString route="/home/lazh/QTproyects/Resources/fma/fma_small";
//QString route="/home/adrian/Escritorio/Musica";
QString route2="/home/lazh/QTproyects/Resources/fma/fma_metadata/raw_tracks.csv";
int songPosition=0;


int artistPosition=5;
int albumPosition=2;
int genrePosition=artistPosition;

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

    LocalfileGetter *myFileGetter= new LocalfileGetter;
    myFileGetter->setSource(route);
    DoubleList<std::string> *myList=myFileGetter->getDirectoryList();

    //DoubleList<std::string> *myList= new DoubleList<std::string>;


    this->csv=new CSVHandler;
    this->csv->setFileDirectory(route2.toStdString());
    MyProyectStringIterator* myIterator=new MyProyectStringIterator;
    myIterator->setAfter(".mp3");
    myIterator->setBefore("0");
    myIterator->setBeforeDigits(5);
    this->iterator=myIterator;
    gallery=NULL;

    ui->setupUi(this);
    ui->vol->setValue(starting_Vol);

    //iniciado de directorios
    insertListToListView(*myList,"carpetas");

    //


}

Widget::~Widget()
{
    delete ui;
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
 * Adds items to both list view
 * @brief Widget::addThingTo
 * @param listView
 * @param dir
 * @param name
 */
void Widget::addThingTo(QString listView ,QString dir,QString name){

    Clikable_Item* newItem= new Clikable_Item;

    newItem->setInfo(dir);        //direccion a seguir
    newItem->setText(name);       //nombre visible
    if(listView=="carpetas")
    {
        ui->directorios->addItem(newItem);
    }
   if(listView=="canciones"){

        ui->canciones->addItem(newItem);
   }






}
QString Widget::calculateRealName(QString ruta){

    QStringList aux= ruta.split("/");
    QString resultado= aux.at(aux.length()-1);
    aux= resultado.split(".");
    resultado=aux.at(0);
    return resultado;



}

DoubleList<std::string> Widget::FixSongsNames(DoubleList<std::string> List)
{
    QString dir_info;
    QString dir_nombre;
    std::string Name;
    DoubleList<std::string> ReturnList;
    for(int i=0;i<List.getLen();i++){
        dir_info= QString::fromStdString(List.get(i)->data());
        dir_nombre= calculateRealName(dir_info);
        while(dir_nombre.left(1)=="0"){
            dir_nombre=dir_nombre.right(dir_nombre.length()-1);
         }
        dir_nombre= calculateRealName(dir_nombre);
        Name=dir_nombre.toStdString();
        ReturnList.add(Name);


    }
    return ReturnList;

}

void Widget::insertListToListView( DoubleList<std::string> listilla,QString listView){

     if(listView!="canciones")sort(&listilla);
     this->csv->startReading();
    for (int i=0; i< listilla.getLen();i++ ){

        QString dir_info= QString::fromStdString(listilla.get(i)->data());
        QString dir_nombre= calculateRealName(dir_info);
        if(listView=="canciones"){
            std::cout<<"satanas"<<std::endl;
        }



        addThingTo(listView,dir_info,dir_nombre);
        //addThingTo("carpetas",QString::number(123),QString::number(123));


    }


}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////////////////////


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
 * Dettecs any on purpose movement of the volumebar and update the current volume
 * @brief Widget::on_vol_valueChanged
 * @param value
 */

void Widget::on_vol_valueChanged(int value){
    player->setVolumen(value);
    //DUMMY TEST HERE addThingTo("carpetas",QString::number(value),QString::number(value));
    //std::cout<<"hola "<<value<< std::endl;
}


/**
 * @brief Widget::on_directorios_itemClicked
 * @param item
 */

void Widget::on_directorios_itemClicked( QListWidgetItem *item)
{
    Clikable_Item *algo= dynamic_cast<Clikable_Item*>(item)  ;

    LocalfileGetter *myFileGetter= new LocalfileGetter;
    getter.setSouce(algo->returnInfo().toStdString());
    myFileGetter->setSource(algo->returnInfo());

    if(gallery!=NULL)free(gallery);
    gallery=new CassetteGallery(15);

    gallery->setAlbumPosition(albumPosition);
    gallery->setArtistPosition(artistPosition);\
    gallery->setGenrePosition(genrePosition);
    gallery->setRequestLen(15);
    gallery->setCsvDir(route2.toStdString());
    gallery->setIterator(this->iterator);
    gallery->setSourceDir(algo->returnInfo().toStdString());
    DoubleList<Song>* SongList=gallery->getActualList();
    DoubleList<std::string>* List=new DoubleList<std::string>;
    std::string tempString;
    for(int i=0;i<SongList->getLen();i++){
        tempString=SongList->get(i)->toString();
        List->add(tempString);
    }
     ui->canciones->clear();//LIMPIA LA VARA
    insertListToListView(*List,"canciones");


   // insertListToListView(*myList2,"canciones");


}



void Widget::on_canciones_itemClicked(QListWidgetItem *item)
{
        Clikable_Item *algo= dynamic_cast<Clikable_Item*>(item);
        player->addToPlayList(getter.getSong(algo->text()));
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
 * initialize ,stops and resume songs
 * @brief Widget::on_PlayB_clicked
 */
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

         //player->addToPlayList(getter.getSong(ui->input->text()));///////HERE HERE
         player->Play();


         //empieza a actualizar el escenario///////

             playing=!playing;
             timer->start(updateFramingConstant);
         //////////////////////////////////////////
        }

}
/**
 * Dettecs any on purpose movement of the timebar and update the current position of the song
 * @brief Widget::on_timeBar_sliderMoved
 * @param position
 */
void Widget::on_timeBar_sliderMoved(int position){
            player->setTime(position);
}


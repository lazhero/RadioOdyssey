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
#include<QResizeEvent>
#include <QScrollBar>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "clikable_item.h"
#include<DoubleList/InsertionSort.hpp>


QString PlayText="Play";
QString PauseText="Pause";
std::string AllString="All";
//QString route="/home/adrian/Escritorio/Musica";
//QString route2="/home/adrian/Escritorio/Musica/fma_metadata/raw_tracks.csv";
QString DirectoriesID="carpetas";
QString SongsID="canciones";
QString route="/home/lazh/QTproyects/Resources/fma/Out";
QString route2="/home/lazh/QTproyects/Resources/fma/fma_metadata/raw_tracks.csv";

LocalfileGetter getter;
int songPosition=0;
int starting_Vol=50;
int updateFramingConstant=150;
int SongsInMemory=10;
float sizeItemRelationConstant=480/10;  //for each 480 pixels  10 items fits
int artistPosition=5;
int albumPosition=2;
int genrePosition=artistPosition;

namespace s = std;


Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    //instancias
    this->csv=new CSVHandler;
    player = new  MusicPlayer;
    timer  = new  QTimer(this);
    LocalfileGetter *myFileGetter= new LocalfileGetter;

    //valores iniciales
    playing=false;
    getter.setSource(route);
    myFileGetter->setSource(route);
    player->setVolumen(starting_Vol);
    //maxVisibleItems=3;//quitar esto despues


    this->csv=new CSVHandler;
    this->csv->setFileDirectory(route2.toStdString());
    MyProyectStringIterator* myIterator=new MyProyectStringIterator;
    myIterator->setAfter(".mp3");
    myIterator->setBefore("0");
    myIterator->setBeforeDigits(6);
    this->iterator=myIterator;
    gallery=NULL;

    ui->setupUi(this);
    ui->vol->setValue(starting_Vol);


    //starting all song Gallery
    allSongGallery=new AllSongsGallery;
    allSongGallery->setIterator(*myIterator);
    allSongGallery->setAlbumPosition(albumPosition);
    allSongGallery->setArtistPosition(artistPosition);
    allSongGallery->setGenrePosition(genrePosition);
    allSongGallery->setNamePosition(songPosition);


    //conexiones
    connect(ui->canciones->verticalScrollBar(), &QScrollBar::valueChanged, [&]{reportScrollPosition();}  );
    connect(timer, &QTimer::timeout,[&]{if(playing)updateScenario();});

    //iniciado de directorios
    DoubleList<std::string> *myList = myFileGetter->getDirectoryList();
   // this->csv->setFileDirectory(route2.toStdString());
    insertListToListView(*myList,DirectoriesID);
    maxVisibleItems=this->ui->canciones->size().height()/sizeItemRelationConstant;

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

    struct sysinfo memInfo;
    sysinfo (&memInfo);
    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    //s::cout<<virtualMemUsed<< s::endl;
    ui->Memory->setText(QString::number(virtualMemUsed/1048576) +"mb");

    /////////////Calculo de memoria en uso


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
void Widget::addThingTo(QString listView ,QString dir,QString name,QString realName){

    Clikable_Item* newItem= new Clikable_Item;

    newItem->setInfo(dir);        //direccion a seguir
    newItem->setText(name);       //nombre visible

    if(listView==DirectoriesID){
        ui->directorios->addItem(newItem);
    }
    if(listView==SongsID){
        newItem->setRname(realName);
        ui->canciones->addItem(newItem);
    }



}
/**
 * Remove all routes prefixes
 * @brief Widget::calculateRealName
 * @param ruta
 * @return
 */
QString Widget::calculateRealName(QString ruta){

    QStringList aux= ruta.split("/");
    QString resultado= aux.at(aux.length()-1);
    aux= resultado.split(".");
    resultado=aux.at(0);
    return resultado;



}
/**
 * Fix all visual issues with songs in a list
 *  @brief Widget::FixSongsNames
 * @param List
 * @return
 */
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
/**
* Insert a entire directory list into  a Listview
 * @brief Widget::insertListToListView
 * @param listilla
 * @param listView
 */
void Widget::insertListToListView( DoubleList<std::string> listilla,QString listView,DoubleList<QString>* DirList){

     //if(listView!=SongsID)sort(&listilla);
     this->csv->startReading();
    for (int i=0; i< listilla.getLen();i++ ){
        QString temp;
        QString dir_info= QString::fromStdString(listilla.get(i)->data());
        QString dir_nombre= calculateRealName(dir_info);
        if(listView==SongsID){
            temp=*DirList->get(i);
            dir_info=temp;

            //std::cout<<"El texto es "<<temp.toStdString()<<std::endl;
        }


        addThingTo(listView,dir_info,dir_nombre,temp);
        //addThingTo("carpetas",QString::number(123),QString::number(123));


    }
}

/**
 * @brief Widget::resizeEvent
 * @param event
 */
void Widget::resizeEvent(QResizeEvent* event){

      maxVisibleItems=this->ui->canciones->size().height()/sizeItemRelationConstant;
      //maxVisibleItems=3; //quitar esto despues
      s::cout<<"estas viendo: "<< maxVisibleItems<<" items"<<"tamaño es :"<< this->size().height()<<s::endl;
      QWidget::resizeEvent(event);
    }


/**
 * @brief Widget::updateSongview
 */
void Widget::updateSongview(){
        DoubleList<Song>* SongList=gallery->getActualList();
        DoubleList<std::string>* List=new DoubleList<std::string>;
        DoubleList<QString> * DirList=new DoubleList<QString>;
        std::string tempString;
        QString tempQString;

        for(int i=0;i<SongList->getLen();i++){
            tempString=SongList->get(i)->toString();
            List->add(tempString);
            tempQString=SongList->get(i)->getDirectory();
            DirList->add(tempQString);
        }
        currentLen=SongList->getLen();
         ui->canciones->clear();//LIMPIA LA VARA
        insertListToListView(*List,SongsID,DirList);
    }





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                //A partir de aca puro codigo de interfaz//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Widget::on_directorios_itemClicked
 * @param item
 */

void Widget::on_directorios_itemClicked( QListWidgetItem *item){

        //instantiation//
        std::string tempString;
        QString tempQString;

        Clikable_Item *clickableItem = dynamic_cast<Clikable_Item*>(item)  ;
        LocalfileGetter *myFileGetter=          new LocalfileGetter;


        //setting sources//
        getter.setSouce(clickableItem->returnInfo().toStdString());
        myFileGetter->setSource(clickableItem->returnInfo());
        ui->canciones->clear();


        //gallery Configuration//
        if(gallery!=NULL)free(gallery);
        gallery=new CassetteGallery(maxVisibleItems);
        gallery->configure(maxVisibleItems,route2.toStdString(),this->iterator,clickableItem->returnInfo().toStdString());//Me vole el codigo que tenia acá e hice este metodo lindo


        updateSongview();





    }


/**
 * Set pagination mode active or inactive
 * @brief Widget::setPaginationMode
 * @param state
 */

void Widget::setPaginationMode(bool state){

    if(!state) {SongsInMemory = 100; }
    else {SongsInMemory=maxVisibleItems; }
    this->updateSongview();
}

/**
 * catch changes on the checkbox and call setpaginationmode
 * @brief Widget::on_checkBox_stateChanged
 * @param arg1
 */
void Widget::on_checkBox_stateChanged(int arg1){
     paginationMode=arg1;
     setPaginationMode(paginationMode);
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
}

/**
 * Dettecs any on purpose movement of the volumebar and update the current volume
 * @brief Widget::on_vol_valueChanged
 * @param value
 */

void Widget::on_vol_valueChanged(int value){
    player->setVolumen(value);

}



void Widget::on_canciones_itemClicked(QListWidgetItem *item)
{
        Clikable_Item *algo= dynamic_cast<Clikable_Item*>(item);
        //s::cout<<"Estoy imprimiendo la clave de la vida eterna"<<std::endl;
        //s::cout<<algo->getRname().toStdString()<<s::endl;
        ui->PlayB->setText(PlayText);
        Song temp;
        temp.setDirectory(algo->getRname());
        player->addToPlayList(temp);
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


/**
 * @brief Widget::reportScrollPosition
 */
void Widget::reportScrollPosition(){
    int currentPos=ui->canciones->verticalScrollBar()->value();

    if (lastScrollPos>currentPos){
        gallery->moveForwards();
    }
    else if(lastScrollPos<currentPos){
       gallery->moverBackwards();
    }

    lastScrollPos=currentPos;
    //s::cout<<ui->canciones->verticalScrollBar()->value() <<s::endl;

}



void Widget::on_pushButton_clicked()
{
          gallery->moveForwards();
          updateSongview();

}

void Widget::on_pushButton_2_clicked()
{
    gallery->moverBackwards();
    updateSongview();

}

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
#include <QMouseEvent>
#include<QMessageBox>

QString PlayText="Play";
QString PauseText="Pause";
std::string AllString="All";
QString route="/home/adrian/Escritorio/MusicaP/Out";
//QString route2="/home/adrian/Escritorio/MusicaP/sortedCSV.csv";
QString route2="/home/adrian/Escritorio/MusicaP/raw_tracks.csv";
QString DirectoriesID="carpetas";
QString SongsID="canciones";
//QString route="/home/lazh/QTproyects/Resources/fma/Out";
//QString route2="/home/lazh/QTproyects/Resources/fma/fma_metadata/raw_tracks.csv";

LocalfileGetter getter;
int songPosition=0;
int starting_Vol=50;
int updateFramingConstant=150;
int SongsInMemory=10;
float sizeItemRelationConstant=480/10;  //for each 480 pixels  10 items fits


namespace s = std;

/**
 * @brief Widget::Widget
 * @param parent
 */
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
    allSongGallery->setCsvDir(route2.toStdString());
    allSongGallery->setIterator(*myIterator);
    allSongGallery->setRequestedLen(11);
    allSongGallery->setSource(route.toStdString());
    allSongGallery->setAlbumPosition(2);
    allSongGallery->setArtistPosition(5);
    allSongGallery->setGenrePosition(39);
    allSongGallery->setNamePosition(songPosition);


    //conexiones
    connect(ui->canciones->verticalScrollBar(), &QScrollBar::valueChanged, [&]{reportScrollPosition();}  );
    connect(timer, &QTimer::timeout,[&]{if(playing)updateScenario();});

    //iniciado de directorios
    DoubleList<std::string> *myList = myFileGetter->getDirectoryList();
   // this->csv->setFileDirectory(route2.toStdString());
    insertListToListView(*myList,DirectoriesID);
    maxVisibleItems=this->ui->canciones->size().height()/sizeItemRelationConstant;
    allMode=false;
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
    //long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    int virtualMemUsed;
    if(allMode){
        if(allSongGallery!=NULL)virtualMemUsed=allSongGallery->getUsedMemory();
    }
    else{
        if(gallery==NULL)virtualMemUsed=gallery->getUsedMemory();
    }
    //s::cout<<virtualMemUsed<< s::endl;

    ui->Memory->setText(QString::number(virtualMemUsed) +" b");

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

    if(paginationMode){
         ui->canciones->verticalScrollBar()->resize(0,ui->canciones->verticalScrollBar()->height() );;
        }

    else{
        ui->canciones->verticalScrollBar()->resize(300,ui->canciones->verticalScrollBar()->height() );
        }


    this->csv->startReading();
    for (int i=0; i< listilla.getLen();i++ ){
        QString temp;
        QString dir_info= QString::fromStdString(listilla.get(i)->data());
        QString dir_nombre= calculateRealName(dir_info);
        if(listView==SongsID){
            temp=*DirList->get(i);
            dir_info=temp;



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
          s::cout<<"estas viendo: "<< maxVisibleItems<<" items"<<"tamaño es :"<< this->size().height()<<s::endl;

      maxVisibleItems=this->ui->canciones->size().height()/sizeItemRelationConstant;
      //maxVisibleItems=3; //quitar esto despues
      s::cout<<"estas viendo: "<< maxVisibleItems<<" items"<<"tamaño es :"<< this->size().height()<<s::endl;
      QWidget::resizeEvent(event);

}
/**
 * Dettects mouse wheel movement and update pagination pages
 * @brief Widget::wheelEvent
 * @param event
 */
void Widget::wheelEvent(QWheelEvent *event){

    if (paginationMode && ui->canciones->count()!=0){

        if(event->angleDelta().y()<0){
            if(!allMode)gallery->moveForwards();
            else allSongGallery->moveForward();
        }
        else{
            if(!allMode)gallery->moverBackwards();
            else allSongGallery->moveBackward();
        }
        updateSongview();
    }


}


/**
 * @brief Widget::updateSongview
 */
void Widget::updateSongview(){

        DoubleList<Song>* SongList;
        if(!allMode){
            SongList=gallery->getActualList();

        }
        else{
            SongList=allSongGallery->getActualPage();

        }


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
        allMode=false;
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
        if(!paginationMode)SongsInMemory=100;

        gallery=new CassetteGallery(SongsInMemory);
        gallery->configure(SongsInMemory,route2.toStdString(),this->iterator,clickableItem->returnInfo().toStdString());//Me vole el codigo que tenia acá e hice este metodo lindo

        updateSongview();
        updateScenario();


    }


/**
 * Set pagination mode active or inactive
 * @brief Widget::setPaginationMode
 * @param state
 */

void Widget::setPaginationMode(bool state){

    paginationMode=state;
    if(!state) {SongsInMemory = 100; }
    else {SongsInMemory=maxVisibleItems; }

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
    ui->PlayB->setText(PlayText);
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
    lastScrollPos=currentPos;
}
void Widget::on_visualizeAll_clicked()
{

   if(!paginationMode){
       allSongGallery->setPagingCondition(false);

       QMessageBox::StandardButton reply = QMessageBox::question(this, "CAUTION", "Are you sure about that?, no-pagination mode can crash your pc and forces you to restart it?",QMessageBox::Yes |  QMessageBox::Cancel);

       if (reply == QMessageBox::Yes){

            if(ui->demos->isChecked()){
                allSongGallery->setPagingCondition(true);
                allSongGallery->setRequestedLen(2000);
            }



           allSongGallery->startReading();
           allMode=true;
           updateSongview();
           updateScenario();
       }



   }



   else{
            allSongGallery->setPagingCondition(true);
            allSongGallery->setRequestedLen(maxVisibleItems);
            allSongGallery->startReading();
            allMode=true;
            updateSongview();
            updateScenario();
       }






}

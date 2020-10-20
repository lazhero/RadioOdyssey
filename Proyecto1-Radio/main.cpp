#include "widget.h"
#include"song.h"
#include"musicplayer.h"
#include "QDir"
#include <QApplication>
#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include<localfilegetter.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::fstream inputStream;
    inputStream.open("/home/lazh/QTproyects/Resources/fma/fma_metadata/raw_albums.csv",std::ios_base::in);
    std::vector<std::string> vector;
    std::string line,word;
    for(int i=0;i<100;i++){
        getline(inputStream,line);
        std::stringstream s(line);
       while (getline(s, word, ',')) {

         //  std::cout<<word<<std::endl;
       }

       // std::cout<<"________________________________________________________________________"<<std::endl;
    }

    LocalfileGetter* file=new LocalfileGetter;
    file->setSouce("/home/lazh/QTproyects/Resources/fma/fma_small");
    std::string data="025606.mp3";
    Song song=file->getSong(data);
    std::cout<<"El texto es :"<<song.getDirectory().toStdString()<<std::endl;
    Widget w;
    w.show();
    return a.exec();
}

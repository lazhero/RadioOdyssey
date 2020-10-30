#include "widget.h"
#include <QApplication>
#include"csvhandler.h"
#include<iostream>
#include<localfilegetter.h>
#include<csvsorting.h>
#include<myproyectstringiterator.h>
#include<DoubleList/InsertionSort.hpp>






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*


    DoubleList<std::string>* line=csv->getnextLine();
    for(int i=0;i<line->getLen();i++){
        std::cout<<*line->get(i)<<std::endl;
    }



    DoubleList<std::string>* List;
    DoubleList<DoubleList<std::string>>* matrix=csv->getAllLinesWithIn("AWOL - A Way Of Life",11);
      std::cout<<"EStpy aqui perras"<<std::endl;
    for(int i=0;i<matrix->getLen();i++){
        List=matrix->get(i);
        for(int j=0;j<List->getLen();j++){
            std::cout<<*List->get(j)<<std::endl;
        }
        std::cout<<"_______________________________________________________________________________________________"<<std::endl;
    }
 */


/*
    CSVSorting *csv=new CSVSorting;
    csv->setCsvDirectory("/home/lazh/QTproyects/Resources/fma/fma_metadata/raw_tracks.csv");
    csv->setOutputDirectory("/home/lazh/QTproyects/Resources/fma/Out");
    csv->setSource("/home/lazh/QTproyects/Resources/fma/fma_small");
    csv->setReferencePosition(2);
    csv->setFilePosition(0);
    MyProyectStringIterator iterator;
    iterator.setAfter(".mp3");
    iterator.setBefore("0");
    iterator.setBeforeDigits(6);
    csv->setIterator(iterator);
    csv->sortToDirectory();
    */
    /*
    CSVHandler* csv=new CSVHandler;
    csv->setFileDirectory("/home/lazh/QTproyects/Resources/fma/fma_metadata/tracks.csv");
    csv->startReading();
    csv->getNextLineWithIn("190",0);
    */
    Widget w;
    w.show();
    return a.exec();

}

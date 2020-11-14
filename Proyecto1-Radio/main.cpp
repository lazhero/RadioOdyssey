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
    CSVSorting *csv=new CSVSorting;
    csv->setCsvDirectory("/home/lazh/QTproyects/Resources/fma/fma_metadata/sortedCSV.csv");
    csv->setOutputDirectory("/home/lazh/QTproyects/Resources/fma/Out");
    csv->setSource("/home/lazh/QTproyects/Resources/fma/fma_small");
    csv->setReferencePosition(5);
    csv->setFilePosition(0);
    MyProyectStringIterator iterator;
    iterator.setAfter(".mp3");
    iterator.setBefore("0");
    iterator.setBeforeDigits(6);
    csv->setIterator(iterator);
    csv->sortToDirectory();
    std::cout<<"satanas"<<std::endl;
    Widget w;
    w.show();
    return a.exec();

}

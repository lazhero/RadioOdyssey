#include "csvhandler.h"

std::string emptyString="";
int lower=0;
int negative=-1;
int unity=1;
CSVHandler::CSVHandler()

{
    Route=new std::string;
    inputStream=NULL;
}

void CSVHandler::setFileDirectory(std::string name)
{

    *this->Route=name;
}

std::string CSVHandler::getFileDirectory()
{
    return *Route;
}

DoubleList<std::string> *CSVHandler::getnextLine()
{
    return getlines(unity)->get(minIndex);
}


void CSVHandler::startReading()
{
    if(inputStream==NULL){
       inputStream=new std::fstream;
       inputStream->open(*Route,std::ios_base::in);

    }
    else {
        inputStream->clear();
        inputStream->seekg(0,std::ios_base::beg);
    }





}

DoubleList<DoubleList<std::string> > *CSVHandler::getlines(int n)
{
    DoubleList<DoubleList<std::string>>* returnMatrix=new DoubleList<DoubleList<std::string>>;
    for(int i=0;i<n;i++){
        returnMatrix->add(*getNextLineWithIn(emptyString,lower));
    }
    return returnMatrix;
}

DoubleList<std::string> *CSVHandler::getNextLineWith(std::string text)
{

    return getNextLineWithIn(text,negative);
}


DoubleList<std::string> *CSVHandler::getNextLineWithIn(std::string text, int position)
{
    std::string line;
    std::string item;
    std::stringstream* linestream;
    DoubleList<std::string>* returnList;
    bool found;
    bool failCondition;
    while(getline(*inputStream,line)){
        if(line.compare(emptyString)==0) continue;
        returnList=new DoubleList<std::string>;
        linestream=new std::stringstream(line);
        found=false;
        failCondition=false;
        for(int i=0;getline(*linestream,item,delimiter) && !failCondition;i++){
            if(i==position && item.compare(text)!=0 && text.compare(emptyString)!=0)failCondition=true;
            if(text.compare(item)==0)found=true;
            returnList->add(item);
        }
        if(!failCondition && ((position>=0 && returnList->getLen()>position) || text.compare(emptyString)==0))return returnList;
        if(position<0 && found)return returnList;


    }
    return new DoubleList<std::string>;
}

DoubleList<DoubleList<std::string> > *CSVHandler::getAllLinesWith(std::string text)
{

    return getAllLinesWithIn(text,negative);
}

DoubleList<DoubleList<std::string>> *CSVHandler::getAllLinesWithIn(std::string text, int position)
{
    DoubleList<DoubleList<std::string>>* matriz=new DoubleList<DoubleList<std::string>>;
    DoubleList<std::string> *vector;
    for(vector=getNextLineWithIn(text,position);inputStream->peek()!=EOF;vector=vector=getNextLineWithIn(text,position)){
        if(vector->getLen()>0)matriz->add(*vector);
    }
    if(vector!=NULL && vector->getLen()>0)matriz->add(*vector);
    return matriz;


}


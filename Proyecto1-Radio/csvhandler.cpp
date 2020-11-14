#include "csvhandler.h"
int lower=0;
int negative=-1;
int unity=1;
/**
 * @brief CSVHandler::CSVHandler
 */
CSVHandler::CSVHandler()

{
    Route=new std::string;
    inputStream=NULL;
    FordWard=true;
}
/**
 * @brief CSVHandler::setFileDirectory
 * @param name
 */
void CSVHandler::setFileDirectory(std::string name)
{

    *this->Route=name;
}
/**
 * @brief CSVHandler::getFileDirectory
 * @return
 */
std::string CSVHandler::getFileDirectory()
{
    return *Route;
}
/**
 * @brief CSVHandler::getnextLine
 * @return
 */
DoubleList<std::string> *CSVHandler::getnextLine()
{
    return getlines(unity)->get(minIndex);
}
/**
 * @brief CSVHandler::startReading
 */

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
   // inputStream->see




}
/**
 * @brief CSVHandler::getlines
 * @param n
 * @return
 */
DoubleList<DoubleList<std::string> > *CSVHandler::getlines(int n)
{
    DoubleList<DoubleList<std::string>>* returnMatrix=new DoubleList<DoubleList<std::string>>;
    for(int i=0;i<n;i++){
        returnMatrix->add(*getNextLineWithIn(emptyString,lower));
    }
    return returnMatrix;
}
/**
 * @brief CSVHandler::getNextLineWith
 * @param text
 * @return
 */
DoubleList<std::string> *CSVHandler::getNextLineWith(std::string text)
{

    return getNextLineWithIn(text,negative);
}

/**
 * @brief CSVHandler::getNextLineWithIn
 * @param text
 * @param position
 * @return
 */
DoubleList<std::string> *CSVHandler::getNextLineWithIn(std::string text, int position)
{
    std::string line;
    std::string item;
    std::stringstream* linestream;
    DoubleList<std::string>* returnList;
    bool found;
    bool failCondition;
    while(this->getTheLine(*inputStream,line)){
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
/**
 * @brief CSVHandler::getAllLinesWith
 * @param text
 * @return
 */
DoubleList<DoubleList<std::string> > *CSVHandler::getAllLinesWith(std::string text)
{

    return getAllLinesWithIn(text,negative);
}
/**
 * @brief CSVHandler::getAllLinesWithIn
 * @param text
 * @param position
 * @return
 */
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
/**
 * @brief CSVHandler::getAllLines
 * @return
 */
DoubleList<DoubleList<std::string> > *CSVHandler::getAllLines()
{
    return getAllLinesWithIn(emptyString,negative);


}
/**
 * @brief CSVHandler::setForward
 * @param state
 */
void CSVHandler::setForward(bool state)
{
   FordWard=state;
}
/**
 * @brief CSVHandler::getTheLine
 * @param is
 * @param str
 * @return
 */
std::istream& CSVHandler::getTheLine(std::istream &is, std::string &str)
{
    if(!FordWard){
        int pos=inputStream->tellg();
        if(pos>0){
            inputStream->seekg(pos-1,std::ios_base::beg);
        }
    }
    return getline(is,str);


}


#include "cassettegallery.h"
#include "routetools.h"
const int pageNumber=3;
const std::string delimiter="/";
const std::string format=".mp3";
int artistPosition=5;
int albumPosition=2;
int orNamePosition=37;

#include<DoubleList/InsertionSort.hpp>
#include<localfilegetter.h>

/**
 * @brief CassetteGallery::CassetteGallery
 * @param requestedLen
 */
CassetteGallery::CassetteGallery(int requestedLen)
{
    page=new Pages(requestedLen);
    csvHandler=new CSVHandler;
    this->csvDir=new std::string;
    this->sourceDir=new std::string;
    csvData=new std::vector<DoubleList<std::string>*>;

}
/**
 * @brief CassetteGallery::~CassetteGallery
 */
CassetteGallery::~CassetteGallery()
{
    free(FilesList);
    free(page);
    free(csvDir);
    free(sourceDir);
    free(CSVList);

}

/**
 * @brief CassetteGallery::getSong
 * @param AtributteList
 * @return
 */
Song *CassetteGallery::getSong(DoubleList<std::string>* AtributteList){
    std::string FileDirectory;
    Song *temp=new Song;

    temp->setArtist(*new std::string(*AtributteList->get(ArtistPosition)));
    temp->setFileName(*new std::string(*AtributteList->get(NamePosition)));
    temp->setOrName(*new std::string(*AtributteList->get(OrNamePosition)));
    temp->setAlbum(*new std::string(*AtributteList->get(AlbumPosition)));

    FileDirectory=*sourceDir;
    FileDirectory.append(delimiter);
    std::string firstTemp=temp->getFileName().toStdString();
    std::string tempString=iterator->iterateString(firstTemp);
    FileDirectory.append(tempString);
    temp->setDirectory(* new std::string(FileDirectory));
    return temp;

}
/**
 * @brief CassetteGallery::setSourceDir
 * @param dir
 */
void CassetteGallery::setSourceDir(std::string dir){

    if(!FileManager::canOpen(dir))return;
    clear();
    page->setListLen(requestedLen);
    std::string FileDirectory;
    *this->sourceDir=dir;
    LocalfileGetter *getter=new LocalfileGetter;
    getter->setSouce(dir);
    FilesList=getter->getRecursiveFileList();
    DoubleList<int>* tempList=new DoubleList<int>;
    int tempInt;
    std::string myTempString;
    RouteTools tools;
    SubDirectoryList=new DoubleList<std::string>;
    for(int i=0;i<FilesList->getLen();i++){
        tools.setRoute(*FilesList->get(i));
        tempInt=std::stoi(tools.getFileName());
        myTempString=tools.getSeccionRoute(minIndex,tools.getSplittedStringLen()-1);
        SubDirectoryList->add(myTempString);
        tempList->add(tempInt);
    }
    sort(tempList);
    DoubleList<std::string>* TempStringList=new DoubleList<std::string>;
    std::string tempString;
    for(int i=0;i<tempList->getLen();i++){
        tempInt=*tempList->get(i);
        tempString=std::to_string(tempInt);
        TempStringList->add(tempString);
    }
    FilesList=TempStringList;
    csvHandler->startReading();
    initCSV((pageNumber-1)*requestedLen);
    add((pageNumber-1)*requestedLen);
    page->emptyBack();
}
/**
 * @brief CassetteGallery::moveForwards
 * @return
 */
bool CassetteGallery::moveForwards()
{
    if(FilesList->getLen()>0)initCSV(1);
    if(endPos<(signed int)csvData->size()){
        *sourceDir=*SubDirectoryList->get(endPos);
        page->AddToFront(*getSong(csvData->at(endPos)));
        endPos++;
    }
    else{
        page->iterateBack();
        page->DeleteLeftOver();
    }
    startPos=endPos-page->getTotal();
    return true;
}
/**
 * @brief CassetteGallery::moverBackwards
 * @return
 */
bool CassetteGallery::moverBackwards(){

    if(startPos>minIndex){
        *sourceDir=*SubDirectoryList->get(startPos-1);
        page->AddToBack(*getSong(csvData->at(startPos-1)));
        startPos--;
    }
    else{
        page->iterateFront();
        page->DeleteLeftOver();
    }
    endPos=startPos+page->getTotal();
    return true;
}
/**
 * @brief CassetteGallery::getUsedMemory
 * @return
 */
int CassetteGallery::getUsedMemory(){
    if(page==NULL)return 0;
    return sizeof(*page)*page->getTotal();

}


/**
 * @brief CassetteGallery::add
 * @param n
 */
void CassetteGallery::add(int n)

{
    Song* temp;
    std::string tempString;
    int  i;
    page->setListLen(requestedLen);
    for( i=endPos;i<csvData->size() && i<endPos+n;i++){
        *sourceDir=*SubDirectoryList->get(i);
        temp=getSong(csvData->at(i));
        page->AddToFront(*temp);
    }
    if(i!=endPos){
    startPos=endPos;
    endPos=i;
    }
    requestedLen=page->getActual()->getLen();
}
/**
 * @brief CassetteGallery::clear
 */
void CassetteGallery::clear()
{
    free(page);
    if(csvData!=nullptr)free(csvData);
    csvData=new std::vector<DoubleList<std::string>*>;
    page=new Pages(minIndex);
    startPos=minIndex;
    endPos=minIndex;

}
/**
 * Initiales the CSV handler
 * @brief CassetteGallery::initCSV
 * @param number
 */
void CassetteGallery::initCSV(int number)
{
    DoubleList<std::string>* temp;
    while(FilesList->getLen()>0 && number!=0){
       temp=csvHandler->getNextLineWithIn(*FilesList->get(minIndex),NamePosition);
       csvData->push_back(temp);
       FilesList->erase(minIndex);
       number--;
    }
}
/**
 * @brief CassetteGallery::configure
 * @param Size
 * @param route
 * @param iterator
 * @param dir
 */
void CassetteGallery::configure(int Size, std::string route, stringIterator* iterator,std::string dir){
   this->setAlbumPosition(albumPosition);
   this->setArtistPosition(artistPosition);
   this->setOrnamePosition(orNamePosition);
   this->setRequestLen(Size);
   this->setCsvDir(route);
   this->setIterator(iterator);
   this->setSourceDir(dir);
}




///////////////////////////////////////////////////////////////////
                //setters an getters//
///////////////////////////////////////////////////////////////////


/**
 * @brief CassetteGallery::setRequestLen
 * @param len
 */
void CassetteGallery::setRequestLen(int len)
{
    page->setListLen(len);
    this->requestedLen=page->getListLen();

}
/**
 * @brief CassetteGallery::getRequestLen
 * @return
 */
int CassetteGallery::getRequestLen()
{
    return this->requestedLen;

}
/**
 * @brief CassetteGallery::setCsvDir
 * @param dir
 */
void CassetteGallery::setCsvDir(std::string dir)
{
    if(!FileManager::canOpen(dir))return;
    *this->csvDir=dir;
    csvHandler->setFileDirectory(dir);
    csvHandler->startReading();
}
/**
 * @brief CassetteGallery::getCsvDir
 * @return
 */
std::string CassetteGallery::getCsvDir()
{
    return *this->csvDir;
}

/**
 * @brief CassetteGallery::getSourceDir
 * @return
 */
std::string CassetteGallery::getSourceDir()
{
    return *this->sourceDir;
}
/**
 * @brief CassetteGallery::getStartPos
 * @return
 */
int CassetteGallery::getStartPos()
{
    return startPos;
}
/**
 * @brief CassetteGallery::setStartPos
 * @param value
 */
void CassetteGallery::setStartPos(int value)
{
    startPos = value;
}
/**
 * @brief CassetteGallery::getEndPos
 * @return
 */
int CassetteGallery::getEndPos()
{
    return endPos;
}
/**
 * @brief CassetteGallery::setEndPos
 * @param value
 */
void CassetteGallery::setEndPos(int value)
{
    endPos = value;
}
/**
 * @brief CassetteGallery::getNamePosition
 * @return
 */
int CassetteGallery::getNamePosition()
{
    return NamePosition;
}
/**
 * @brief CassetteGallery::setNamePosition
 * @param value
 */
void CassetteGallery::setNamePosition(int value)
{
    NamePosition = value;
}
/**
 * @brief CassetteGallery::getArtistPosition
 * @return
 */
int CassetteGallery::getArtistPosition()
{
    return ArtistPosition;
}
/**
 * @brief CassetteGallery::setArtistPosition
 * @param value
 */
void CassetteGallery::setArtistPosition(int value)
{
    ArtistPosition = value;
}
/**
 * @brief CassetteGallery::getAlbumPosition
 * @return
 */
int CassetteGallery::getAlbumPosition()
{
    return AlbumPosition;
}
/**
 * @brief CassetteGallery::setAlbumPosition
 * @param value
 */
void CassetteGallery::setAlbumPosition(int value)
{
    AlbumPosition = value;
}
/**
 * @brief CassetteGallery::getGenrePosition
 * @return
 */
int CassetteGallery::getGenrePosition()
{
    return OrNamePosition;
}
/**
 * @brief CassetteGallery::setOrnamePosition
 * @param value
 */
void CassetteGallery::setOrnamePosition(int value)
{
    OrNamePosition = value;
}
/**
 * @brief CassetteGallery::setIterator
 * @param iterator
 */
void CassetteGallery::setIterator(stringIterator* iterator)
{
    this->iterator=iterator;
}
/**
 * @brief CassetteGallery::getIterator
 * @return
 */
stringIterator CassetteGallery::getIterator(){
    return *this->iterator;
}

/**
 * @brief CassetteGallery::getActualList
 * @return
 */
DoubleList<Song> *CassetteGallery::getActualList()
{
    return page->getActual();
}




#include "cassettegallery.h"
#include "routetools.h"
const int pageNumber=3;
const std::string delimiter="/";
const std::string format=".mp3";
int artistPosition=5;
int albumPosition=2;
int genrePosition=artistPosition;

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
 * @brief CassetteGallery::setRequestLen
 * @param len
 */
void CassetteGallery::setRequestLen(int len)
{
    page->setListLen(len);
    this->requestedLen=page->getListLen();

}

int CassetteGallery::getRequestLen()
{
    return this->requestedLen;

}

void CassetteGallery::setCsvDir(std::string dir)
{
    if(!FileManager::canOpen(dir))return;
    *this->csvDir=dir;
    csvHandler->setFileDirectory(dir);
    csvHandler->startReading();
}

std::string CassetteGallery::getCsvDir()
{
    return *this->csvDir;
}

void CassetteGallery::setSourceDir(std::string dir)
{
    if(!FileManager::canOpen(dir))return;
    clear();
    page->setListLen(requestedLen);
    std::string FileDirectory;
    *this->sourceDir=dir;
    LocalfileGetter *getter=new LocalfileGetter;
    getter->setSouce(dir);
    FilesList=getter->getFilesList();
    DoubleList<int>* tempList=new DoubleList<int>;
    int tempInt;
    RouteTools tools;
    SubDirectoryList=new DoubleList<std::string>;
    for(int i=0;i<FilesList->getLen();i++){
        tools.setRoute(*FilesList->get(i));
        tempInt=std::stoi(tools.getFileName());
       //SubDirectoryList->add(tools.getDirectory(t))
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

std::string CassetteGallery::getSourceDir()
{
    return *this->sourceDir;
}

int CassetteGallery::getStartPos()
{
    return startPos;
}

void CassetteGallery::setStartPos(int value)
{
    startPos = value;
}

int CassetteGallery::getEndPos()
{
    return endPos;
}

void CassetteGallery::setEndPos(int value)
{
    endPos = value;
}

int CassetteGallery::getNamePosition()
{
    return NamePosition;
}

void CassetteGallery::setNamePosition(int value)
{
    NamePosition = value;
}

int CassetteGallery::getArtistPosition()
{
    return ArtistPosition;
}

void CassetteGallery::setArtistPosition(int value)
{
    ArtistPosition = value;
}

int CassetteGallery::getAlbumPosition()
{
    return AlbumPosition;
}

void CassetteGallery::setAlbumPosition(int value)
{
    AlbumPosition = value;
}

int CassetteGallery::getGenrePosition()
{
    return GenrePosition;
}

void CassetteGallery::setGenrePosition(int value)
{
    GenrePosition = value;
}

void CassetteGallery::setIterator(stringIterator* iterator)
{
    this->iterator=iterator;
}
stringIterator CassetteGallery::getIterator(){
    return *this->iterator;
}

bool CassetteGallery::moveForwards()
{
    if(FilesList->getLen()>0)initCSV(1);
    std::cout<<"el len del file list es"<<FilesList->getLen()<<std::endl;
    if(endPos<(signed int)csvData->size()){
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
bool CassetteGallery::moverBackwards(){

    if(startPos>minIndex){
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

DoubleList<Song> *CassetteGallery::getActualList()
{
    return page->getActual();
}



Song *CassetteGallery::getSong(DoubleList<std::string>* AtributteList)
{
    std::string FileDirectory;
    Song *temp=new Song;
    temp->setArtist(*new std::string(*AtributteList->get(ArtistPosition)));
    temp->setFileName(*new std::string(*AtributteList->get(NamePosition)));
    temp->setGenre(*new std::string(*AtributteList->get(GenrePosition)));
    FileDirectory=*sourceDir;
    FileDirectory.append(delimiter);
    std::string firstTemp=temp->getFileName().toStdString();
    std::string tempString=iterator->iterateString(firstTemp);
    FileDirectory.append(tempString);
    temp->setDirectory(* new std::string(FileDirectory));
    return temp;

}

void CassetteGallery::add(int n)

{
    Song* temp;
    std::string tempString;
    int  i;
    page->setListLen(requestedLen);
    for( i=endPos;i<csvData->size() && i<endPos+n;i++){
        temp=getSong(csvData->at(i));
        page->AddToFront(*temp);
    }
    if(i!=endPos){
    startPos=endPos;
    endPos=i;
    }
    requestedLen=page->getActual()->getLen();
}

void CassetteGallery::clear()
{
    free(page);
    page=new Pages(minIndex);
    startPos=minIndex;
    endPos=minIndex;
}

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
void CassetteGallery::configure(int Size, std::string route, stringIterator* iterator,std::string dir){
   this->setAlbumPosition(albumPosition);
   this->setArtistPosition(artistPosition);
   this->setGenrePosition(genrePosition);
   this->setRequestLen(Size);
   this->setCsvDir(route);
   this->setIterator(iterator);
   this->setSourceDir(dir);
}





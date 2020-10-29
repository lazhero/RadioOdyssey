#include "cassettegallery.h"
const int pageNumber=3;
const char charDelimiter='/';
const std::string delimiter="/";
const std::string format=".mp3";
#include<DoubleList/InsertionSort.hpp>
#include<localfilegetter.h>

CassetteGallery::CassetteGallery(int requestedLen)
{
    page=new Pages(requestedLen);
    csvHandler=new CSVHandler;
    this->csvDir=new std::string;
    this->sourceDir=new std::string;

}

CassetteGallery::~CassetteGallery()
{
    free(FilesList);
    free(page);
    free(csvDir);
    free(sourceDir);
    free(CSVList);

}

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
    for(int i=0;i<FilesList->getLen();i++){
        tempInt=std::stoi(getFileName(*FilesList->get(i)));
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
    add((pageNumber-1)*requestedLen);
    page->swap(0,1);
}

std::string CassetteGallery::getSourceDir()
{
    return *this->sourceDir;
}

int CassetteGallery::getStartPos() const
{
    return startPos;
}

void CassetteGallery::setStartPos(int value)
{
    startPos = value;
}

int CassetteGallery::getEndPos() const
{
    return endPos;
}

void CassetteGallery::setEndPos(int value)
{
    endPos = value;
}

int CassetteGallery::getNamePosition() const
{
    return NamePosition;
}

void CassetteGallery::setNamePosition(int value)
{
    NamePosition = value;
}

int CassetteGallery::getArtistPosition() const
{
    return ArtistPosition;
}

void CassetteGallery::setArtistPosition(int value)
{
    ArtistPosition = value;
}

int CassetteGallery::getAlbumPosition() const
{
    return AlbumPosition;
}

void CassetteGallery::setAlbumPosition(int value)
{
    AlbumPosition = value;
}

int CassetteGallery::getGenrePosition() const
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
    if(endPos>=CSVList->getLen())return false;
    page->AddToFront(*getSong(CSVList->get(endPos)));
    endPos++;
    if(page->isFull())startPos++;
    return true;
}
bool CassetteGallery::moverBackwards(){
    if(startPos<=minIndex)return false;
    page->AddToBack(*getSong(CSVList->get(startPos-1)));
    startPos--;
    if(page->isFull())endPos--;
    return true;
}

DoubleList<Song> *CassetteGallery::getActualList()
{
    return page->getActual();
}

std::string CassetteGallery::getFileName(std::string data)
{
    std::string temp;
    DoubleList<std::string>* SlipList= StringTools::slipString(charDelimiter,data);
    temp=* SlipList->get(SlipList->getLen()-1);
    SlipList=StringTools::slipString('.',temp);
    temp=*SlipList->get(minIndex);
    QString dir_nombre=QString::fromStdString(temp);
    while(dir_nombre.left(1)=="0"){
        dir_nombre=dir_nombre.right(dir_nombre.length()-1);
    }
    return dir_nombre.toStdString();
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
    int i;
    page->setListLen(requestedLen);
    for( i=endPos;i<FilesList->getLen() && i<endPos+n;i++){
        temp=getSong(csvHandler->getNextLineWithIn(*FilesList->get(i),NamePosition));
        //if(page->isFull())page->setListLen(page->getListLen()+1);
        page->AddToFront(*temp);

    }
    if(i!=endPos){
    startPos=endPos;
    endPos=i;
    }
    requestedLen=endPos-startPos;
}

void CassetteGallery::clear()
{
    free(page);
    page=new Pages(minIndex);
    startPos=minIndex;
    endPos=minIndex;
}





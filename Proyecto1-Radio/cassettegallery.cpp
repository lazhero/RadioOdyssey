#include "cassettegallery.h"
const int pageNumber=3;
const char charDelimiter='/';
const std::string delimiter="/";
const std::string format=".mp3";
/**
 * @brief CassetteGallery::CassetteGallery
 * @param requestedLen
 */
CassetteGallery::CassetteGallery(int requestedLen)
{
    page=new Pages(requestedLen);
    csvHandler=new CSVHandler;

}
/**
 * @brief CassetteGallery::~CassetteGallery
 */
CassetteGallery::~CassetteGallery()
{
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
    std::string FileDirectory;
    *this->sourceDir=dir;
    DoubleList<std::string> slippedString;
    slippedString=*StringTools::slipString(charDelimiter,dir);
    csvHandler->startReading();
    CSVList= csvHandler->getAllLinesWithIn(*slippedString.get(slippedString.getLen()-1),AlbumPosition);
    Song* temp;
    int i;
    for(i=0;i<CSVList->getLen() && i<pageNumber*requestedLen;i++){
        temp=getSong(CSVList->get(i));
        page->AddToFront(*temp);

    }
    startPos=minIndex;   //Inclusive
    endPos=i;//Exclusive
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

void CassetteGallery::setIterator(stringIterator iterator)
{
    *this->iterator=iterator;
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

Song *CassetteGallery::getSong(DoubleList<std::string>* AtributteList)
{
    std::string FileDirectory;
    Song *temp=new Song;
    temp->setArtist(*AtributteList->get(ArtistPosition));
    temp->setFileName(*AtributteList->get(NamePosition));
    temp->setGenre(*AtributteList->get(GenrePosition));
    FileDirectory=*sourceDir;
    FileDirectory.append(delimiter);
    FileDirectory.append(iterator->iterateString(temp->getFileName().toStdString()));
    temp->setDirectory(FileDirectory);
    return temp;

}





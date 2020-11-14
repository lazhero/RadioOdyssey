#include "allsongsgallery.h"
std::string filesDelimiter="/";
/**
 * @brief AllSongsGallery::AllSongsGallery
 */
AllSongsGallery::AllSongsGallery()
{
    csvData=new std::vector<DoubleList<std::string>*>;
    Directories=new std::vector<std::string>;
    pages=new Pages(minIndex);
    handler= new CSVHandler;
    PagingCondition=true;



}
/**
 * @brief AllSongsGallery::getNamePosition
 * @return
 */
int AllSongsGallery::getNamePosition() const
{
    return NamePosition;
}
/**
 * @brief AllSongsGallery::getArtistPosition
 * @return
 */
int AllSongsGallery::getArtistPosition() const
{
    return ArtistPosition;
}
/**
 * @brief AllSongsGallery::getGenrePosition
 * @return
 */
int AllSongsGallery::getGenrePosition() const
{
    return GenrePosition;
}
/**
 * @brief AllSongsGallery::getAlbumPosition
 * @return
 */
int AllSongsGallery::getAlbumPosition() const
{
    return AlbumPosition;
}
/**
 * @brief AllSongsGallery::setAlbumPosition
 * @param value
 */
void AllSongsGallery::setAlbumPosition(int value)
{
    AlbumPosition = value;
}
/**
 * @brief AllSongsGallery::setSource
 * @param source
 */
void AllSongsGallery::setSource(std::string source)
{
    sourceDir=source;
}
/**
 * @brief AllSongsGallery::setIterator
 * @param iterator
 */
void AllSongsGallery::setIterator(MyProyectStringIterator iterator)
{
    this->iterator=iterator;
}
/**
 * @brief AllSongsGallery::getRequestedLen
 * @return
 */
int AllSongsGallery::getRequestedLen() const
{
    return requestedLen;
}
/**
 * @brief AllSongsGallery::setRequestedLen
 * @param value
 */
void AllSongsGallery::setRequestedLen(int value)
{
    requestedLen = value;
    pages->setListLen(value);
}
/**
 * @brief AllSongsGallery::setArtistPosition
 * @param value
 */
void AllSongsGallery::setArtistPosition(int value)
{
    ArtistPosition = value;
}
/**
 * @brief AllSongsGallery::setGenrePosition
 * @param value
 */
void AllSongsGallery::setGenrePosition(int value)
{
    GenrePosition = value;
}
/**
 * @brief AllSongsGallery::setNamePosition
 * @param value
 */
void AllSongsGallery::setNamePosition(int value)
{
    NamePosition = value;
}
/**
 * @brief AllSongsGallery::startReading
 */

void AllSongsGallery::startReading()
{
    clear();
    //handler->setFileDirectory(csvDir);
    handler->startReading();
    pages->setListLen(requestedLen);
    if(PagingCondition){
        add(2*requestedLen);
        AddNSong(2*requestedLen);
    }
    else{
        add(-1);
        requestedLen=csvData->size();
        pages->setListLen(requestedLen);
        AddNSong(requestedLen);
    }


    pages->emptyBack();
}
/**
 * @brief AllSongsGallery::add
 * @param n
 */
void AllSongsGallery::add(int n)
{
    DoubleList<std::string> *Line;
    std::string route;
    while (n!=0 && (Line=handler->getnextLine())->getLen()>0) {
        try{
            route=buildString(*Line->get(ArtistPosition),*Line->get(NamePosition));
            if(route.length()<300 && FileManager::canOpen(route)){
                n--;
                Directories->push_back(route);
                csvData->push_back(Line);
            }
        }
        catch (OutIndexException) {

        }
    }
}
/**
 * @brief AllSongsGallery::buildString
 * @param subDirectory
 * @param filename
 * @return
 */
std::string AllSongsGallery::buildString(std::string subDirectory, std::string filename)
{
    std::string copy=sourceDir;
    std::string myFileName=iterator.iterateString(filename);
    copy.append(filesDelimiter);
    copy.append(subDirectory);
    copy.append(filesDelimiter);
    copy.append(myFileName);
    return copy;
}
/**
 * @brief AllSongsGallery::getSong
 * @param position
 * @return
 */
Song AllSongsGallery::getSong(int position)
{
    DoubleList<std::string> attributeList=*csvData->at(position);
    Song song;
    try{
        song.setDirectory(Directories->at(position));
        song.setFileName(*attributeList.get(NamePosition));
        song.setAlbum(*attributeList.get(AlbumPosition));
        song.setArtist(*attributeList.get(ArtistPosition));
        song.setOrName(*attributeList.get(GenrePosition));
    }
    catch (OutIndexException) {

    }
    return song;
}


/**
 * @brief AllSongsGallery::moveForward
 */
void AllSongsGallery::moveForward()
{
    add(1);
    if(end<csvData->size()){
        pages->AddToFront(getSong(end));
        end++;
    }
    else{
        pages->iterateBack();
        pages->DeleteLeftOver();
    }
    start=end-pages->getTotal();
}
/**
 * @brief AllSongsGallery::moveBackward
 */
void AllSongsGallery::moveBackward()
{
    if(start>minIndex){
        pages->AddToBack(getSong(start-1));
        start--;
    }
    else{
        pages->iterateFront();
        pages->DeleteLeftOver();
    }
}
/**
 * @brief AllSongsGallery::getActualPage
 * @return
 */
DoubleList<Song> *AllSongsGallery::getActualPage()
{
    return pages->getActual();
}
/**
 * @brief AllSongsGallery::getCsvDir
 * @return
 */
std::string AllSongsGallery::getCsvDir() const
{
    return csvDir;
}
/**
 * @brief AllSongsGallery::setCsvDir
 * @param value
 */
void AllSongsGallery::setCsvDir(const std::string &value)
{
    handler->setFileDirectory(value);
    csvDir = value;
}
/**
 * @brief AllSongsGallery::getPagingCondition
 * @return
 */
bool AllSongsGallery::getPagingCondition() const
{
    return PagingCondition;
}
/**
 * @brief AllSongsGallery::setPagingCondition
 * @param value
 */
void AllSongsGallery::setPagingCondition(bool value)
{
    PagingCondition = value;
}
/**
 * @brief AllSongsGallery::getUsedMemory
 * @return
 */

int AllSongsGallery::getUsedMemory()
{
    if(pages==NULL)return 0;
    return sizeof (Song)*pages->getTotal();
}
/**
 * @brief AllSongsGallery::AddNSong
 * @param n
 */
void AllSongsGallery::AddNSong(int n)
{
    Song temp;
    for(int i=start;i<n;i++){
        temp=getSong(i);
        pages->AddToFront(temp);
    }
    end=start+pages->getTotal();
}
/**
 * @brief AllSongsGallery::clear
 */
void AllSongsGallery::clear()
{
   start=minIndex;
   end=minIndex;
   free(csvData);
   free(Directories);
   free(pages);
   csvData=new std::vector<DoubleList<std::string>*>;
   Directories=new std::vector<std::string>;
   pages=new Pages(minIndex);

}

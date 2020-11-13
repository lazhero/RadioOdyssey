#include "allsongsgallery.h"
std::string filesDelimiter="/";
AllSongsGallery::AllSongsGallery()
{
    csvData=new std::vector<DoubleList<std::string>*>;
    Directories=new std::vector<std::string>;
    pages=new Pages(minIndex);

}

int AllSongsGallery::getNamePosition() const
{
    return NamePosition;
}

int AllSongsGallery::getArtistPosition() const
{
    return ArtistPosition;
}

int AllSongsGallery::getGenrePosition() const
{
    return GenrePosition;
}

int AllSongsGallery::getAlbumPosition() const
{
    return AlbumPosition;
}

void AllSongsGallery::setAlbumPosition(int value)
{
    AlbumPosition = value;
}

void AllSongsGallery::setIterator(MyProyectStringIterator iterator)
{
    this->iterator=iterator;
}

int AllSongsGallery::getRequestedLen() const
{
    return requestedLen;
}

void AllSongsGallery::setRequestedLen(int value)
{
    requestedLen = value;
    pages->setListLen(value);
}


void AllSongsGallery::startReading()
{
    handler->startReading();
    if(PagingCondition){
        add(requestedLen);
    }
    else{
        add(-1);
        requestedLen=csvData->size();
    }
    AddNSong(requestedLen);
    pages->emptyBack();
}

void AllSongsGallery::add(int n)
{
    DoubleList<std::string> *Line;
    std::string route;
    while (n!=0 && (Line=handler->getnextLine())->getLen()>0) {
        route=buildString(*Line->get(ArtistPosition),*Line->get(NamePosition));
        if(FileManager::canOpen(route)){
            n--;
            Directories->push_back(route);
            csvData->push_back(Line);
        }
    }
}

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

Song AllSongsGallery::getSong(int position)
{
    DoubleList<std::string> attributeList;
    Song song;
    song.setArtist(*attributeList.get(ArtistPosition));
    song.setGenre(*attributeList.get(GenrePosition));
    song.setDirectory(Directories->at(position));
    song.setFileName(*attributeList.get(NamePosition));
    return song;
}



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

void AllSongsGallery::AddNSong(int n)
{
    while(n>0){
        moveForward();
        n--;
    }
}

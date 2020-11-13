#include "allsongsgallery.h"
std::string filesDelimiter="/";
AllSongsGallery::AllSongsGallery()
{
    csvData=new std::vector<DoubleList<std::string>*>;
    Directories=new std::vector<std::string>;
    pages=new Pages(minIndex);
    handler= new CSVHandler;
    PagingCondition=true;



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

void AllSongsGallery::setSource(std::string source)
{
    sourceDir=source;
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

void AllSongsGallery::setArtistPosition(int value)
{
    ArtistPosition = value;
}

void AllSongsGallery::setGenrePosition(int value)
{
    GenrePosition = value;
}

void AllSongsGallery::setNamePosition(int value)
{
    NamePosition = value;
}


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
        AddNSong(requestedLen);
    }


    pages->emptyBack();
}

void AllSongsGallery::add(int n)
{
    DoubleList<std::string> *Line;
    std::string route;
    while (n!=0 && (Line=handler->getnextLine())->getLen()>0) {
        try{
            route=buildString(*Line->get(ArtistPosition),*Line->get(NamePosition));
            if(FileManager::canOpen(route)){
                n--;
                Directories->push_back(route);
                csvData->push_back(Line);
            }
        }
        catch (OutIndexException) {

        }
    }
    std::cout<<"Me cago en Milton/ Noguera/ Isaac "<<std::endl;
}

std::string AllSongsGallery::buildString(std::string subDirectory, std::string filename)
{
    std::string copy=sourceDir;
    std::string myFileName=iterator.iterateString(filename);
    copy.append(filesDelimiter);
    copy.append(subDirectory);
    copy.append(filesDelimiter);
    copy.append(myFileName);
    std::cout<<"HOLAAAAAAAAAAAAAAAAAA:   "<<  copy ;
    std::cout<<std::endl;
    return copy;
}

Song AllSongsGallery::getSong(int position)
{
    DoubleList<std::string> attributeList=*csvData->at(position);
    Song song;
    try{
        song.setDirectory(Directories->at(position));
        song.setFileName(*attributeList.get(NamePosition));
        song.setArtist(*attributeList.get(ArtistPosition));
        song.setGenre(*attributeList.get(GenrePosition));
    }
    catch (OutIndexException) {

    }
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

DoubleList<Song> *AllSongsGallery::getActualPage()
{
    return pages->getActual();
}

std::string AllSongsGallery::getCsvDir() const
{
    return csvDir;
}

void AllSongsGallery::setCsvDir(const std::string &value)
{
    handler->setFileDirectory(value);
    csvDir = value;
}

bool AllSongsGallery::getPagingCondition() const
{
    return PagingCondition;
}

void AllSongsGallery::setPagingCondition(bool value)
{
    PagingCondition = value;
}

void AllSongsGallery::AddNSong(int n)
{
    Song temp;
    for(int i=start;i<n;i++){
        temp=getSong(i);
        pages->AddToFront(temp);
    }
    end=start+pages->getTotal();
}

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

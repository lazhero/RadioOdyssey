#include "song.h"

Song::Song()
{
    Artist=new QString;
    directory=new QString;
    FileName=new QString;
    album=new QString;
    originalName=new QString;
    isLocal=true;

}
QString Song::getArtist(){
    return *Artist;
}


void Song::setLocalState(bool state)
{
    isLocal=state;
}

bool Song::getLocalState()
{
    return isLocal;
}

QString Song::getFileName()
{
    return *this->FileName;
}
void Song::setFileName(QString Name){
    *this->FileName=Name;
}

void Song::setOriginalName(std::string Name)
{
    *originalName=QString::fromStdString(Name);
}


void Song::setFileName(std::string Name){
    this->setFileName(QString::fromStdString(Name));
}


/**
 * @brief Song::toString
 * @return
 */
std::string Song::toString()
{
    QString returning;
    returning.append(*FileName);
    returning.append(" or:  ");

    returning.append(*originalName);
    returning.append(" al: ");

    returning.append(*album);
    returning.append(" ar:  ");

    returning.append(*Artist);
    return returning.toStdString();
}




QString Song::getDirectory(){
    return *directory;
}
void Song::setArtist(QString artist){
    *Artist=artist;

}

void Song::setArtist(std::string artist)
{
    setArtist(QString::fromStdString(artist));

}
void Song::setDirectory(QString dir){
    *directory=dir;
}

void Song::setDirectory(std::string data)
{
    this->setDirectory(QString::fromStdString(data));
}
QString Song::getGenre(){
    return *this->album;
}
void Song::setAlbum(QString Name){
    *this->album=Name;
}
void Song::setAlbum(std::string Name){
  this->setAlbum(QString::fromStdString(Name));
}
Song::~Song(){
    //free(Artist);
    //free(directory);
    //free(FileName);
    //free(genre);
}

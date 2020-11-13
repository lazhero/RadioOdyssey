#include "song.h"

Song::Song()
{
    isLocal=true;

}
QString Song::getArtist(){
    return Artist;
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
    return this->FileName;
}
void Song::setFileName(QString Name){
    this->FileName=Name;
}
void Song::setFileName(std::string Name){
    this->setFileName(QString::fromStdString(Name));
}

std::string Song::toString()
{
    QString returning;
    returning.append(FileName);
    returning.append(Artist);
    return returning.toStdString();
}
QString Song::getDirectory(){
    return directory;
}
void Song::setArtist(QString artist){
    Artist=artist;

}

void Song::setArtist(std::string artist)
{
    setArtist(QString::fromStdString(artist));

}
void Song::setDirectory(QString dir){
    directory=dir;
}

void Song::setDirectory(std::string data)
{
    this->setDirectory(QString::fromStdString(data));
}
QString Song::getGenre(){
    return this->genre;
}
void Song::setGenre(QString Name){
    this->genre=Name;
}
void Song::setGenre(std::string Name){
  this->setGenre(QString::fromStdString(Name));
}
Song::~Song(){
    //free(Artist);
    //free(directory);
    //free(FileName);
    //free(genre);
}

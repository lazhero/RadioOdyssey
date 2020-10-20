#include "song.h"

Song::Song()
{
    Artist=new QString;
    directory=new QString;
}
QString Song::getArtist(){
    return *Artist;
}
QString Song::getDirectory(){
    return *directory;
}
void Song::setArtist(QString artist){
    *Artist=artist;

}
void Song::setDirectory(QString dir){
    *directory=dir;
}
Song::~Song(){
    free(Artist);
    free(directory);
}

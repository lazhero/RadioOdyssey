#include "song.h"

Song::Song()
{
    Artist=new QString;
    directory=new QString;
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

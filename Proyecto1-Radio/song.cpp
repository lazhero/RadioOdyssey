#include "song.h"

Song::Song()
{
    isLocal=true;

}
/**
 * Converts the object to a string
 * @brief Song::toString
 * @return
 */
std::string Song::toString()
{
    QString returning;
    returning.append(FileName);
    returning.append(" | ");
    returning.append(cutText(OrName,10));
    returning.append(" | ");
    returning.append(cutText(Artist,10));
    returning.append(" | ");
    returning.append(cutText(Album,10));
    return returning.toStdString();
}
/**
 * Resizes strings for visualization
 * @brief Song::cutText
 * @param text
 * @param size
 * @return
 */
QString Song::cutText(QString text, int size){

    std::string textaux=text.toStdString().substr(0,size);


    while (QString::fromStdString(textaux).length()<size) {

        textaux.append(" ");

    }

    return  QString::fromStdString(textaux);
}


///////////////////////////////////////////////////////////////////
                //setters an getters//
///////////////////////////////////////////////////////////////////
/**
 * @brief Song::getArtist
 * @return
 */
QString Song::getArtist(){
    return Artist;
}

/**
 * @brief Song::setLocalState
 * @param state
 */
void Song::setLocalState(bool state)
{
    isLocal=state;
}
/**
 * @brief Song::getLocalState
 * @return
 */
bool Song::getLocalState()
{
    return isLocal;
}
/**
 * @brief Song::getFileName
 * @return
 */
QString Song::getFileName()
{
    return this->FileName;
}
/**
 * @brief Song::setFileName
 * @param Name
 */
void Song::setFileName(QString Name){
    this->FileName=Name;
}
/**
 * @brief Song::setFileName
 * @param Name
 */
void Song::setFileName(std::string Name){
    this->setFileName(QString::fromStdString(Name));
}

QString Song::getAlbum() const
{
    return Album;
}
/**
 * @brief Song::setAlbum
 * @param value
 */
void Song::setAlbum(const std::string &value)
{
    Album = QString::fromStdString( value);
}
/**
 * @brief Song::getDirectory
 * @return
 */
QString Song::getDirectory(){
    return directory;
}
/**
 * @brief Song::setArtist
 * @param artist
 */
void Song::setArtist(QString artist){
    Artist=artist;

}
/**
 * @brief Song::setArtist
 * @param artist
 */
void Song::setArtist(std::string artist)
{
    setArtist(QString::fromStdString(artist));

}
/**
 * @brief Song::setDirectory
 * @param dir
 */
void Song::setDirectory(QString dir){
    directory=dir;
}
/**
 * @brief Song::setDirectory
 * @param data
 */
void Song::setDirectory(std::string data)
{
    this->setDirectory(QString::fromStdString(data));
}
/**
 * @brief Song::getGenre
 * @return
 */
QString Song::getGenre(){
    return this->OrName;
}
/**
 * @brief Song::setOrName
 * @param Name
 */
void Song::setOrName(QString Name){
    this->OrName=Name;
}
/**
 * @brief Song::setOrName
 * @param Name
 */
void Song::setOrName(std::string Name){
  this->setOrName(QString::fromStdString(Name));
}
/**
 * @brief Song::~Song
 */
Song::~Song(){
    //free(Artist);
    //free(directory);
    //free(FileName);
    //free(genre);
}

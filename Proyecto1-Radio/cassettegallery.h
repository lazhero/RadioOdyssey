#ifndef CASSETTEGALLERY_H
#define CASSETTEGALLERY_H
#include<pages.h>
#include<filemanager.h>
#include<string>
#include<csvhandler.h>
#include<stringtools.h>
#include<stringiterator.h>
class CassetteGallery
{
public:
    CassetteGallery(int requestedLen);
    ~CassetteGallery();

    void setRequestLen(int len);
    int getRequestLen();

    void setCsvDir(std::string dir);
    std::string getCsvDir();

    void setSourceDir(std::string dir);
    std::string getSourceDir();

    int getStartPos() const;
    void setStartPos(int value);

    int getEndPos() const;
    void setEndPos(int value);

    int getNamePosition() const;
    void setNamePosition(int value);

    int getArtistPosition() const;
    void setArtistPosition(int value);

    int getAlbumPosition() const;
    void setAlbumPosition(int value);

    int getGenrePosition() const;
    void setGenrePosition(int value);

    void setIterator(stringIterator iterator);
    stringIterator getIterator();

    bool moveForwards();
    bool moverBackwards();



private:

    int requestedLen;
    int startPos;
    int endPos;
    int NamePosition;
    int ArtistPosition;
    int AlbumPosition;
    int GenrePosition;


    std::string * sourceDir;
    std::string* csvDir;

    Pages* page;
    CSVHandler* csvHandler;
    stringIterator* iterator;
    DoubleList<DoubleList<std::string>>* CSVList;

    Song* getSong(DoubleList<std::string>* AtributeList);




};

#endif // CASSETTEGALLERY_H

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

    int getStartPos();
    void setStartPos(int value);

    void configure(int Size , std::string route, stringIterator* iterator,std::string dir);

    int getEndPos();
    void setEndPos(int value);

    int getNamePosition();
    void setNamePosition(int value);

    int getArtistPosition();
    void setArtistPosition(int value);

    int getAlbumPosition();
    void setAlbumPosition(int value);

    int getGenrePosition();
    void setOrnamePosition(int value);

    void setIterator(stringIterator* iterator);
    stringIterator getIterator();

    bool moveForwards();
    bool moverBackwards();

    int getUsedMemory();



   DoubleList<Song>* getActualList();



private:

    int requestedLen;
    int startPos;
    int endPos;
    int NamePosition;
    int ArtistPosition;
    int AlbumPosition;
    int OrNamePosition;


    std::string * sourceDir;
    std::string* csvDir;

    Pages* page;
    CSVHandler* csvHandler;
    stringIterator* iterator;
    DoubleList<DoubleList<std::string>>* CSVList;
    DoubleList<std::string> *FilesList;
    DoubleList<std::string> *SubDirectoryList;
    std::vector<DoubleList<std::string>*>* csvData;
    Song* getSong(DoubleList<std::string>* AtributeList);
    void add(int n);
    void clear();
    void initCSV(int number);





};

#endif // CASSETTEGALLERY_H

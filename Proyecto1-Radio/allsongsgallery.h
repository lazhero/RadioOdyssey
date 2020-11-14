#ifndef ALLSONGSGALLERY_H
#define ALLSONGSGALLERY_H
#include<vector>
#include<DoubleList/DoubleList.hpp>
#include<filemanager.h>
#include<csvhandler.h>
#include<myproyectstringiterator.h>
#include<pages.h>



class AllSongsGallery
{
public:
    AllSongsGallery();
    int getNamePosition() const;

    int getArtistPosition() const;

    int getGenrePosition() const;

    int getAlbumPosition() const;
    void setAlbumPosition(int value);

    void setSource(std::string source);
    void setIterator(MyProyectStringIterator iterator);
    void startReading();




    int getRequestedLen() const;
    void setRequestedLen(int value);

    void setArtistPosition(int value);

    void setGenrePosition(int value);

    void setNamePosition(int value);

    void clear();
    void moveForward();
    void moveBackward();
    DoubleList<Song>* getActualPage();


    std::string getCsvDir() const;
    void setCsvDir(const std::string &value);

    bool getPagingCondition() const;
    void setPagingCondition(bool value);

     int getUsedMemory();

private:
    int start;
    int end;
    int NamePosition;
    int ArtistPosition;
    int GenrePosition;
    int AlbumPosition;
    int requestedLen;
    bool PagingCondition;

    std::string sourceDir;

    CSVHandler* handler;
    std::vector<DoubleList<std::string>*>* csvData;
    std::vector<std::string>* Directories;
    MyProyectStringIterator iterator;

    Pages *pages;


    std::string csvDir;
    void add(int n);
    std::string buildString(std::string subDirectory,std::string filename);
    Song getSong(int position);
    void AddNSong(int n);



};

#endif // ALLSONGSGALLERY_H

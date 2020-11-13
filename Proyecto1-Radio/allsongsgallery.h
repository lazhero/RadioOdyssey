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





    int getRequestedLen() const;
    void setRequestedLen(int value);

    void setArtistPosition(int value);

    void setGenrePosition(int value);

    void setNamePosition(int value);

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

    void startReading();

    void add(int n);
    std::string buildString(std::string subDirectory,std::string filename);
    Song getSong(int position);
    void moveForward();
    void moveBackward();
    void AddNSong(int n);
    void clear();


};

#endif // ALLSONGSGALLERY_H
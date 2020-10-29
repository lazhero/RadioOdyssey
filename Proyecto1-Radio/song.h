#ifndef SONG_H
#define SONG_H
#include<QString>

class Song
{
public:
    Song();
    ~Song();
    void setDirectory(QString dir);
    void setDirectory(std::string);
    QString getDirectory();
    void setArtist(QString artist);
    void setArtist(std::string artist);
    QString getArtist();
    QString getGenre();
    void setGenre(QString Name);
    void setGenre(std::string Name);
    void setLocalState(bool state);
    bool getLocalState();
    QString getFileName();
    void setFileName(QString Name);
    void setFileName(std::string Name);
    std::string toString();
private:
    QString* FileName;
    QString* directory;
    QString * Artist;
    QString* genre;
    bool isLocal;
};

#endif // SONG_H

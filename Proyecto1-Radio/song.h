#ifndef SONG_H
#define SONG_H
#include<QString>

class Song
{
public:
    Song();
    ~Song();
    void setDirectory(QString dir);
    QString getDirectory();
    void setArtist(QString artist);
    QString getArtist();
    void setLocalState(bool state);
    bool getLocalState();

private:
    QString* directory;
    QString * Artist;
    bool isLocal;
};

#endif // SONG_H

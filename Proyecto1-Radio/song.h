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

private:
    QString* directory;
    QString * Artist;
};

#endif // SONG_H

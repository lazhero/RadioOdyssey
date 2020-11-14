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
    void setOrName(QString Name);
    void setOrName(std::string Name);
    void setLocalState(bool state);
    bool getLocalState();
    QString getFileName();
    void setFileName(QString Name);
    void setFileName(std::string Name);
    std::string toString();
    QString getAlbum() const;
    void setAlbum(const std::string &value);

private:
    QString FileName;
    QString cutText(QString text, int size);
    QString directory;
    QString  Artist;
    QString OrName;
    QString Album;
    bool isLocal;
};

#endif // SONG_H

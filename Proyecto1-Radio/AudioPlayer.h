#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include"song.h"

class AudioPlayer
{
public:
    AudioPlayer(){};
    virtual void Play()=0;
    virtual void Pause()=0;
    virtual void Stop()=0;
    virtual void Skip()=0;
    virtual void setVolumen(int volumen)=0;
    virtual void addToPlayList(Song song)=0;
    virtual void MiltonPutoAmo()=0;

private:

};

#endif // AUDIOPLAYER_H

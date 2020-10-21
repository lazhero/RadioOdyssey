
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include"AudioPlayer.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>

class MusicPlayer: public AudioPlayer
{
public:
    MusicPlayer();
    void Play();
    void Pause();
    void Stop();
    void Skip();
    void addToPlayList(Song song);
    void setVolumen(int volumen);
    double currentMediaDuration();
private:
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    void deleteFirst();


};

#endif // MUSICPLAYER_H

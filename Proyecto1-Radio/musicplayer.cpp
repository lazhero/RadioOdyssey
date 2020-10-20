#include "musicplayer.h"
#include<QUrl>
int lowest=0;
MusicPlayer::MusicPlayer()
{
    player=new QMediaPlayer;
    playlist=new QMediaPlaylist;
    player->setPlaylist(playlist);
}
void MusicPlayer::Play(){
    player->play();

}
void MusicPlayer::Stop(){
    player->stop();
}
void MusicPlayer::Pause(){
    player->pause();
}
void MusicPlayer::Skip(){
    player->stop();
    playlist->next();
    player->play();
}
void MusicPlayer::addToPlayList(Song song){
    if(song.getLocalState())playlist->addMedia(QUrl::fromLocalFile(song.getDirectory()));
    else playlist->addMedia(QUrl(song.getDirectory()));
}

void MusicPlayer::setVolumen(int volumen)
{
    if(volumen<0 || volumen>100)return;
    player->setVolume(volumen);
}
void MusicPlayer::deleteFirst(){
    if(!playlist->isEmpty()){
        playlist->removeMedia(lowest);
    }
}
double MusicPlayer::currentMediaDuration(){
    return  player->duration();
}

#include "musicplayer.h"
#include<QUrl>
int lowest=0;
MusicPlayer::MusicPlayer()
{
    player=new QMediaPlayer;
    playlist=new QMediaPlaylist;
    player->setPlaylist(playlist);
}
/**
 * reproduces the current song
 * @brief MusicPlayer::Play
 * @author Luis Zuniga
 */
void MusicPlayer::Play(){
    player->play();

}

/**
 * stop the current song
 * @brief MusicPlayer::Stop
 * @author Luis Zuniga
 */
void MusicPlayer::Stop(){
    player->stop();
}
/**
 * pause the current song
 * @brief MusicPlayer::Pause
 * @author Luis Zuniga
 */
void MusicPlayer::Pause(){
    player->pause();
}
/**
 * skip the actual song
 *  @brief MusicPlayer::Skip
 * @author Luis Zuniga
 */
void MusicPlayer::Skip(){
    player->stop();
    playlist->next();
    player->play();
}
/**
 * add a song to the playlist
 * @brief MusicPlayer::addToPlayList
 * @param song
 * @author Luis Zuniga
 */
void MusicPlayer::addToPlayList(Song song){
    if(song.getLocalState())
    {
        playlist->removeMedia(0);
        //MODIFICACION AQUI, SE BORRA VACIA LA LISTA PARA EVITAR CIERTOS ERRORES
        playlist->addMedia(QUrl::fromLocalFile(song.getDirectory()));
    }


    else
    {
        playlist->addMedia(QUrl(song.getDirectory()));
    }
}

/**
 * establishes the song volume
 * @brief MusicPlayer::setVolumen
 * @param volumen
 * @author Luis Zuniga
 */
void MusicPlayer::setVolumen(int volumen)
{
    if(volumen>=0 && volumen<=100){
        player->setVolume(volumen);
    }

}
/**
 * delete the first song of the playlist
 *  @brief MusicPlayer::deleteFirst
 * @author Luis Zuniga
 */
void MusicPlayer::deleteFirst(){
    if(!playlist->isEmpty()){
        playlist->removeMedia(lowest);
    }
}
/**
 * returns the song duration in miliseconds
 * @brief MusicPlayer::currentMediaDuration
 * @return  double
 */
double MusicPlayer::currentMediaDuration(){
    return  player->duration();
}

/**
 * returns if the song is paused
 * @brief MusicPlayer::isStop
 * @return  bool
 * @author Adrian Gonzalez
 */
bool MusicPlayer::isStop(){
    bool resultado=player->state()== QMediaPlayer::PausedState; //si esta sonando true
    return resultado;
}
/**
 * set the song in some time especified
 * @brief MusicPlayer::setTime
 * @param milisecond
 * @author Adrian
 */
void MusicPlayer::setTime(int milisecond){
    player->setPosition(milisecond);

}

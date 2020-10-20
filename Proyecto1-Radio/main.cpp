#include "widget.h"
#include"song.h"
#include"musicplayer.h"
#include "QDir"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Song* song=new Song;
    song->setDirectory(QDir().absoluteFilePath("../Proyecto1-Radio/Resources/Music/testBach.mp3"));
    AudioPlayer* player=new MusicPlayer;
    player->setVolumen(90);
    player->addToPlayList(*song);
    player->Play();
    Widget w;
    w.show();
    return a.exec();
}

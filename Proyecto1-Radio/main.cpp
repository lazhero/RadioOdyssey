#include "widget.h"
#include"song.h"
#include"musicplayer.h"
#include "QDir"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

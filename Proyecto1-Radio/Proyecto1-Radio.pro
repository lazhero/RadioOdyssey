QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += multimedia
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    cassettegallery.cpp \
    csvhandler.cpp \
    csvsorting.cpp \
    filemanager.cpp \
    clikable_item.cpp \
    localfilegetter.cpp \
    main.cpp \
    myproyectstringiterator.cpp \
    pages.cpp \
    stringIterator.cpp \
    stringtools.cpp \
    widget.cpp\
    musicplayer.cpp \
    song.cpp

HEADERS += \
    SongGetter.h \
    cassettegallery.h \
    csvhandler.h \
    csvsorting.h \
    filemanager.h \
    clikable_item.h \
    localfilegetter.h \
    myproyectstringiterator.h \
    pages.h \
    stringiterator.h \
    stringtools.h \
    widget.h\
    AudioPlayer.h \
    mainwindow.h \
    musicplayer.h \
    song.h\
    DoubleNode/DoubleNode.hpp\
    DoubleList/DoubleList.hpp

FORMS += \
    widget.ui

# Default rules for deployment.
QMAKE_CXXFLAGS+= -std=c++17
QMAKE_LFLAGS +=  -std=c++17
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES += \
    Resources/Images/volume.png


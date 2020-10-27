#ifndef PAGES_H
#define PAGES_H
#include<DoubleList/DoubleList.hpp>
#include<song.h>


class Pages
{
public:
    Pages(int len);
    void AddToBack(Song song);
    void AddToFront(Song song);
    int getListLen();
    void setListLen(int len);
    bool isFull();

private:
    int ListLen;
    DoubleList<Song>* Prev;
    DoubleList<Song> * Actual;
    DoubleList<Song>* Next;
    bool lenVerification(int len);
    void iterateFront();
    void iterateBack();
};

#endif // PAGES_H

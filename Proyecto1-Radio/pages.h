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
    DoubleList<Song>* getActual();
    bool isFull();
    void swap(int a,int b);
    void emptyBack();

private:
    int ListLen;
    DoubleList<Song>* Prev;
    DoubleList<Song> * Actual;
    DoubleList<Song>* Next;
    bool lenVerification(int len);
    void iterateFront();
    void iterateBack();
    void DeleteLeftOver();


};

#endif // PAGES_H

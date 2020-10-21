#ifndef SONGGETTER_H
#define SONGGETTER_H
#include<song.h>
#include<string>
class SongGetter{
public:
    virtual Song getSong(QString id)=0;
    virtual Song getSong(std::string id)=0;
    virtual void setSource(QString source)=0;
    virtual void setSouce(std::string source)=0;
    virtual QString getSource()=0;
};

#endif // SONGGETTER_H

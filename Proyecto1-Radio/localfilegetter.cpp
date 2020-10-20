#include "localfilegetter.h"
#include<iostream>
std::string empty_value="";
const char delim='/';
LocalfileGetter::LocalfileGetter()
{
    Source_Route=new QString;

}

Song LocalfileGetter::getSong(QString id)
{
    std::string route=getRoute(Source_Route->toStdString(),id.toStdString());
    Song* song=new Song;
    song->setDirectory(QString::fromStdString(route));
    return *song;
}

Song LocalfileGetter::getSong(std::string id)
{
    return this->getSong(QString::fromStdString(id));
}

void LocalfileGetter::setSource(QString source)
{
    *Source_Route=source;

}
void LocalfileGetter::setSouce(std::string source){
    *Source_Route=QString::fromStdString(source);
}

QString LocalfileGetter::getSource()
{
    return *new QString;
}

std::string LocalfileGetter::getRoute(std::string route,std::string value)
{
    std::string sonReturn;
    for(auto& p: fs::directory_iterator(route)){
      if(p.is_directory()){
          if((sonReturn=getRoute(p.path(),value)).compare(empty_value)!=0)return sonReturn;
      }
      else if(p.path().filename().compare(value)==0)return p.path();


    }
    return empty_value;
}

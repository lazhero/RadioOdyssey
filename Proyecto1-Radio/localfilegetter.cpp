#include "localfilegetter.h"
#include<iostream>
std::string empty_value="";
LocalfileGetter::LocalfileGetter()
{
    Source_Route=new QString;

}
/**
 * Create a "song" instance and asociate it with a file by a pointer
 * @brief LocalfileGetter::getSong
 * @param id
 * @return Song
 * @author Luis zuniga
 */
Song LocalfileGetter::getSong(QString id)
{
    std::string route=getRoute(Source_Route->toStdString(),id.toStdString());
    Song song;
    song.setDirectory(QString::fromStdString(route));
    std::cout<<"imprimiendo: "<< route <<std::endl;
    return song;
}
/**
 * Auxiliar of other funtion
 * @brief LocalfileGetter::getSong
 * @param id
 * @return Song
 * @author Luis zuniga
 */
Song LocalfileGetter::getSong(std::string id)
{
    return this->getSong(QString::fromStdString(id));
}

/**
 * @brief LocalfileGetter::setSource
 * @param source
 */

void LocalfileGetter::setSource(QString source)
{
    *Source_Route=source;

}

/**
 * @brief LocalfileGetter::setSouce
 * @param source
 */
void LocalfileGetter::setSouce(std::string source){
    *Source_Route=QString::fromStdString(source);
}
/**
 * @brief LocalfileGetter::getSource
 * @return
 */

QString LocalfileGetter::getSource()
{
    return *new QString;
}

DoubleList<std::string> *LocalfileGetter::getDirectoryList()
{
    return getRoutesList(true);

}

DoubleList<std::string> *LocalfileGetter::getFilesList()
{
    return getRoutesList(false);

}

DoubleList<std::string> *LocalfileGetter::getRecursiveFileList()
{

    std::string temp;
    DoubleList<std::string> * ReturnList=new DoubleList<std::string>;
    for(auto& p: fs::recursive_directory_iterator(Source_Route->toStdString())){
      if(!p.is_directory()){
          temp=p.path();
          ReturnList->add(temp);
      }

    }
    return ReturnList;

}



/**
 * look for a file with name "value" and save it directory
 * @brief LocalfileGetter::getRoute
 * @param route
 * @param value
 * @author Luis zuniga
 * @return
 */
std::string LocalfileGetter::getRoute(std::string route,std::string value)
{
    std::string sonReturn;
    for(auto& p: fs::directory_iterator(route)){
      if(p.is_directory()){
          if((sonReturn=getRoute(p.path(),value)).compare(empty_value)!=0)
              return sonReturn;
      }
      else
          if(p.path().filename().compare(value)==0)
              return p.path();


    }
    return empty_value;
}

DoubleList<std::string> *LocalfileGetter::getRoutesList(bool ISDIRECTORY)
{
    std::string temp;
    DoubleList<std::string> * ReturnList=new DoubleList<std::string>;

    for(auto& p: fs::directory_iterator(Source_Route->toStdString())){
      if(p.is_directory()==ISDIRECTORY){

          temp=p.path();
          ReturnList->add(temp);
      }

    }
    return ReturnList;
}







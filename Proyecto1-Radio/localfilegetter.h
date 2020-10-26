
#ifndef LOCALFILEGETTER_H
#define LOCALFILEGETTER_H
#include<SongGetter.h>
#include <filesystem>
#include<DoubleList/DoubleList.hpp>
#include<exception>
namespace fs =std::filesystem ;
class LocalfileGetter:SongGetter
{
public:
    LocalfileGetter();
    Song getSong(QString id);
    Song getSong(std::string id);
    void setSource(QString source);
    void setSouce(std::string source);
    QString getSource();
    DoubleList<std::string>* getDirectoryList();
    DoubleList<std::string>* getFilesList();
    Song getNextFile();
    std::string getNextDir();
    void restartIterator();
private:
    QString* Source_Route;
    std::string getRoute(std::string route, std::string value);
    DoubleList<std::string>* getRoutesList(bool ISDIRECTORY);
    fs::directory_iterator myIterator;
    std::filesystem::directory_entry getNextBooleanCondition(bool dirCondition);




};

struct NotFoundException:public std::exception{
    const char * what () const throw () {
        return "The file requested has been not Found";
    }
};


#endif // LOCALFILEGETTER_H

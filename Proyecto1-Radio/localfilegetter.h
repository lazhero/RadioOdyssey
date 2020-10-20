
#ifndef LOCALFILEGETTER_H
#define LOCALFILEGETTER_H
#include<SongGetter.h>
#include <filesystem>
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
private:
    QString* Source_Route;
    std::string getRoute(std::string route, std::string value);



};

#endif // LOCALFILEGETTER_H

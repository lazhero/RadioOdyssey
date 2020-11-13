#include "routetools.h"
#include<stringtools.h>
#include<QString>
RouteTools::RouteTools()
{

}

int RouteTools::getSplittedStringLen()
{
    return this->data->getLen();

}

std::string RouteTools::getDirectory(int position)
{
    return *this->data->get(position);
}

std::string RouteTools::getFileName()
{
    return getDirectory(data->getLen()-1);
}

void RouteTools::setRoute(std::string route)
{
    this->route=route;
    slip();
}
std::string RouteTools::getRoute(){
    return this->route;
}

std::string RouteTools::getSeccionRoute(int start, int final)
{
    QString string;
    for(int i=start;i<final;i++){
        string.append(QString::fromStdString(*data->get(i)));
        string.append(charDelimiter);
    }
    return string.toStdString();
}

std::string RouteTools::deleteExtension(std::string data)
{
    std::string temp;
    temp=*StringTools::slipString(extensionDelimiter,data)->get(minIndex);
    return temp;
}

void RouteTools::slip()
{
    data= StringTools::slipString(charDelimiter,route);
}


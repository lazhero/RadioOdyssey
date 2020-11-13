#ifndef ROUTETOOLS_H
#define ROUTETOOLS_H
#include<string>
#include<DoubleList/DoubleList.hpp>

class RouteTools
{
public:
    RouteTools();
    int getSplittedStringLen();
    std::string getDirectory(int position);
    std::string getFileName();
    void setRoute(std::string route);
    std::string getRoute();
    std::string getSeccionRoute(int start,int final);
    static std::string deleteExtension(std::string data);



private:
    std::string route;
    static const char charDelimiter='/';
    static const char extensionDelimiter='.';
    DoubleList<std::string>* data;

    //private methods / funcions members
    void slip();


};

#endif // ROUTETOOLS_H

#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H
#include<string>
#include<DoubleList/DoubleList.hpp>
#include<sstream>

class StringTools
{
public:
    StringTools();
    static DoubleList<std::string>* slipString(char delimiter,std::string input);
    static std::string* appendString(std::string First,std::string Second);

};

#endif // STRINGTOOLS_H

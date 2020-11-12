#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H
#include<string>
#include<DoubleList/DoubleList.hpp>
#include<sstream>
#include<QString>
class StringTools
{
public:
    StringTools();
    static DoubleList<std::string>* slipString(char delimiter,std::string input);
    static std::string* appendString(std::string First,std::string Second);
    static std::string replaceChar(std::string string, char toReplace,std::string Changed);
    static std::string reducedString(int len,std::string str);
    static std::string deleteStringFromLeft(std::string data,std::string erase);
private:
    static void fix(std::string& string,std::string erasing,bool leftcondition);


};

#endif // STRINGTOOLS_H


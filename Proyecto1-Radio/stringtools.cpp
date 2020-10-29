#include "stringtools.h"

StringTools::StringTools()
{

}

DoubleList<std::string>* StringTools::slipString(char delimiter, std::string input)
{
    DoubleList<std::string> * SlipList=new DoubleList<std::string>;
    std::stringstream stream(input);
    std::string tempSavedString;
    while (getline(stream,tempSavedString,delimiter)){
        SlipList->add(tempSavedString);
    }
    return SlipList;
}

std::string *StringTools::appendString(std::string First, std::string Second)
{
    std::string *returnString=new std::string;
    returnString->append(First);
    returnString->append(Second);
    return returnString;

}

std::string StringTools::replaceChar(std::string string, char toReplace, std::string Changed){
    int i=0;
    for(char t:string){
        if(t==toReplace){
            string.replace(i,1,Changed);
        }
        i++;
    }
    return string;
}



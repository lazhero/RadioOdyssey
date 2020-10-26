#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include "DoubleList/DoubleList.hpp"
#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>

class CSVHandler
{
public:
    CSVHandler();
    void setFileDirectory(std::string name);
    std::string getFileDirectory();
    DoubleList<std::string>* getnextLine();
    void startReading();
    DoubleList<DoubleList<std::string>>* getlines(int n);
    DoubleList<std::string>* getNextLineWith(std::string text);
    DoubleList<std::string> *getNextLineWithIn(std::string text, int position);
    DoubleList<DoubleList<std::string>>*getAllLinesWith(std::string text);
    DoubleList<DoubleList<std::string>> *getAllLinesWithIn(std::string text, int position);
    const char delimiter=',';
private:
    std::string* Route;
    std::fstream* inputStream;


};

#endif // CSVHANDLER_H

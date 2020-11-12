#pragma once
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
    DoubleList<DoubleList<std::string>> * getAllLines();
    void setForward(bool state);
    const char delimiter=',';
private:
    bool FordWard;
    const std::string emptyString="";
    std::fstream* inputStream;
    std::string * Route;

    std::istream& getTheLine(std::istream& is,std::string& str);


};

#endif // CSVHANDLER_H

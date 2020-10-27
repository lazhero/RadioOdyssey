#ifndef CSVSORTING_H
#define CSVSORTING_H
#include<string>
#include<filemanager.h>
#include<csvhandler.h>
#include<localfilegetter.h>
#include<stringtools.h>
#include<stringiterator.h>
class CSVSorting
{
public:

    CSVSorting();
    void sortToDirectory();
    void setSource(std::string source);
    void setOutputDirectory(std::string dir);
    void setCsvDirectory(std::string dir);
    void setReferencePosition(int position);
    void setFilePosition(int position);
    std::string getSource();
    std::string getOutputDirectory();
    std::string getCsvDirectory();
    int getReferencePosition();
    int getFilePosition();
    void setIterator(stringIterator &iterator);


private:
    bool verification();
    std::string source;
    std::string OutputDirectory;
    std::string CsvDirectory;
    int ReferencePosition;
    int FilePosition;
    stringIterator *iterator;
    const std::string verificationFile="Sucess.txt";


};

#endif // CSVSORTING_H

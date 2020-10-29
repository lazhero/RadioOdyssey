#include "csvsorting.h"
std::string delimiter="/";
char charDelimiter='/';
std::string voidString;
std::string Filetext="Job Done";
std::string substitute="-";
CSVSorting::CSVSorting()
{


}

void CSVSorting::sortToDirectory()
{

    if(verification())return;
    CSVHandler* handler1=new CSVHandler;
    CSVHandler* handle2=new CSVHandler;
    DoubleList<std::string>* csvLine;
    DoubleList<DoubleList<std::string>>* FilesMatrix;
    LocalfileGetter* getter=new LocalfileGetter;
    std::string tempRoute;
    std::string OutputSubDirectory;
    std::string FileName;
    std::string* fixDirectory;
    std::string FixedSubDirectory;
    getter->setSouce(source);
    handler1->setFileDirectory(CsvDirectory);
    handle2->setFileDirectory(CsvDirectory);
    handler1->startReading();
    handle2->startReading();

    for(csvLine=handler1->getnextLine();csvLine->getLen()>0;csvLine=handler1->getnextLine()){
        if(ReferencePosition>=csvLine->getLen())continue;
        OutputSubDirectory=*csvLine->get(ReferencePosition);
        FixedSubDirectory=StringTools::replaceChar(OutputSubDirectory,charDelimiter,substitute);
        if(FileManager::canOpen(*StringTools::appendString(*StringTools::appendString(OutputDirectory,delimiter),FixedSubDirectory)))continue;
        FileManager::createDirectory(OutputDirectory,FixedSubDirectory);
        if(OutputSubDirectory.compare(voidString)==0)continue;
        FilesMatrix=handle2->getAllLinesWithIn(OutputSubDirectory,ReferencePosition);
        for(int i=0;i<FilesMatrix->getLen();i++){
            if(FilesMatrix->get(i)->getLen()<=FilePosition)continue;
            FileName=*FilesMatrix->get(i)->get(FilePosition);
            if(FileName.compare(voidString)==0)continue;
            FileName=iterator->iterateString(FileName);
            tempRoute= getter->getSong(FileName).getDirectory().toStdString();
            if(!FileManager::canOpen(tempRoute))continue;
            fixDirectory=StringTools::appendString(OutputDirectory,delimiter);
            fixDirectory=StringTools::appendString(*fixDirectory,OutputSubDirectory);
            fixDirectory=StringTools::appendString(*fixDirectory,delimiter);
            fixDirectory=StringTools::appendString(*fixDirectory,FileName);
            FileManager::copyFile(tempRoute,*fixDirectory);
            free(fixDirectory);
        }

        handle2->startReading();


    }

    free(handler1);
    free(handle2);
    free(csvLine);
    FileManager::createFile(OutputDirectory,verificationFile,Filetext);

}

void CSVSorting::setSource(std::string source)
{
    this->source=source;

}
void CSVSorting::setCsvDirectory(std::string dir){
    this->CsvDirectory=dir;
}
void CSVSorting::setOutputDirectory(std::string dir){
    this->OutputDirectory=dir;
}
void CSVSorting::setFilePosition(int position){
    this->FilePosition=position;
}
void CSVSorting::setReferencePosition(int position){
    this->ReferencePosition=position;
}
std::string CSVSorting::getCsvDirectory(){
    return this->CsvDirectory;
}
std::string CSVSorting::getOutputDirectory(){
    return this->OutputDirectory;
}
std::string CSVSorting::getSource(){
    return this->source;
}
int CSVSorting::getFilePosition(){
    return this->FilePosition;
}

void CSVSorting::setIterator(stringIterator &iterator)
{
    this->iterator=&iterator;
}

bool CSVSorting::verification()
{
    std::string direction;
    direction.append(OutputDirectory);
    direction.append(delimiter);
    direction.append(verificationFile);
    if(FileManager::canOpen(direction))return true;
    return false;
}
int CSVSorting::getReferencePosition(){
    return this->ReferencePosition;
}



#include "csvsorting.h"
#include<DoubleList/InsertionSort.hpp>
std::string delimiter="/";
char charDelimiter='/';
std::string voidString;
std::string Filetext="Job Done";
std::string substitute="-";
int maxLen=40;

/**
 * @brief CSVSorting::CSVSorting
 */

CSVSorting::CSVSorting()
{


}
/**
 * @brief CSVSorting::sortToDirectory
 */
void CSVSorting::sortToDirectory()
{

    if(verification())return;
    DoubleList<DoubleList<std::string>>* FilesMatrix;
    LocalfileGetter* getter=new LocalfileGetter;
    std::string tempRoute;
    std::string OutputSubDirectory;
    std::string FileName;
    std::string* fixDirectory;
    std::string FixedSubDirectory;
    getter->setSouce(source);
    initializeMatriz();
    while(csvMatrix->getLen()>0){
        OutputSubDirectory=getReference();
        if(OutputSubDirectory.compare(voidString)==0)continue;
        FixedSubDirectory=StringTools::replaceChar(OutputSubDirectory,charDelimiter,substitute);
        FixedSubDirectory=StringTools::reducedString(maxLen,FixedSubDirectory);
        FilesMatrix=getNextIDFrame();
        if(FileManager::canOpen(*StringTools::appendString(*StringTools::appendString(OutputDirectory,delimiter),FixedSubDirectory)))continue;
        FileManager::createDirectory(OutputDirectory,FixedSubDirectory);
        for(int i=0;i<FilesMatrix->getLen();i++){
            if(FilesMatrix->get(i)->getLen()<=FilePosition)continue;
            FileName=*FilesMatrix->get(i)->get(FilePosition);
            if(FileName.compare(voidString)==0)continue;
            FileName=iterator->iterateString(FileName);
            tempRoute= getter->getSong(FileName).getDirectory().toStdString();
            if(!FileManager::canOpen(tempRoute))continue;
            fixDirectory=StringTools::appendString(OutputDirectory,delimiter);
            fixDirectory=StringTools::appendString(*fixDirectory,FixedSubDirectory);
            fixDirectory=StringTools::appendString(*fixDirectory,delimiter);
            fixDirectory=StringTools::appendString(*fixDirectory,FileName);
            FileManager::copyFile(tempRoute,*fixDirectory);
            free(fixDirectory);
        }
        free(FilesMatrix);


    }


    FileManager::createFile(OutputDirectory,verificationFile,Filetext);

}
/**
 * @brief CSVSorting::setSource
 * @param source
 */
void CSVSorting::setSource(std::string source)
{
    this->source=source;

}
/**
 * @brief CSVSorting::setCsvDirectory
 * @param dir
 */
void CSVSorting::setCsvDirectory(std::string dir){
    this->CsvDirectory=dir;
}
/**
 * @brief CSVSorting::setOutputDirectory
 * @param dir
 */
void CSVSorting::setOutputDirectory(std::string dir){
    this->OutputDirectory=dir;
}
/**
 * @brief CSVSorting::setFilePosition
 * @param position
 */
void CSVSorting::setFilePosition(int position){
    this->FilePosition=position;
}
/**
 * @brief CSVSorting::setReferencePosition
 * @param position
 */
void CSVSorting::setReferencePosition(int position){
    this->ReferencePosition=position;
}
/**
 * @brief CSVSorting::getCsvDirectory
 * @return
 */
std::string CSVSorting::getCsvDirectory(){
    return this->CsvDirectory;
}
/**
 * @brief CSVSorting::getOutputDirectory
 * @return
 */
std::string CSVSorting::getOutputDirectory(){
    return this->OutputDirectory;
}
/**
 * @brief CSVSorting::getSource
 * @return
 */
std::string CSVSorting::getSource(){
    return this->source;
}
/**
 * @brief CSVSorting::getFilePosition
 * @return
 */
int CSVSorting::getFilePosition(){
    return this->FilePosition;
}
/**
 * @brief CSVSorting::setIterator
 * @param iterator
 */
void CSVSorting::setIterator(stringIterator &iterator)
{
    this->iterator=&iterator;
}
/**
 * @brief CSVSorting::verification
 * @return
 */
bool CSVSorting::verification()
{
    std::string direction;
    direction.append(OutputDirectory);
    direction.append(delimiter);
    direction.append(verificationFile);
    if(FileManager::canOpen(direction))return true;
    return false;
}
/**
 * @brief CSVSorting::getNextIDFrame
 * @return
 */
DoubleList<DoubleList<std::string>>*  CSVSorting::getNextIDFrame(){

    DoubleList<DoubleList<std::string>> * tempList=new DoubleList<DoubleList<std::string>>;
    std::string referenceString=getReference();
    bool stopflag=false;
    while(csvMatrix->getLen()>0  && !stopflag){
        if(csvMatrix->get(minIndex)->getLen()<= ReferencePosition)stopflag=true;
        else if(csvMatrix->get(minIndex)->get(ReferencePosition)->compare(referenceString)!=0)stopflag=true;
        else{
            tempList->add(*csvMatrix->get(minIndex));
            csvMatrix->erase(minIndex);

        }

    }
    return tempList;

}
/**
 * @brief CSVSorting::getReference
 * @return
 */
std::string CSVSorting::getReference()
{
    std::string returning;
    DoubleList<std::string> * tempList;
    bool foundCondition=false;
    while(csvMatrix->getLen()>0 && !foundCondition){
        tempList=csvMatrix->get(minIndex);
        if(tempList->getLen()<=ReferencePosition){
            csvMatrix->erase(minIndex);
        }
        else if(tempList->get(ReferencePosition)->compare("")==0)csvMatrix->erase(minIndex);
        else{
            foundCondition=true;
            returning=*tempList->get(ReferencePosition);
        }
    }
    return returning;

}
/**
 * @brief CSVSorting::initializeMatriz
 */
void CSVSorting::initializeMatriz()
{
    CSVHandler* handler=new CSVHandler;
    handler->setFileDirectory(CsvDirectory);
    handler->startReading();
    DoubleList<DoubleList<std::string>>* Matriz=handler->getAllLines();
    DoubleList<std::string>* tempLine=new DoubleList<std::string>;
    csvMatrix=new DoubleList<DoubleList<std::string>>;
    std::string tempReference;
    while(Matriz->getLen()>0 && false){
        if(Matriz->get(minIndex)->getLen()<=ReferencePosition){
            Matriz->erase(minIndex);
        }
        else{
            tempReference=*Matriz->get(minIndex)->get(ReferencePosition);
            for(int i=minIndex;i<Matriz->getLen();i++){
                tempLine=Matriz->get(i);
                if(tempLine->getLen()<=ReferencePosition){
                    Matriz->erase(i);
                }
                else if(tempLine->get(ReferencePosition)->compare(tempReference)==0){
                    csvMatrix->add(*tempLine);
                    Matriz->erase(i);
           ^
int CSVSorting::getReferencePosition(){
    return this->ReferencePosition;
}



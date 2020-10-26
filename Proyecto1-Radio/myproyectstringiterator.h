#ifndef MYPROYECTSTRINGITERATOR_H
#define MYPROYECTSTRINGITERATOR_H
#include<stringiterator.h>

class MyProyectStringIterator: public stringIterator
{
public:
    MyProyectStringIterator();
    std::string iterateString(std::string data)override;
    std::string getBefore();
    std::string getAfter();
    void setAfter(std::string data);
    void setBefore(std::string data);
    int getBeforeDigits();
    void setBeforeDigits(int data);
private:
    std::string before;
    std::string after;
    int BeforeDigits;
};

#endif // MYPROYECTSTRINGITERATOR_H

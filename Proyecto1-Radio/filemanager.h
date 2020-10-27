#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<filesystem>
#include<fstream>
class FileManager
{
public:
    static void copyFile(std::string Source,std::string To);
    static void createDirectory(std::string Root, std::string Name);
    static bool canOpen(std::string path);
    static std::string delimiter;
    static void createFile(std::string root,std::string filename,std::string text);

};

#endif // FILEMANAGER_H

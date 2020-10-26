#include "filemanager.h"


void FileManager::copyFile(std::string Source, std::string To)
{
    std::filesystem::copy_file(Source,To);
}

void FileManager::createDirectory(std::string Root, std::string Name)
{
    std::filesystem::create_directory(Root.append(delimiter).append(Name));
}

bool FileManager::canOpen(std::string path)
{
    return std::filesystem::exists(path);
}

void FileManager::createFile(std::string root, std::string filename,std::string text)
{
    std::fstream stream(root.append(delimiter).append(filename));
    stream<<text<<std::endl;
}
std::string FileManager::delimiter="/";

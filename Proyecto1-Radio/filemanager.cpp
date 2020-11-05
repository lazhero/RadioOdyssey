#include "filemanager.h"
#include<stdio.h>
std::string emptyString="";


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

void FileManager::DeleteEmptyDir(std::string route)
{
    if(route.compare(emptyString)==0)return;
    if(!canOpen(route))return;
    for(auto& p: std::filesystem::directory_iterator(route)){
      if(p.is_directory()){
          if(std::filesystem::is_empty(p.path())){
              remove(p.path().c_str());
          }
      }
    }
}
std::string FileManager::delimiter="/";

#include "libTreater.hpp"

bool isMP3(char file[]){
    unsigned size=strlen(file);
    if (strlen(file)>3)
        return ((file[size-4]=='.') && (file[size-3]=='m') && (file[size-2]=='p') && (file[size-1]=='3'));
    else
        return false;
}

std::vector<std::string> getNames(std::string filename){
    DIR* dir;
    struct dirent* entry;
    std::vector<std::string> res;
    dir=opendir(filename.c_str());
    if(dir==NULL)
        std::cout << "File not found " << std::endl;
    while((entry=readdir(dir))!= NULL){
        if(isMP3(entry->d_name)){
            res.push_back(filename+std::string(entry->d_name));
        }
    }
    std::sort(res.begin(),res.end());
    closedir(dir);
    return res;
}

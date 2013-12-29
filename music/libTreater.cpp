#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>

#define MUSIC_LIB "./music/"

bool isMP3(char file[]){
	unsigned size=strlen(file);
	return ((file[size-4]=='.') && (file[size-3]=='m') && (file[size-2]=='p') && (file[size-1]=='3'));
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
			res.push_back(MUSIC_LIB+std::string(entry->d_name));
		}
	}
	closedir(dir);
	return res;
}

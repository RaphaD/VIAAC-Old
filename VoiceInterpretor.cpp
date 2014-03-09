#include "VoiceInterpretor.hpp"

VoiceInterpretor::VoiceInterpretor() 
{
#ifdef __VERBOSE
    std::cout << "VIAAC AppHandler initialized" << std::endl;
#endif
}

int VoiceInterpretor::mainLoop(){
#ifdef __VERBOSE
    std::cout << "VIAAC Creation of pipes" << std::endl;
#endif
    int mPere_mFils[2];
    if(pipe(mPere_mFils)==-1){
        throw("[Error] Creation of music pipe..");
        return 1;
    }

    FILE *fp;
    int status;
    char path[PATH_MAX];
    char* res;

    while(true){
        fp = popen("./voiceRecon.sh", "r");
        if (fp == NULL){
            throw("[Error] Creating listener process..");
            return 1;
        }
        while (fgets(path, PATH_MAX, fp) != NULL){
            printf("%s", path);
            if(path[0]=='*' && path[1]=='*' && path[2]=='*'){
                res=path;
            }
        }
        status = pclose(fp);
        if (status == -1) {
            throw("[Error] Closing listener process..");
            return 1;
        }else if(status==0){
            std::cout << "\n Command not found \n" << std::endl;
        }else{
            std::cout << "========== VIAAC ==========" << std::endl;
            std::cout << "res is " << res << std::endl;
        }
    }
    return 0;
}

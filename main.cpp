#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

#include "VoiceInterpretor.hpp"
#include "CommandInterpretor.hpp"
#include "AppHandler.hpp"

//#define __VERBOSE
#define T_COMMAND "commands.xml"

int main(int argc,char* argv[])
{
#ifdef __VERBOSE
	std::cout << "========== BEGIN OF VIAAC ==========" << std::endl;
#endif
/*	try{
		if(argc!=2){
			throw("[Error] No option given (-v for voice command, -t for terminal command)");
			return 1;
		}else{

			if(strcmp(argv[1],"-v")==0){
				VoiceInterpretor Voice;
				int toReturn=Voice.mainLoop();
				if(toReturn==1){
					return toReturn;
				}
			}else if(strcmp(argv[1],"-t")==0){
*/				AppHandler* app=new AppHandler();
				CommandInterpretor Command(T_COMMAND,app);
				Command.mainLoop();
/*			}else{
				throw("[Error] Option doesn't exist !");
			}
		}
	}catch(char const* e){
		std::cout << e << std::endl;
	}
*/

#ifdef __VERBOSE
	std::cout << "========== END OF VIAAC ==========" << std::endl;
#endif

	return 0;
}


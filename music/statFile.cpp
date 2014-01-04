#include "statFile.hpp"

#ifdef __STATISTICS

#define STAT_COUNT "STAT_FILE.txt"

void openStat(long double& turn,long unsigned& number_turn){
	std::ifstream fichier(STAT_COUNT,std::ios::in);

	if(fichier){
		std::string contenu;
		std::getline(fichier, contenu);
		turn=std::stoi(contenu);
		getline(fichier, contenu);
		number_turn=std::stoi(contenu);
		std::cout << "turn : " << turn << std::endl;
		std::cout << "number_turn : " << number_turn << std::endl;

		fichier.close();
	}else
		std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
}

void writeStat(long double& turn,long unsigned& number_turn){
	std::ofstream fichier(STAT_COUNT, std::ios::out | std::ios::trunc);

	if(fichier){
		fichier << turn << std::endl;
		fichier << number_turn;

		fichier.close();
	}else
		std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
}
#endif //__STATISTICS

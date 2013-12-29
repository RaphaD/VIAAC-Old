#ifdef __STATISTICS
void openStat(const char* filename){
	std::ifstream fichier(filename,std::ios::in);

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

void writeStat(const char* filename){
	std::ofstream fichier(filename, std::ios::out | std::ios::trunc);

	if(fichier){
		fichier << turn << std::endl;
		fichier << number_turn;

		fichier.close();
	}else
		std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
}
#endif

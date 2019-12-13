#include "ville.hh"

/* si l'arc allant vers m existe, retourne la valeur de celui-ci
retourn 0 sinon */
unsigned int Maison::distanceVers(Maison m){
	for(auto &c :_routes){
		if(m.getCoord()==c){
			//retourne la distance entre la maison
			return(((std::abs(c._x - _coord._x))+(std::abs(c._y - _coord._y))+(std::abs(c._z - _coord._z)))/ 2);
		}
	}
	return 0;
}

void Ville::afficher()const{
	//premiere ligne avec numeros de colonne
	std::cout<<"_";
	for(int i(1);i<=nbSommet();i++){
		std::cout<<"|"<<i;
	}
	std::cout<<std::endl;
	for(int i(1);i<=nbSommet();i++){
		std::cout<<i<<"|";
		for(int j(1);j<=nbSommet();j++){
			std::cout<<getMaison(i).distanceVers(getMaison(j))<<"|";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

#include <iostream>
#include <fstream>
#include "ville.hh"
#include <array>
#include <vector>

Ville initialiserVille(int testNum){
	Ville ville;
	switch(testNum){

		//initialisation pour l'exercice 1
		case(1):{
			//creation de Maisons
			Maison m1(coordonnee(1,2,3));
			Maison m2(coordonnee(3,2,1));
			Maison m3(coordonnee(4,2,3));
			//creation des routes entre les maisons
			m1.ajoutRoute(m2);
			m2.ajoutRoute(m3);
			m3.ajoutRoute(m1);
			//ajout des maisons à la ville
			ville.ajoutMaison(m1);
			ville.ajoutMaison(m2);
			ville.ajoutMaison(m3);
		break;}

		//initialisation pour l'exercice 2
		case(2):{

		break;}

		//initialisation pour l'exercice 3
		case(3):{

		break;}

		//initialisation pour l'exercice 4
		case(4):{

		break;}

		//cas d'erreur
		default: break;
	}
	return ville;
}

void tests(int testNum,Ville &ville){
	//test général
	std::cout<<"test n°"<<testNum<<" sur la matrice suivante:"<<std::endl;
	ville.afficher();

	switch(testNum){

		// tests de l'exo 1
		case(1):{

		break;}

		 // tests de l'exo 2
		case(2):{
		break;}

		 // tests de l'exo 3
		case(3):{
		break;}

		// tests de l'exo 4
	   case(4):{
	   break;}

		//cas d'erreur
		default: std::cout<<"erreur lors de la selection du numero de test"<<std::endl;break;
	}

}
int main(int argc, char** argv){
  	if (argc != 2){
	   	std::cout << "Pas de numero de test entré \n" << std::endl;
	   	std::cout << " UTILISATION SUIVANTE: ./city [n° d'exercice à tester entre 1 et 4]";
	}else{
		int testNum=atoi(argv[1]);
		Ville ville=initialiserVille(testNum);
	  	tests(testNum,ville);
   	}
  	return 0;
}

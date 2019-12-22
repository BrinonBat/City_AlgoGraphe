#include <iostream>
#include <fstream>
#include "ville.hh"
#include <array>
#include <vector>
#include <ctime>
#include <chrono>

Ville initialiserVille(int testNum){
	Ville ville;
	switch(testNum){

		//initialisation pour l'exercice 1
		case(1):{
			//creation de Maisons
			Maison m1(coordonnee(1,-1,0));
			Maison m2(coordonnee(-1,2,-1));
			Maison m3(coordonnee(-2,0,2));
			Maison m4(coordonnee(2,-2,0));
			Maison m5(coordonnee(1,0,-1));
			Maison m6(coordonnee(0, 1, -1));
			//creation des routes entre les maisons
			m1.ajoutRoute(m2);
			m1.ajoutRoute(m4);
			m1.ajoutRoute(m5);
			m2.ajoutRoute(m3);
			m3.ajoutRoute(m1);
			m3.ajoutRoute(m5);
			m5.ajoutRoute(m1);
			m5.ajoutRoute(m6);
			m5.ajoutRoute(m4);
			m4.ajoutRoute(m2);
			m4.ajoutRoute(m6);

			//ajout des maisons à la ville
			ville.ajoutMaison(m1);
			ville.ajoutMaison(m2);
			ville.ajoutMaison(m3);
			ville.ajoutMaison(m4);
			ville.ajoutMaison(m5);
			ville.ajoutMaison(m6);
			break;}

		//initialisation pour l'exercice 2
		case(2):{
			Maison m1(coordonnee(-5, 0, 5));
			Maison m2(coordonnee(0, 0, 0));
			Maison m3(coordonnee(3, 0, -3));
			Maison m4(coordonnee(0, 4, -4));
			Maison m5(coordonnee(-4, 0, 4));
			Maison m6(coordonnee(1, 0, -1));
			Maison m7(coordonnee(6, 0, -6));
			Maison m8(coordonnee(0, 2, -2));

			m1.ajoutRoute(m2);
			m1.ajoutRoute(m8);
			
			m2.ajoutRoute(m7);
			
			m3.ajoutRoute(m2);
			m3.ajoutRoute(m4);
			m3.ajoutRoute(m6);

			m4.ajoutRoute(m6);

			m5.ajoutRoute(m4);

			m6.ajoutRoute(m5);

			m7.ajoutRoute(m6);
			m7.ajoutRoute(m3);

			m8.ajoutRoute(m1);
			m8.ajoutRoute(m7);

			ville.ajoutMaison(m1);
			ville.ajoutMaison(m2);
			ville.ajoutMaison(m3);
			ville.ajoutMaison(m4);
			ville.ajoutMaison(m5);
			ville.ajoutMaison(m6);
			ville.ajoutMaison(m7);
			ville.ajoutMaison(m8);
			break;}

		//initialisation pour l'exercice 3
		case(3):{

		break;}

		//initialisation pour l'exercice 4
		case(4):{

		break;}

		//cas d'erreur
		default: std::cout<<"erreur lors de la selection du numero de test"<<std::endl;break;
	}
	return ville;
}

void tests(int testNum,Ville &ville){
	//test général
	if(testNum>0 && testNum<5){
		std::cout<<"test n°"<<testNum<<" sur la matrice suivante:"<<std::endl;
		ville.afficher();
	}
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
		default: std::cout<<"veuillez selectionnez un numero valide"<<std::endl;break;
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
	Ville ville = initialiserVille(1);
	std::cout<<std::endl;
	ville.afficher();
	ville.courseDijkAetoile(1,2);
	std::cout<<std::endl;
	ville.tarjan();
	ville.kruskal();
	return 0;
}

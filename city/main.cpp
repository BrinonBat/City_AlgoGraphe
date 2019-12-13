#include <iostream>
#include <fstream>
#include "graphe.hpp"
#include "ville.hh"
#include <array>
#include <vector>

int lecture(std::string input, Graphe& G){
  std::ifstream fichier(input);

  if (fichier) {
    unsigned int nbLine = 0;
    std::string ligne;
    while(getline(fichier,ligne)){
      ++nbLine;
      //Si c'est un v on récupère le nombre de sommets et on crée une matrice d'adjacence de cette taille
      if (ligne[0] == 'v') {
        //Parsing des arguments
        unsigned int i=1;
        std::vector<std::string> args;
        while ((i < ligne.length()) and (args.size()<1)) {
          std::string arg = "";
          while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
          while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
          if (arg.length() > 0) args.push_back(arg);
        }
        if (args.size()>1) {
          std::cout << "Too many arguments line " << nbLine << std::endl;
          return 1;
        }
        else {
          int nbSommets;
          try {
           nbSommets = stoi(args[0]);
          }
          catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument : " << ia.what() << " Ligne " << nbLine << std::endl;
            nbSommets = 0;
          }
          G.initMatrice(nbSommets);
        }
      }
      else if (ligne[0] == 'e') {
       //Parsing des arguments
        unsigned int i=1;
        std::vector<std::string> args;
        while ((i < ligne.length()) and (args.size()<3)) {
          std::string arg = "";
          while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
          while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
          if (arg.length() > 0) args.push_back(arg);
        }
        if (args.size()>3) {
          std::cout << "Too many arguments line " << nbLine << std::endl;
          return 1;
        } else if (args.size()<3) {
          std::cout << "Too few arguments line " << nbLine << std::endl;
          return 1;
        }
        else {
          int origine;
          int destination;
          double poids;
          try {
            origine = stoi(args[0]);
            destination = stoi(args[1]);
            poids = stod(args[2]);
          }
          catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument : " << ia.what() << " Ligne " << nbLine << std::endl;
            origine = 0;
            destination = 0;
            poids = -1;
          }
          G.ajoutArc(origine,destination,poids);
        }
      }
      else if (ligne[0] == 'o') {
        unsigned int i=1;
        std::vector<std::string> args;
        while ((i < ligne.length()) and (args.size()<1)) {
          std::string arg = "";
          while ((i < ligne.length()) and (ligne[i]==' ')) ++i;
          while ((i < ligne.length()) and (ligne[i]!=' ')) {arg+=ligne[i]; ++i;}
          if (arg.length() > 0) args.push_back(arg);
        }
        if (args.size()>1) {
          std::cout << "Too many arguments line " << nbLine << std::endl;
          return 1;
        }
        G.setOriente(!args[0].compare("go"));
      }
      else if (ligne[0] != 'c'){
         std::cout << "Ligne " << nbLine << " non reconnue : " << ligne << std::endl;
      }
    }
  }
  else {
    std::cout << "Erreur: impossible d'ouvrir le fichier" << std::endl;
  }
  return 0;
}

int main(int argc, char** argv){
  Graphe G;
  if (argc != 2) std::cout << "Pas de fichier en paramêtre" << std::endl;
  else lecture(argv[1],G);
  G.affichageMatrice();
  G.parcoursProfondeur();
  G.parcoursLargeur();
  G.dijkstra(3);
  return 0;
}

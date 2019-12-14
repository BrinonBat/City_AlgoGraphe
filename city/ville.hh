#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include "graphe.hh"
struct coordonnee
{
    int _x, _y, _z;
    bool operator==(coordonnee const &c) const
    {
        return (_x == c._x) && (_y == c._y) && (_z == c._z);
    }
	//constructeur
	coordonnee(int x,int y,int z):
		_x(x),_y(y),_z(z){}
};

class Maison{
private:
    coordonnee _coord;
    //std::vector<coordonnee> _routes;
	std::vector<Maison> _voisins;
public:
    Maison(coordonnee c) : _coord(c){} // place une maison à la coordonnée c
	~Maison();
	unsigned int distanceVers(Maison m); // retourne la valeur de l'arc (s'il existe) entre la maison et une autre
    coordonnee getCoord() const { return _coord; }
    void setCoord(coordonnee nouv) { _coord = nouv; }
    std::vector<Maison> getRoute() const { return _voisins; }
	//void ajoutRoute(Maison m){_routes.push_back(m.getCoord());}
	void ajoutRoute(Maison &m){_voisins.push_back(m);}
	std::vector<Maison> getVoisins()const{return _voisins;}

	//utilisés pour algorithmes
	bool estDans(std::vector<Maison> vect); // retourne vrai si la maison est dans le vecteur
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Ville{
private:
    /*int _rayon;*/
    std::vector<Maison> _maisons;
	Graphe _graphe;

public:
	//constructeurs
    Ville()=default;
	/*Ville(int r):
		_rayon(r);*/
	Ville(const Ville &autre) = default;
    //accesseurs
    /*int getRayon() const { return _rayon; }*/
	void ajoutMaison(Maison const &m){_maisons.push_back(m);}
	Maison getMaison(int n)const{return _maisons[n-1];}
    int nbSommet() const { return _maisons.size(); }
    std::vector<Maison> getMaisons() const { return _maisons; }
	void afficher();

	void exec();
	int indiceMaison(coordonnee c); //retourne l'indice de la maison situé aux coordonée données

	//algorithmes
	int donneIndice(Maison testee, Maison dst); // évalue la distance entre la maison testée et la maison destination
	std::vector<Maison> CCaEtoile(Maison srx,Maison dst); // algorithme A* donnant un court chemin
	
	//fonction pour dijkstra
	double minDistance(std::array<double, Max> dist, std::array<bool, Max> sptSet);
	void printSolution(std::array<double, Max> dist);
	void dijkstra(int src);//algorithme dijkstra
	void Aetoile(int src);
};

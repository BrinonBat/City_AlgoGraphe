#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <memory>
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
	bool operator==(Maison const & m){return _coord==m.getCoord();}

	//utilisés pour algorithmes
	bool estDans(std::vector<Maison> vect); // retourne vrai si la maison est dans le vecteur

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Ville{
private:
    /*int _rayon;*/
    std::vector<Maison> _maisons;

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

	int indiceMaison(coordonnee c); //retourne l'indice de la maison situé aux coordonée données

	//algorithmes
	void courseDijkAetoile(int src,int dst);// affiche le temps d'exécution de dijkstra et a*
	int donneIndice(Maison testee, Maison dst); // évalue la distance entre la maison testée et la maison destination
	
	void dijkstra(int src,int dst);//algorithme dijkstra
	void Atest(int src, int dst);

	void tarjan();
	void raccorder(std::vector<std::pair<int,int> > noeuds);// raccorde les différente parties d'une ville
	void parcours(int i, int &num, int &nbscc, std::vector<std::pair<int, int>> &noeuds, std::vector<bool> &estdanspile, std::vector<int> &pile);

	void kruskal();
};
	// struct pour dijkstra et A*
	struct noeud
	{
		Maison m;
		// distance parcourue
		int cout;
		// distance parcourue plus distance de l'arrivé
		int heuristique;
		std::pair<int,int> pred;
		noeud(Maison ma, int c, int h) : m(ma), cout(c), heuristique(h) {}
		noeud(Maison ma, int c, int h, std::pair<int, int> p) : m(ma), cout(c), heuristique(h),pred(p)
		{
		}

		bool operator==(noeud const &n)
		{
			return (m.getCoord() == n.m.getCoord()) && (cout == n.cout) && (heuristique == n.heuristique);
		}
		bool operator<(noeud const &n1)
		{
			return heuristique > n1.heuristique;
		}
};

std::ostream & operator<<(std::ostream &os,coordonnee c);
#include "ville.hh"
#include <limits>
#include <array>
#include <iostream>
#include <limits>
/* si l'arc allant vers m existe, retourne la valeur de celui-ci
retourn 0 sinon */
unsigned int Maison::distanceVers(Maison m){
/*	for(auto &c :_routes){
		if(m.getCoord()==c){
			//retourne la distance entre la maison
			return((std::abs(c._x - _coord._x))+(std::abs(c._y - _coord._y))+(std::abs(c._z - _coord._z)));
		}
	}*/
	for(auto &v : _voisins){
		if(v.getCoord()==m.getCoord())return((std::abs(m.getCoord()._x - _coord._x))+(std::abs(m.getCoord()._y - _coord._y))+(std::abs(m.getCoord()._z - _coord._z)));
	}
	return std::numeric_limits<int>::max(); // valeure maximale pouvant etre attribuée à un int
}
Maison::~Maison(){

}
void Ville::afficher(){
	_graphe.affichageMatrice();
}

////////////////////////////////////////////ALGORITHMES///////////////////////////////////////////////////////////////////////////////////////////////////
//estime la distance entre la Maison testée et la destination
int Ville::donneIndice(Maison testee, Maison dst){
	return(
			 (std::abs(testee.getCoord()._x - dst.getCoord()._x))
			+(std::abs(testee.getCoord()._y - dst.getCoord()._y))
			+(std::abs(testee.getCoord()._z - dst.getCoord()._z))
		);
}
bool Maison::estDans(std::vector<Maison> vect){
	for( auto &m : vect){
		if(m.getCoord()==_coord) return true;
	}
	return false;
}
std::vector<Maison> Ville::CCaEtoile(Maison src,Maison dst){
	std::vector<Maison> result;
	result.push_back(src);
	std::vector<Maison> path;
	path.push_back(src);
	for(auto v : src.getVoisins()){

	}

	return result;
}
int Ville::indiceMaison(coordonnee c)
{
	for (int i = 0; i < (int)_maisons.size(); i++)
	{
		if (_maisons[i].getCoord() == c)
		{
			return i;
		}
	}
	return -1;
}

void Ville::exec(){
		_graphe.setNbSommets((int)_maisons.size());
		_graphe.initMatrice();
		for (auto const &i : _maisons)
		{
			for (auto const j : i.getRoute())
			{
				_graphe.ajoutArc(indiceMaison(i.getCoord()),indiceMaison(j.getCoord()),(double) donneIndice(i, j));
			}
		}
}

// DIJKSTRA -----------------------------------------------------------

void Ville::dijkstra(int src){
	_graphe.dijkstra(src);
}
#pragma once
#include <iostream>
#include <vector>

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
    std::vector<coordonnee> _routes;
public:
    Maison(coordonnee c) : _coord(c){} // place une maison à la coordonnée c

	unsigned int distanceVers(Maison m); // retourne la valeur de l'arc (s'il existe) entre la maison et une autre
    coordonnee getCoord() const { return _coord; }
    void setCoord(coordonnee nouv) { _coord = nouv; }
    std::vector<coordonnee> getRoute() const { return _routes; }
	void ajoutRoute(Maison m){_routes.push_back(m.getCoord());}
};

class Ville{
private:
    int _rayon;
    std::vector<Maison> _maisons;

public:
    Ville()=default;
    Ville(const Ville &autre) = default;
    //accesseurs
    int getRayon() const { return _rayon; }
	void ajoutMaison(Maison const &m){_maisons.push_back(m);}
	Maison getMaison(int n)const{return _maisons[n-1];}
    int nbSommet() const { return _maisons.size(); }
    std::vector<Maison> getMaisons() const { return _maisons; }
	void afficher()const;
};

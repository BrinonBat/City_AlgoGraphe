#pragma once
#include "graphe.hpp"
#include <iostream>
#include <vector>

struct coordonnee
{
    int _x, _y, _z;
    bool operator==(coordonnee const &c) const
    {
        return (_x == c._x) && (_y == c._y) && (_z == c._z);
    }
};
class Maison{
private:
    coordonnee _coord;
    std::vector<coordonnee> _routes;
public:
    Maison(coordonnee c) : _coord(c), {}
    Maison(int r); //r est le rayon du graphe

    coordonnee getCoord() const { return _coord; }
    void setCoord(coordonnee nouv) { _coord = nouv; }
    std::vector<coordonnee> getRoute() const { return _routes; }
};
class Ville{
private:
    Graphe _graphe;
    int _rayon;
    int _nbsommet;
    bool _estConstruit; //retourne true si la ville est construite
    std::vector<Maison> _maisons;

public:
    instruction() : _nbsommet(0), _estConstruit(false){};
    instruction(const instruction &autre) = default;
    //accesseurs
    Graphe getGraphe() const { return _graphe; }
    int getRayon() const { return _rayon; }
    int getNbsommet() const { return _nbsommet; }
    std::vector<Maison> getMaisons() const { return _maisons; }
};
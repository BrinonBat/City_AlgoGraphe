#pragma once
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <array>
#include <limits>
const int Max = 1000;


class Graphe
{
private:
    
    std::array<std::array<double, Max>, Max> matrice;
    std::array<bool, Max> parcourus;
    int nbSommets;
    bool oriente;

public:
    Graphe();
    ~Graphe();
    void initMatrice();
    int getNbSommets() { return nbSommets; }
    void setNbSommets(int i) { nbSommets=i; }
    void setOriente(bool o) { oriente = o; };
    void ajoutArc(int, int, double);
    void affichageMatrice();
    void parcoursProfondeur();
    void explorer(int s);
    void parcoursLargeur();
    void dijkstra(int src);
    double minDistance(std::array<double, Max> dist, std::array<bool, Max> sptSet);
    void printSolution(std::array<double, Max> dist);
    void fordfulkerson(int deb, int fin);
};

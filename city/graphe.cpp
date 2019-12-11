#include "graphe.hpp"
#include <sstream>
#include <iostream>
#include <queue>

Graphe::Graphe(): nbSommets(0), oriente(false){
}

Graphe::~Graphe(){
  
}

void Graphe::initMatrice(int nbS){
  nbSommets = nbS;
  for (int i=0; i<nbSommets; ++i){
    for (int j=0; j<nbSommets; ++j){
      matrice[i][j]=std::numeric_limits<double>::infinity();
    }
  }
  std::cout << "Graphe initialisé " <<std::endl;
}

void Graphe::ajoutArc(int origine,int destination, double poids){
  if (!oriente) matrice[destination-1][origine-1] = poids;
  matrice[origine-1][destination-1] = poids;
}

void Graphe::affichageMatrice(){
  std::vector<int> largeurColonne;
  for (int i=0; i<nbSommets; ++i){    
    int max=0;
    for (int j=0; j<nbSommets; ++j){
      std::ostringstream tmp;
      tmp << matrice[j][i];
      if (tmp.tellp() > max) {max=tmp.tellp();}   
    }
    largeurColonne.push_back(max);
  }
  std::cout << "    ";
  for (int i=0; i<nbSommets; ++i)
    printf("%*d ",largeurColonne[i],i+1); 
  std::cout << std::endl; 
  for (int i=0; i<nbSommets; ++i){
    printf("%3d|",i+1);
    for (int j=0; j<nbSommets; ++j){
      printf("%*.*g ",largeurColonne[j],largeurColonne[j],matrice[i][j]);   
    }
    std::cout << std::endl;
  }  
}

void Graphe::parcoursProfondeur(){
  for (int i=0; i<nbSommets; ++i){
    parcourus[i]=false;
  } 
  for (int i=0; i<nbSommets; ++i){
    if (!parcourus[i]) explorer(i);
  }
  std::cout << std::endl;
}

void Graphe::explorer(int s){
  parcourus[s]=true;
  std::cout << "S" << s+1 << " ";
  for (int i=0;i<nbSommets;++i) {
    if (!parcourus[i] and (matrice[s][i]!=std::numeric_limits<double>::infinity()))
      explorer(i);
  }   
}

void Graphe::parcoursLargeur(){
  for (int i=0; i<nbSommets; ++i){
    parcourus[i]=false;
  }  
  std::queue<int> file;
  file.push(0);
  parcourus[0]=true;
  while(!file.empty()){
    int s = file.front();
    std::cout << "S" << s+1 << " ";
    file.pop();
    for (int i = 0;i<nbSommets;++i){
      if (!parcourus[i] and (matrice[s][i]!=std::numeric_limits<double>::infinity())){
        file.push(i);
        parcourus[i]=true;
      }
    }
  }
  std::cout << std::endl;
}
double Graphe::minDistance(std::array<double, Max> dist, std::array<bool, Max> sptSet)
{
  double min = std::numeric_limits<double>::infinity();
  int min_index;
  for(int v=0;v<nbSommets;v++){
    if(sptSet[v]==false && dist[v]<=min)
      min = dist[v],min_index=v;
  }
  return min_index;
}
void Graphe::printSolution(std::array<double, Max> dist)
{
  std::cout<<"Sommet \t\t distance depuis source"<<std::endl;
  for(int i = 0;i<nbSommets;i++){
    std::cout<<std::to_string(i+1)+"\t\t"+std::to_string(dist[i])<<std::endl;
    //printf("%d \t\t %f\n",i,dist[i]);
  }
}
void Graphe::dijkstra(int src){
  //double dist[nbSommets];
  std::array<double,Max> dist;
  std::array<bool,Max> sptSet;
  //bool sptSet[nbSommets];
  for(int i=0;i<nbSommets;i++){
    dist[i] = std::numeric_limits<double>::infinity(), sptSet[i] = false;
  }

  dist[src-1]=0;
  for(int count=0;count<nbSommets-1;count++){
    int u=minDistance(dist,sptSet);
    sptSet[u]=true;
    for(int v =0;v<nbSommets;v++){
      //std::cout << "sptSet: " << sptSet[v]<< " matrice u v : " + std::to_string(u) + " " + std::to_string(v) + " dist u: " + std::to_string(dist[u]) + " dist u + matrice u v : " + std::to_string(dist[u] + matrice[u][v])<<std::endl;
       if (!sptSet[v] && matrice[u][v] && dist[u] != std::numeric_limits<double>::infinity() && dist[u] + matrice[u][v] < dist[v])
      {
        dist[v] = dist[u] + matrice[u][v];
      }
    }
  }
  printSolution(dist);
}

#include "ville.hh"
#include <limits>
#include <array>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>
#include <chrono>
#include <stdio.h>
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
	std::cout<<"  ";
	for(int i=0;i<(int)_maisons.size();i++){
		printf("%*d", 3, i+1);
	}
	std::cout<<std::endl;
	for (int i = 0; i < (int)_maisons.size(); i++)
	{
		std::cout <<i+1<< "|";
		for (int j = 0; j < (int)_maisons.size(); j++)
		{
			if(_maisons[j].estDans(_maisons[i].getRoute())){
				printf("%*d",3,donneIndice(_maisons[i],_maisons[j]));
			}else{
				printf("%*s", 3,"0");
			}
			
		}
		std::cout << std::endl;
	}
	
}

////////////////////////////////////////////ALGORITHMES///////////////////////////////////////////////////////////////////////////////////////////////////
//estime la distance entre la Maison testée et la destination
int Ville::donneIndice(Maison testee, Maison dst){
	return(std::max(std::abs(testee.getCoord()._x - dst.getCoord()._x)
		,std::max(std::abs(testee.getCoord()._y - dst.getCoord()._y)
		,std::abs(testee.getCoord()._z - dst.getCoord()._z))));
			 
}
bool Maison::estDans(std::vector<Maison> vect){
	for( auto &m : vect){
		if(m.getCoord()==_coord) return true;
	}
	return false;
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

// // -------------------------------------------------- DIJKSTRA A* ---------------------------------------------------------------------------------
void Ville::courseDijkAetoile(int src, int dst)
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	dijkstra(src, dst);
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	auto secd = sec.count();

	start = std::chrono::system_clock::now();
	Atest(src, dst);
	sec = std::chrono::system_clock::now() - start;
	std::cout << "temps dijkstra : \t" << secd << std::endl;
	std::cout << "temps aetoile : \t" << sec.count() << std::endl;
		
	
}



//retourne vrai si le noeud est dans la liste 
bool existeliste(noeud n, std::vector<noeud> closedlist)
{
	for(auto &i:closedlist){
		if(i.m.getCoord()==n.m.getCoord()){
			return true;
		}
	}
	return false;
}
int coutliste(noeud n, std::vector<noeud> openlist){

	for (auto &i : openlist)
	{
		if (i.m.getCoord() == n.m.getCoord())
		{
			return i.cout;
		}
	}
	return -1;
}

void Ville::dijkstra(int src, int dst)
{
	std::cout << "------------------------------------------ Début Dijktra ------------------------------------" << std::endl;
	noeud depart(_maisons[src - 1], 0, 0,std::make_pair(0,0));
	noeud arrive(_maisons[dst - 1], 0, 0);
	std::vector<noeud> closedlist;
	std::vector<noeud> openlist;

	openlist.push_back(depart);
	while (!openlist.empty())
	{

		auto u = openlist.back();
		openlist.pop_back();
		std::cout << "---Noeud courant " << indiceMaison(u.m.getCoord()) + 1 << " - " << u.m.getCoord() << std::endl;
		if (u.m == arrive.m)
		{
			std::cout << "-----------------------------------------------------> La distance de " << src << " à " << dst << " selon dijkstra est de " << u.heuristique << std::endl;
			auto it = u;
			std::cout<<"Chemin : ";
			while(indiceMaison(it.m.getCoord())!=src-1){
				std::cout<<indiceMaison(it.m.getCoord())+1<<"<-";
				for(auto & preced : closedlist){
					if(indiceMaison(preced.m.getCoord())==it.pred.first&& preced.pred.first==it.pred.second){
						it=preced;
					}
				}
			}
			std::cout << indiceMaison(it.m.getCoord())+1;
			break;
		}
		if (_maisons[indiceMaison(u.m.getCoord())].getRoute().size() == 0)
		{
			std::cout << "Ce noeud n'a pas de voisin retour arrière" << std::endl;
		}
		for (auto &i : _maisons[indiceMaison(u.m.getCoord())].getVoisins())
		{
			
			noeud v(i,  donneIndice(i, u.m)+u.cout , donneIndice(i, _maisons[dst - 1]),std::make_pair(indiceMaison(u.m.getCoord()),u.pred.first));
			std::cout << "\t Distance entre " << u.m.getCoord() << " et " << indiceMaison(i.getCoord()) + 1 << " - " << i.getCoord() << " est " << donneIndice(i, u.m) << " Distance parcourue : " << v.cout + u.cout << std::endl;
			if (existeliste(v, closedlist) || (existeliste(v, openlist) && v.cout >= coutliste(v, openlist)))
			{
				if ( (existeliste(v, openlist) && v.cout >= coutliste(v, openlist))){
					std::cout << "\t Le sommet " << indiceMaison(i.getCoord()) + 1 << " - " << i.getCoord() << " a déjà un chemin plus court ou égal" << std::endl;
				}else{
					std::cout << "\t Le sommet " << indiceMaison(i.getCoord()) + 1 << " - " << i.getCoord() << " a déjà été parcourue" << std::endl;
				}
			}
			else
			{
				v.cout = u.cout + donneIndice(u.m, v.m);
				v.heuristique = v.cout ;
				std::cout << "\t" << indiceMaison(v.m.getCoord()) + 1 << " - " << v.m.getCoord() << " - cout: " << v.cout << " - heur: " << v.heuristique << " - dist arrive: " << donneIndice(v.m, arrive.m) << std::endl;
				openlist.push_back(v);
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
		closedlist.push_back(u);
		std::sort(openlist.begin(), openlist.end());
		std::cout << "   Noeuds possible";
		for (auto &k : openlist)
		{
			std::cout << " ||| " << indiceMaison(k.m.getCoord()) + 1 << " pred:"<< (k.pred.first +1) << k.m.getCoord() << " Distance parcourue : " << k.heuristique;
		}
		std::cout << std::endl;
		std::cout << "   " << indiceMaison(openlist.back().m.getCoord()) + 1 << " - " << (openlist.back().m.getCoord()) << " a été choisi car il est le plus proche de notre destination" << std::endl;
		std::cout << std::endl;
	}
	std::cout << "\nSommets parcourus : ";
	for (auto &i : closedlist)
	{
		std::cout << indiceMaison(i.m.getCoord()) + 1 << "->";
	}
	std::cout << dst << std::endl;
}


std::ostream & operator <<(std::ostream &os,coordonnee c){
	os<<"("<<c._x<<","<<c._y<<","<<c._z<<")";
	return os;
}
void Ville::Atest(int src, int dst)
{
	std::cout << "------------------------------------------ Début A* ------------------------------------" << std::endl;
	noeud depart(_maisons[src - 1], 0, 0, std::make_pair(0, 0));
	noeud arrive(_maisons[dst - 1], 0, 0);
	std::vector<noeud> closedlist;
	std::vector<noeud> openlist;

	openlist.push_back(depart);
	while (!openlist.empty())
	{
		
		auto u = openlist.back();
		openlist.pop_back();
		std::cout << "---Noeud courant " << indiceMaison(u.m.getCoord()) + 1 << " - " << u.m.getCoord() << std::endl;
		if (u.m == arrive.m)
		{
			std::cout << "-----------------------------------------------------> La distance de " << src << " à " << dst << " selon A* est de " << u.heuristique << std::endl;
			auto it = u;
			std::cout << "Chemin : ";
			while (indiceMaison(it.m.getCoord()) != src - 1)
			{
				std::cout << indiceMaison(it.m.getCoord()) + 1 << "<-";
				for (auto &preced : closedlist)
				{
					if (indiceMaison(preced.m.getCoord()) == it.pred.first && preced.pred.first == it.pred.second)
					{
						it = preced;
					}
				}
			}
			std::cout << indiceMaison(it.m.getCoord()) + 1;
			break;
		}
		if (_maisons[indiceMaison(u.m.getCoord())].getRoute().size()==0){
			std::cout<<"Ce noeud n'a pas de voisin retour arrière"<<std::endl;
		}
			for (auto &i : _maisons[indiceMaison(u.m.getCoord())].getVoisins())
			{
				noeud v(i, donneIndice(i, u.m) + u.cout, donneIndice(i, _maisons[dst - 1]), std::make_pair(indiceMaison(u.m.getCoord()), u.pred.first));
				std::cout << "\t Distance entre " << u.m.getCoord() << " et " << indiceMaison(i.getCoord()) + 1 << " - " << i.getCoord() << " est " << donneIndice(i, u.m) << " Distance parcourue : " << u.cout+v.cout << std::endl;
				
				if (existeliste(v, closedlist) || (existeliste(v,openlist) && v.cout >= coutliste(v,openlist)))
				{
					if ((existeliste(v, openlist) && v.cout >= coutliste(v, openlist)))
					{
						std::cout << "\t Le sommet " << indiceMaison(i.getCoord()) + 1 << " - " << i.getCoord() << " a déjà un chemin plus court ou égal" << std::endl;
					}
					else
					{
						std::cout << "\t Le sommet " << indiceMaison(i.getCoord()) + 1 << " - " << i.getCoord() << " a déjà été parcourue" << std::endl;
					}
				}
				else
				{
					
					v.cout = u.cout + donneIndice(u.m, v.m);
					v.heuristique = v.cout + donneIndice(v.m, arrive.m);
					std::cout << "\t" << indiceMaison(v.m.getCoord()) + 1 << " - " << v.m.getCoord() << " - cout: " << v.cout << " - heur: " << v.heuristique << " - dist arrive: " << donneIndice(v.m, arrive.m) << std::endl;
					openlist.push_back(v);
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
			closedlist.push_back(u);
			std::sort(openlist.begin(), openlist.end());
			std::cout << "   Noeuds possible";
			for (auto &k : openlist)
			{
				std::cout << " ||| " << indiceMaison(k.m.getCoord()) + 1 << " " << k.m.getCoord() << " Distance parcourue + distance de l'arrivé: " << k.heuristique;
		}
		std::cout<<std::endl;
		std::cout<<"   "<<indiceMaison(openlist.back().m.getCoord())+1<<" - "<<(openlist.back().m.getCoord())<<" a été choisi car il est le plus proche de notre destination"<<std::endl;
		std::cout<<std::endl;
	}
	std::cout<<"\nSommets parcourus : ";
	for(auto & i : closedlist){
		std::cout<<indiceMaison(i.m.getCoord())+1<<"->";
	}
	std::cout<<dst<<std::endl;
}


// -------------------------------------------------- TARJAN ---------------------------------------------------------------------------------

void Ville::parcours(int i,int &num,int &nbscc, std::vector<std::pair<int, int>> &noeuds, std::vector<bool>& estdanspile, std::vector<int> &pile){
	pile.push_back(i);
	estdanspile[i] = true;
	noeuds[i].first=  num++;
	std::cout<<"Noeud courant : "<<i+1<<std::endl;
	noeuds[i].second = noeuds[i].first;
	std::cout << "\tPile : ";
	for (auto it : pile)
	{
		std::cout << it + 1 << " - ";
	}
	std::cout << std::endl;
	for(auto j : _maisons[i].getRoute()){
		if(noeuds[indiceMaison(j.getCoord())].first==-1){
			parcours(indiceMaison(j.getCoord()), num,nbscc, noeuds, estdanspile, pile);
			noeuds[i].second = std::min(noeuds[i].second, noeuds[indiceMaison(j.getCoord())].second);
		}else if (estdanspile[indiceMaison(j.getCoord())]){
			noeuds[i].second = std::min(noeuds[i].second, noeuds[indiceMaison(j.getCoord())].first);
		}
	}

	if(noeuds[i].first==noeuds[i].second){// si i est une racine, on calcule la composante fortement connexe associé
		std::cout<<"Racine : "<<i+1<<std::endl;
		std::cout << "On dépile : ";
		while(!pile.empty()){
			auto node = pile.back();
			std::cout << node + 1<<" " ;
			pile.pop_back();
			estdanspile[node] = false;
			noeuds[node].second=noeuds[i].first;
			if(node ==i) break;
		}
		std::cout<<std::endl;
		nbscc++;
	}
}
bool estraccorde(int p1, int p2, std::vector<std::pair<int, int>> parties, std::vector<std::pair<int, int>> noeuds)
{
	for(auto & i: parties){
		// si il existe déjà un arc entre partie p1 et p2 renvoie true
		if ((noeuds[i.first].second == noeuds[p1].second && noeuds[i.second].second == noeuds[p2].second) || (noeuds[i.first].second == noeuds[p2].second && noeuds[i.second].second == noeuds[p1].second)){
			return true;
		}
	}
	return false;
}
void Ville::raccorder(std::vector<std::pair<int,int> > noeuds){// raccorde les différente parties d'une ville
	std::vector<std::pair<int,int> > parties;// first -> sommet parti 1 second-> sommet partie 2
	for(int i=0;i<nbSommet();i++){
		for(auto & it :_maisons[i].getVoisins()){
			// si c'est un arc qui relie 2 parties différente et qu'il n'existe pas déjà d'arc enrengistré entre ces 2 parties
			if (noeuds[indiceMaison(it.getCoord())].second != noeuds[i].second && !estraccorde(indiceMaison(it.getCoord()), noeuds[i].second,parties,noeuds))
			{
				parties.push_back(std::make_pair(i, indiceMaison(it.getCoord())));
			}
		}
	}
	for(auto & i : parties){//ajoute un arc inverse
		std::cout<<"Ajout arc de "<<i.second+1<< " à "<<i.first+1<<std::endl;
		_maisons[i.second].ajoutRoute(_maisons[i.first]);
	}
	std::cout<<std::endl;
}
void Ville::tarjan(){
	std::cout <<"-------------------------------------- Tarjan --------------------------------"<< std::endl;
	//index i dans le vecteur représente le noeud i
	int pasvisite = -1;
	int num=0;
	int nbscc=0;
	std::vector<std::pair<int,int> > noeuds;
	std::vector<bool> estdanspile;
	std::vector<int> pile;
	for(int i=0;i<nbSommet();i++){//initialisation a 0
		//valeur du premier est la numérotation du sommet, 
		// la valeur du second est la numérotation du sommet le plus petit dans le cycle
		noeuds.push_back(std::make_pair(pasvisite,0));
		estdanspile.push_back(false);
	}
	for(int i=0;i<nbSommet();i++){
		if(noeuds[i].first==pasvisite){
			//parcours récursif
			parcours(i,num,nbscc,noeuds,estdanspile,pile);
		}
	}
	std::cout<<"Nombre de partie connexes : "<<nbscc<<std::endl;
	for (int i = 0; i < nbSommet(); i++)
	{
		std::cout<<"Sommet :"<<i+1<<" num:"<<noeuds[i].first<<" rattaché à num:"<<noeuds[i].second<<std::endl;
	}
	if (nbscc > 1)
	{
		std::cout << "Voulez-vous raccorder les parties de la ville entre elles?(y/n) " << std::endl;
		char raccordez;
		std::cin >> raccordez;
		if (raccordez == 'y')
		{
			raccorder(noeuds);
			afficher();
			tarjan();
		}
	}
}
// -------------------------------------------------- KRUSKAL ---------------------------------------------------------------------------------
bool recherchekruskal(int s1,int s2,std::vector<std::pair<int,std::pair<int,int> > > arcs){
	for (auto &it : arcs)
	{
		if((it.second.first==s1 && it.second.second==s2 ) || (it.second.first==s2 && it.second.second==s1)){
			return true;
		}
	}
	return false;
}

int findroot(int i, int * parent){
	//si i est son propre parent
	if(i==parent[i]){
		return i;
	}else{
		//sinon si i n'est pas son propre parent, alors i n'est pas représentatif de
		// son arbre, donc on appel findroot sur son parent
		return findroot(parent[i],parent);
	}
}

void Ville::kruskal(){
	std::cout <<"---------------------------------- Kruskal --------------------------------"<< std::endl;
	std::vector<std::pair<int,std::pair<int,int> > > arcs;
	std::vector<std::pair<int, std::pair<int, int>>> spanningtree;
	int *parent=new int[nbSommet()];

	for(int i=0; i<nbSommet();i++){
		parent[i]=i;
	}

	// on récupère tous les arcs du graphe
	for(auto & at : _maisons){
		for(auto & to : at.getVoisins()){
			if (!recherchekruskal(indiceMaison(at.getCoord()), indiceMaison(to.getCoord()),arcs)){
				arcs.push_back(std::make_pair(donneIndice(at,to),std::make_pair(indiceMaison(at.getCoord()),indiceMaison(to.getCoord()))));
			}
		}
	}
	// on trie par ordre croissant de poids
	std::sort(arcs.begin(),arcs.end());
	std::cout<<"Liste des arcs par ordre croissant"<<std::endl;
	for (auto &i : arcs){
		std::cout << i.first << ":" << i.second.first + 1 << "-" << i.second.second + 1 << "  ";
	}
	std::cout<<std::endl;
	int uRep,vRep;
	for(int i=0; i < (int)arcs.size();i++){
		std::cout<<"Etape "<<i+1<<" :"<<std::endl;
		std::cout<<"Arc courant : "<<arcs[i].second.first+1<<" - "<<arcs[i].second.second+1<<std::endl;
		uRep= findroot(arcs[i].second.first,parent);
		vRep=findroot(arcs[i].second.second,parent);
		std::cout << " Racine de " << arcs[i].second.first +1<< " est : " << uRep+1 << " Racine de " << arcs[i].second.second+1 << " est : " << vRep+1 << std::endl;
		if(uRep!=vRep){
			std::cout << " On ajoute à l'arbre de poids minimal l'arc " << arcs[i].second.first+1 << " - " << arcs[i].second.second+1<<std::endl;
			spanningtree.push_back(arcs[i]);// on ajoute à l'arbre de poids minimal
			parent[uRep]=parent[vRep];// le parent du sommet vrep devient celui de urep aussi
		}else{
			std::cout<<" Les deux sommets sont déjà dans l'arbre, on ne fait rien"<<std::endl;
		}
		std::cout << std::endl;
		std::cout<<"Arbre -> ";
		for (auto &i : spanningtree)
		{
			std::cout << i.first << ":" << i.second.first + 1 << " - " << i.second.second + 1 <<" | ";
		}
		std::cout<<"\n"<<std::endl;
	}

	
	std::cout<<"\nArbre de poids minimum"<<std::endl;
	std::cout << "Poids :\tArc" << std::endl;
	int poids=0;
	for (auto &i : spanningtree)
	{
		std::cout << i.first << "     : " << i.second.first + 1 << " - " << i.second.second + 1 << std::endl;
		poids+=i.first;
	}
	std::cout<<"Poids : "<<poids<<std::endl;
}
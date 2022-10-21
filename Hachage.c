#include "Hachage.h"

//FONCTION DE LIBERATION D'UN TABLEAU D'HACHAGE
void free_Hachage(TableHachage* T){
	for(int i = 0 ; i < T->taille ; i++){
		liberer_cellNoeud(T->tab[i]);
	}
	free(T);
}


//QUESTION 4.2
int fonction_cle(double x, double y){
  //Fonction qui calcule la clef d'une table de hachage avec gestion par collision
  return y+(x+y)*(x+y+1)/2;
}


//QUESTION 4.3
int fonction_hachage(int k,int m){
  //Fonction de hachage qui permet de déterminer la case du tableau pour toute clef k
  return m*(k*((sqrt(5)-1)/2)-((int)(k*(sqrt(5)-1)/2)));
}


//QUESTION 4.4
Noeud* rechercheCreeNoeudHachage(Reseau* R,TableHachage* H, double x, double y){
  //Fonction qui retourne un Noeud du reseau R correspondant au point (x, y) dans la table de hachage H
  if(!H || !R){
    printf("Table de hachage vide ou Reseau vide \n");
    return NULL;
  }
  int ind = fonction_hachage(fonction_cle(x,y), H->taille);
  CellNoeud* tab1=(H->tab)[ind];
  //Test de l'appartenance d'un point dans la table de hachage
  while(tab1 != NULL && ((tab1->nd->x != x) && (tab1->nd->y != y))){
		tab1 = tab1->suiv;
  }
  if(tab1 != NULL){
		return tab1->nd;
  }
  //On crée le noeud à ajouter
  Noeud* res=(Noeud*)malloc(sizeof(Noeud));
  res->x=x;
  res->y=y;
  res->num=R->nbNoeuds+1;
  R->nbNoeuds=R->nbNoeuds+1;
  res->voisins=NULL;
  CellNoeud* newCn=(CellNoeud*)malloc(sizeof(CellNoeud));
  newCn->nd=res;
  //Recherche du noeud dans la table de hachage
  newCn->suiv=H->tab[ind];
  H->tab[ind]=newCn;
  //On ajoute le cellnoeud au réseau
  CellNoeud* Cr=(CellNoeud*)malloc(sizeof(CellNoeud));
  Cr->nd=res;
  Cr->suiv=R->noeuds;
  R->noeuds=Cr;
  return res;
}


//QUESTION 4.5
Reseau* reconstitueReseauHachage(Chaines *C, int M){
  //Fonction qui reconstruit le reseau R a partir de la liste des chaınes C et en utilisant une table de hachage H de taille M.
  if(C==NULL){
    printf("Chaine vide \n");
    return NULL;
  }
  //On crée le réseau R
  Reseau* R = (Reseau*)malloc(sizeof(Reseau));
  R->nbNoeuds=0;
  R->gamma=C->gamma;
  R->commodites=NULL;
  R->noeuds=NULL;
  //On crée la table de Hachage
  TableHachage *H = (TableHachage*)malloc(sizeof(TableHachage));
  H->tab=(CellNoeud**)malloc(sizeof(CellNoeud*)*M);
  for(int i=0; i<M ;i++){
	H->tab[i]=NULL;
  }
  H->taille=M;
  CellChaine* cellchaine = C->chaines;
  Noeud* temp=NULL;
  //On parcourt les cellchaines de la chaine C
  while (cellchaine){
    //On initialise la première extrémité d'une commoditée
	CellPoint* cellpoint=cellchaine->points;
	CellCommodite* commod=(CellCommodite*)malloc(sizeof(CellCommodite));
   	temp=rechercheCreeNoeudHachage(R,H, cellpoint->x, cellpoint->y);
	commod->extrA=rechercheCreeNoeudHachage(R,H, cellpoint->x, cellpoint->y);;
	cellpoint=cellpoint->suiv;
    while (cellpoint){
       	//On parcourt tous les points d'une cellchaine
      	Noeud* n1=rechercheCreeNoeudHachage(R,H, cellpoint->x, cellpoint->y);
  	  	CellNoeud* temp1=(CellNoeud*)malloc(sizeof(CellNoeud));
        CellNoeud* temp2=(CellNoeud*)malloc(sizeof(CellNoeud));
        temp1->nd=n1;
        temp2->nd=temp;
	  	CellNoeud* v1=n1->voisins;
        int g=0;
        //Gestion du cas où le voisin est déjà présent
        while(v1){
        	if(v1->nd==temp){
            	g=1;
            }
        	v1=v1->suiv;
        }
        //On gère le cas des voisins
        if(g==0){
        	temp2->suiv=n1->voisins;
        	n1->voisins=temp2;
        	temp1->suiv=temp->voisins;
        	temp->voisins=temp1;
        }
    //Deuxième extremité de la commoditée traitée
		if(cellpoint->suiv==NULL){
        	commod->extrB =n1;
        }
        temp=n1;
        cellpoint=cellpoint->suiv;
	}
  //Gestion des commoditées du réseau
	if(R->commodites==NULL){
		R->commodites=commod;
    }
    else{
		commod->suiv=R->commodites;
       	R->commodites=commod;
    }
    cellchaine = cellchaine->suiv;
  }
  return R;
}

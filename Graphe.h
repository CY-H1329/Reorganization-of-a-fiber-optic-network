#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include<stdlib.h>
#include<stdio.h>
#include "Struct_Liste.h"
#include "Struct_File.h"
#include "Reseau.h"
#include "SVGwriter.h"
#include "Chaine.h"

typedef struct{
  int u,v;        /* Numeros des sommets extremité */
} Arete;


typedef struct cellule_arete{
  Arete *a;     /* pointeur sur l'arete */
  struct cellule_arete *suiv;
} Cellule_arete;


typedef struct {
  int num;                 /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin;  /* Liste chainee des voisins */
} Sommet;


typedef struct{
  int e1,e2;    /* Les deux extremites de la commodite */
} Commod;


typedef struct{
  int nbsom;        /* Nombre de sommets */
  Sommet* *T_som;    /* Tableau de pointeurs sur sommets */
  int gamma;
  int nbcommod;     /* Nombre de commodites */
  Commod *T_commod; /* Tableau des commodites */
} Graphe;

//QUESTION 7.1
Graphe* creerGraphe(Reseau *R);
//QUESTION 7.2
int nbArete(Graphe *G, int u, int v);
//QUESTION 7.3
ListeEntier* nbAreteListe(Graphe *G, int u, int v);
//QUESTION 7.4
int reorganiseReseau(Reseau *r);

//FONCTION DE LIBERATION D'UNE CELLULE ARETE
void free_Cell_arete(Cellule_arete* ca);

//FONCTION DE LIBERATION DES SOMMETS
void free_Sommet(Sommet* S);

//FONCTION DE LIBERATION D'UN GRAPHE
void free_Graphe(Graphe* G);
#endif

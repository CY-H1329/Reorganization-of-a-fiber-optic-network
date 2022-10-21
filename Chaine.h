#ifndef __CHAINE_H__
#define __CHAINE_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "SVGwriter.h"

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

//QUESTION 1.1
Chaines* lectureChaines(FILE *f);

//QUESTION 1.2
void ecrireChaines(Chaines *C, FILE *f);
//Fonction qui compte le nombre de CellPoint
int compte_cellpoints(CellChaine *cellP);


//QUESTION 1.3
void afficheChainesSVG(Chaines *C, char* nomInstance);

//QUESTION 1.4
double longeurChaine(CellChaine *c);
double longueurTotale(Chaines *C);
//Fonction qui calcule la distance
double distance(double x1, double y1, double x2, double y2);

//QUESTION 1.5
int comptePointsTotal(Chaines *C);

//QUESTION 6.2
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax, int ymax);

//ANNEXES
//Fonction de création des structures
CellPoint *creer_cellpoint(double x, double y);
CellChaine *creer_cellchaine(int num);
Chaines *creer_chaines(int nb_chaine, int gamma);

//Fonction d'insertion des structures
CellPoint *inserer_cellpoint(CellChaine *cc, double x, double y);
CellChaine *inserer_cellchaine(Chaines *ptrc, int num);

//Fonctions de libération des structures
void free_cellpoint(CellPoint *nv);
void free_cellchaine(CellChaine *cell);
void free_chaines(Chaines *cell);

#endif

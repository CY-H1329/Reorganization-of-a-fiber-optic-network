#ifndef __ARBRE_QUAT_H__
#define __ARBRE_QUAT_H__
#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"

/* Arbre quaternaire contenant les noeuds du reseau */
typedef struct arbreQuat{
    double xc, yc;          /* Coordonnees du centre de la cellule */
    double coteX;           /* Longueur de la cellule */
    double coteY;           /* Hauteur de la cellule */
    Noeud* noeud;           /* Pointeur vers le noeud du reseau */
    struct arbreQuat *so;   /* Sous-arbre sud-ouest, pour x < xc et y < yc */
    struct arbreQuat *se;   /* Sous-arbre sud-est, pour x >= xc et y < yc */
    struct arbreQuat *no;   /* Sous-arbre nord-ouest, pour x < xc et y >= yc */
    struct arbreQuat *ne;   /* Sous-arbre nord-est, pour x >= xc et y >= yc */
} ArbreQuat;

//QUESTION 5.1
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax);
//QUESTION 5.2
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX,double coteY);
//QUESTION 5.3
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat*parent);
//QUESTION 5.4
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*parent, double x, double y);
//QUESTION 5.5
Reseau* reconstitueReseauArbre(Chaines* C);

//FONCTION DE LIBERATION D'ARBRE
void free_Arbre(ArbreQuat* A);

//FONCTION D'AFFICHAGE D'ARBRE
void draw_AR( ArbreQuat *a );
#endif

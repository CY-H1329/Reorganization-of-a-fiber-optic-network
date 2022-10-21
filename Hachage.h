#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"

//QUESTION 4.1

typedef struct tableHachage{
    CellNoeud** tab;
    int taille;
} TableHachage;


//QUESTION 4.2
int fonction_cle(double x, double y);

//QUESTION 4.3
int fonction_hachage(int k,int m);

//QUESTION 4.4
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y);

//QUESTION 4.5
Reseau* reconstitueReseauHachage(Chaines *C, int M);


//FONCTION DE LIBERATION D'UN TABLEAU D'HACHAGE
void free_Hachage(TableHachage* T);

#endif

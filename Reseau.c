#include "Reseau.h"

//ANNEXES UTILES POUR LA SUITE
void liberer_cellNoeud(CellNoeud* cellN){
	//Fonction qui permet de libérer l'ensemble des cellnoeud
    CellNoeud *tmp_celln;
    CellNoeud *voisin;
    while (cellN){
        if (cellN->nd){
            voisin = cellN->nd->voisins;
            while (voisin){
                tmp_celln = voisin;
                voisin = voisin->suiv;
                free(tmp_celln);
            }
        }
        tmp_celln = cellN;
        cellN = cellN->suiv;
        free(tmp_celln);
    }
}

void liberer_cellcommodite(CellCommodite *cell){
		//Fonction qui permet de libérer les commoditées
    CellCommodite *tmp;
    while (cell){
        tmp = cell;
        cell = cell->suiv;
        free(tmp);
    }
}

void liberer_reseau(Reseau *R){
  //Fonction qui libère la memoire allouée pour un reseau
    liberer_cellNoeud(R->noeuds);
    liberer_cellcommodite(R->commodites);
  free(R);
}




//QUESTION 2.1
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
	//Fonction qui retourne un Noeud du reseau R correspondant au point (x,y) dans la liste chaîınée noeuds de R.
	CellNoeud* cn=R->noeuds;
	while(cn){
		//Test de l'appartenance du point x et y dans le réseau
		if((cn->nd->x)==x && (cn->nd->y)==y){
			return cn->nd;
		}
		cn=cn->suiv;
	}
	//On crée le noeud
	Noeud* res=(Noeud*)malloc(sizeof(Noeud));
	if(res==NULL){
		printf("Erreur d'allocation du Noeud\n");
		return NULL;
	}
	res->num=R->nbNoeuds+1;
	res->x=x;
	res->y=y;
	res->voisins=NULL;
	//On insère le noeud dans le reseau
	CellNoeud* newc=(CellNoeud*)malloc(sizeof(CellNoeud));
	if(newc==NULL){
		printf("Erreur d'allocation du CellNoeud\n");
		return NULL;
	}
	newc->nd=res;
	R->nbNoeuds++;
	CellNoeud* temp=R->noeuds;
	newc->suiv=temp;
	R->noeuds=newc;
	return res;
}


//QUESTION 2.2
Reseau* reconstitueReseauListe(Chaines *C){
	//Fonction qui reconstruit le reseau R à partir de la liste des chaînes C
	if(C==NULL){
		printf("Chaine vide \n");
		return NULL;
	}
    //On crée le reseau
    Reseau* reseau=(Reseau*)malloc(sizeof(Reseau));
		if(reseau==NULL){
			fprintf(stderr,"Erreur d'allocation du Reseau\n");
			return NULL;
		}
    reseau->nbNoeuds=0;
    reseau->gamma=C->gamma;
    reseau->noeuds=NULL;
    reseau->commodites=NULL;
    CellChaine* cc=C->chaines;
		//On parcourt les cellchaine de la chaine
    while(cc){
			//On traite le cas du première extremité de la commoditée du réseau traitée
        CellPoint* cp=cc->points;
        CellCommodite* commod=(CellCommodite*)malloc(sizeof(CellCommodite));
				if(commod==NULL){
					fprintf(stderr, "Erreur d'allocation lors de la reconstitution\n");
					return NULL;
				}
        Noeud* temp=rechercheCreeNoeudListe(reseau,cp->x,cp->y);
        commod->extrA=temp;
        cp=cp->suiv;
        while(cp){
					//On parcourt les cellpoints de la cellchaine traitée
            Noeud* n1=rechercheCreeNoeudListe(reseau,cp->x,cp->y);
            CellNoeud* temp1=(CellNoeud*)malloc(sizeof(CellNoeud));
            CellNoeud* temp2=(CellNoeud*)malloc(sizeof(CellNoeud));
						if(temp1==NULL || temp2==NULL){
							fprintf(stderr, "Erreur d'allocation lors de la reconstitution\n");
							return NULL;
						}
            temp1->nd=n1;
            temp2->nd=temp;
            CellNoeud* v1=n1->voisins;
            int g=0;
            while(v1){
                if(v1->nd==temp){
                    g=1;
                }
                v1=v1->suiv;
            }
						//Gestion du cas des voisins en l'ajoutant s'il ne fait pas déjà partie des voisins du cellnoeud traitée
            if(g==0){
                temp2->suiv=n1->voisins;
                n1->voisins=temp2;
                temp1->suiv=temp->voisins;
                temp->voisins=temp1;
            }
						//Gestion du deuxième extremité de la commoditée du réseau traitée
            if(cp->suiv==NULL){
                commod->extrB =n1;
            }
            temp=n1;
            cp=cp->suiv;
        }
				//Ajout des commodites au réseau
        if(reseau->commodites==NULL){
            reseau->commodites=commod;
        }
        else{
            commod->suiv=reseau->commodites;
            reseau->commodites=commod;
        }
        cc=cc->suiv;
    }
    return reseau;
}

//QUESTION 3.1
int nbCommodites(Reseau *R){
	//Fonction qui compte le nombre de commoditées totales du réseau
  int cpt=0;
  CellCommodite* res= R->commodites;
  while(res != NULL){
    cpt++;
    res = res->suiv;
  }
  return cpt;
}


int nbLiaisons(Reseau *R){
	//Fonction qui compte le nombre de liaisons totales du réseau
	int cpt=0;
	CellNoeud* cn=R->noeuds;
	while(cn){
		CellNoeud* vois=cn->nd->voisins;
		while(vois){
			if(cn->nd->num<vois->nd->num){
				cpt++;
			}
			vois=vois->suiv;
		}
		cn=cn->suiv;
	}
	return cpt;
}




//QUESTION 3.2
void ecrireReseau(Reseau *R, FILE *f){
	//Fonction qui ́ecrit dans un fichier le contenu d’un Reseau en respectant le même format du fichier 00014burma.res
    if(f == NULL){
      printf("Probleme provenant du fichier\n");
      return;
    }
    if(R == NULL){
      printf("La Chaine n'existe pas !\n");
      return;
    }

    //Ecriture des 4 premières lignes
    fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
    fprintf(f, "NbLiaisons: %d\n",nbLiaisons(R));
    fprintf(f, "NbCommodites: %d\n",nbCommodites(R));
    fprintf(f, "Gamma: %d\n", R->gamma);
    fprintf(f,"\n");


    //Ecriture des noeuds
    CellNoeud *cn = R->noeuds;
    while(cn){
        fprintf(f, "v %d %f %f\n", cn->nd->num, cn->nd->x, cn->nd->y);
        cn = cn->suiv;
    }
    fprintf(f,"\n");


    //Ecriture des liaisons
    CellNoeud *c = R->noeuds;
    while(c){
        CellNoeud *v = c->nd->voisins;
        while(v){
            if(v->nd->num<c->nd->num){
                fprintf(f, "l %d %d\n", v->nd->num,c->nd->num);
            }
            v = v->suiv;
        }
        c = c->suiv;
    }
    fprintf(f,"\n");

    //Ecriture des commodites
    CellCommodite *cc = R->commodites;
    while (cc){
        fprintf(f,"k %d %d\n",cc->extrA->num , cc->extrB->num);
        cc = cc->suiv;
    }
}


//QUESTION 3.3
void afficheReseauSVG(Reseau *R, char* nomInstance){
	//Fonction qui permet de creer un fichier SVG en html pour visualiser un reseau.
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}

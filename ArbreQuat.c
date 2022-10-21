#include "ArbreQuat.h"

//FONCTION DE LIBERATION D"ARBRE
void free_Arbre(ArbreQuat* A){
	if(A->noeud!=NULL){
		CellNoeud* voisin = A->noeud->voisins;
		CellNoeud *tmp_celln;
		while (voisin){
			tmp_celln = voisin;
			voisin = voisin->suiv;
			free(tmp_celln);
	    }
		free(A->noeud);
	}
	if(A->so!=NULL){
		free_Arbre(A->so);
		free(A->so);
	}
	if(A->no!=NULL){
		free_Arbre(A->no);
		free(A->no);
	}
	if(A->se!=NULL){
		free_Arbre(A->se);
		free(A->se);
	}
	if(A->ne!=NULL){
		free_Arbre(A->ne);
		free(A->ne);
	}
	free(A);
}
	

//QUESTION 5.1
void chaineCoordMinMax(Chaines *C, double *xmin, double *ymin, double *xmax, double *ymax){
  //Fonction qui détermine les coordonnees minimales et maximales des points constituant les differentes chaînes du reseau
    if( C == NULL ){
      printf("Chaine vide\n");
      return;
    }
    *xmin = C->chaines->points->x;
    *ymin = C->chaines->points->y;
    *xmax = C->chaines->points->x;
    *ymax = C->chaines->points->y;

    CellChaine *cc = C->chaines;
    while(cc){
        CellPoint *cp = cc->points;
        while(cp){
            double cx = cp->x;
            double cy = cp->y;
            if(cx >= *xmax){
                *xmax = cx;
            }
            else if( cx < *xmin){
                *xmin = cx;
            }

            if( cy >= *ymax){
            *ymax = cy;
            }

            else if( cy < *ymin){
                *ymin = cy;
            }
        cp = cp->suiv;
        }
    cc = cc->suiv;
    }
}

//QUESTION 5.2
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
  //Fonction qui permet de creer l’arbre quaternaire
  ArbreQuat *abr = (ArbreQuat *)malloc(sizeof(ArbreQuat));
  if(!abr){
    fprintf(stderr,"Erreur d'allocation\n");
    return NULL;
  }
  abr->xc = xc;
  abr->yc = yc;
  abr->coteX = coteX;
  abr->coteY = coteY;
  abr->noeud = NULL;
  abr->no = NULL;
  abr->so = NULL;
  abr->se = NULL;
  abr->ne = NULL;
  return abr;
}

//QUESTION 5.3

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
  //Fonction permettant d’inserer un Noeud du reseau dans un arbre quaternaire, lors de l’insertion d’un noeud, trois cas sont à considerer (arbre vide, feuille et cellule interne).
	if(*a == NULL){
		//Cas de l'arbre vide
		if ((n->x < parent->xc) && (n->y < parent->yc)){
			*a = creerArbreQuat(parent->xc - (parent->coteX)/4, parent->yc - (parent->coteY)/4, (parent->coteX)/2, (parent -> coteY)/2);
			parent->so = *a;
			(*a)->noeud = n;
		}
		if ((n->x >= parent->xc) && (n->y < parent->yc)){
			*a = creerArbreQuat(parent->xc + (parent->coteX)/4, parent->yc - (parent->coteY)/4, (parent->coteX)/2, (parent -> coteY)/2);
			parent->se = *a;
			(*a)->noeud = n;
		}
		if ((n->x >= parent->xc) && (n->y >= parent->yc)){
			*a = creerArbreQuat(parent->xc + (parent->coteX)/4, parent->yc + (parent->coteY)/4, (parent->coteX)/2, (parent -> coteY)/2);
			parent->ne = *a;
			(*a)->noeud = n;
		}
		if ((n->x < parent->xc) && (n->y >= parent->yc)){
			*a = creerArbreQuat(parent->xc - (parent->coteX)/4, parent->yc + (parent->coteY)/4, (parent->coteX)/2, (parent -> coteY)/2);
			parent->no = *a;
			(*a)->noeud = n;
		}
	}else{
		if ((*a)->noeud == NULL){
      //Cas : feuille
			if ((n->x<(*a)->xc) && (n->y<(*a)->yc)){
					insererNoeudArbre(n, &((*a)->so), *a);
			}
			if ((n->x>=(*a)->xc) && (n->y<(*a)->yc)){
					insererNoeudArbre(n, &((*a)->se), *a);
			}
			if ((n->x>=(*a)->xc) && (n->y>=(*a)->yc)){
					insererNoeudArbre(n, &((*a)->ne), *a);
			}
			if ((n->x<(*a)->xc) && (n->y>=(*a)->yc)){
					insererNoeudArbre(n, &((*a)->no), *a);
			}

		}
		if ((*a != NULL)&& ((*a)->noeud != NULL)){
			//Cas : noeud interne
			//On demarre par l'insertion de l'ancienne feuille
			Noeud *ntmp = (*a)->noeud;
			(*a)->noeud = NULL;
			if ((ntmp->x<(*a)->xc) && (ntmp->y<(*a)->yc)){
				insererNoeudArbre(ntmp,&((*a)->so),*a);
			}
			if ((ntmp->x>=(*a)->xc) && (ntmp->y<(*a)->yc)){
				insererNoeudArbre(ntmp,&((*a)->se),*a);
			}
			if ((ntmp->x>=(*a)->xc) && (ntmp->y>=(*a)->yc)){
				insererNoeudArbre(ntmp,&((*a)->ne),*a);
			}
			if ((ntmp->x<(*a)->xc) && (ntmp->y>=(*a)->yc)){
				insererNoeudArbre(ntmp,&((*a)->no),*a);
			}

			//Insertion du noeud n
			if ((n->x<(*a)->xc) && (n->y<(*a)->yc)){
				insererNoeudArbre(n,&((*a)->so),*a);
			}
			if ((n->x>=(*a)->xc) && (n->y<(*a)->yc)){
				insererNoeudArbre(n,&((*a)->se),*a);
			}
			if ((n->x>=(*a)->xc) && (n->y>=(*a)->yc)){
				insererNoeudArbre(n,&((*a)->ne),*a);
			}
			if ((n->x<(*a)->xc) && (n->y>=(*a)->yc)){
				insererNoeudArbre(n,&((*a)->no),*a);
			}
		}
	}
}


//QUESTION 5.4
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
  //Fonction qui retourne un Noeud du reseau R correspondant au point de coordonnees (x,y) dans l’arbre quaternaire. Trois cas sont à distinguer (arbre vide, feuille et cellule interne)
  //Premier cas : Arbre vide
  if((*a == NULL)){
    //On crée le noeud
    Noeud* res=(Noeud*)malloc(sizeof(Noeud));
    if(res==NULL){
      fprintf(stderr, "Erreur d'allocation du Noeud\n");
      return NULL;
    }
  	res->num=R->nbNoeuds+1;
  	res->x=x;
  	res->y=y;
  	res->voisins=NULL;
    //On insère le noeud dans le reseau
    CellNoeud* newc=(CellNoeud*)malloc(sizeof(CellNoeud));
    if(newc==NULL){
      fprintf(stderr, "Erreur d'allocation du CellNoeud\n");
      return NULL;
    }
    newc->nd=res;
    R->nbNoeuds++;
    newc->suiv=R->noeuds;
    R->noeuds=newc;
    //On insère le noeud dans l'arbre
    insererNoeudArbre(res,a,parent);
    return res;
  	}else{
    //Deuxième cas : Feuille
    if(((*a)->noeud != NULL)){
      if((*a)->noeud->x==x && (*a)->noeud->y==y){
        return (*a)->noeud;
	  }
      else{
        if(((*a)->xc>=x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->no),*a,x,y);}
        if(((*a)->xc>=x) && ((*a)->yc < y)){
          return rechercheCreeNoeudArbre(R,&((*a)->so),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->se),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc <y)){
          return rechercheCreeNoeudArbre(R,&((*a)->ne),*a,x,y);}
      }
    }else{
      //Troisème cas : Cellule interne
	  if((*a != NULL)&& ((*a)->noeud == NULL)){
        if(((*a)->xc>=x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->no),*a,x,y);}
        if(((*a)->xc>=x) && ((*a)->yc < y)){
          return rechercheCreeNoeudArbre(R,&((*a)->so),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc>=y)){
          return rechercheCreeNoeudArbre(R,&((*a)->se),*a,x,y);}
        if(((*a)->xc < x) && ((*a)->yc <y)){
          return rechercheCreeNoeudArbre(R,&((*a)->ne),*a,x,y);}
      }
    }
  }
  return NULL;
}


//QUESTION 5.5
Reseau* reconstitueReseauArbre(Chaines* C){
  //Fonction qui reconstruit le réseau R à partir de la liste des chaînes C et en utilisant l'arbre quaternaire
  //On crée le reseau
  Reseau* reseau=(Reseau*)malloc(sizeof(Reseau));
  if(reseau==NULL){
    fprintf(stderr, "Erreur d'allocation du Reseau\n");
    return NULL;
  }
  reseau->nbNoeuds=0;
  reseau->gamma=C->gamma;
  reseau->noeuds=NULL;
  reseau->commodites=NULL;
  //On trouve les coordonnées minimales et maximales de la chaine
  double coteXMin;
  double coteYMin;
  double coteXMax;
  double coteYMax;
  chaineCoordMinMax(C,&coteXMin,&coteYMin,&coteXMax,&coteYMax);
  //Création de l'arbre quaternaire avec les coordonnées XMax et YMax
  ArbreQuat* abr=creerArbreQuat(coteXMin+(coteXMax-coteXMin)/2,coteYMin+(coteYMax-coteYMin)/2, coteXMax*2, coteYMax*2);
  CellChaine* cellchaine = C->chaines;
  //compteur de points totales
  int cpt=0;
  while (cellchaine){
	 CellPoint* cellpoint=cellchaine->points;
   Noeud* temp=rechercheCreeNoeudArbre(reseau,&abr,abr,cellpoint->x, cellpoint->y);
	 Noeud* comA=temp;
	 cellpoint=cellpoint->suiv;
	 cpt++;
	 while (cellpoint){
      Noeud* n1=rechercheCreeNoeudArbre(reseau,&abr,abr,cellpoint->x, cellpoint->y);
  	  CellNoeud* temp1=(CellNoeud*)malloc(sizeof(CellNoeud));
     	CellNoeud* temp2=(CellNoeud*)malloc(sizeof(CellNoeud));
      if(temp1==NULL || temp2==NULL){
        fprintf(stderr, "Erreur d'allocation en cours de reconstitution\n");
        return NULL;
      }
      temp1->nd=n1;
     	temp2->nd=temp;
	  	CellNoeud* v1=n1->voisins;
      	int g=0;
      	while(v1){
			       if(v1->nd->x==temp->x && v1->nd->y==temp->y){
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
      temp=n1;
		  cpt++;
      cellpoint=cellpoint->suiv;
	}
	Noeud* comB=temp;
  CellCommodite* commod=(CellCommodite*)malloc(sizeof(CellCommodite));
  if(commod==NULL){
    fprintf(stderr, "Erreur d'allocation de la CellCommodite\n");
    return NULL;
  }
  //Gestion des deux extremités d'une commoditée
	commod->extrA=comA;
	commod->extrB=comB;
  //Gestion de la liaison des commoditées avec le réseau
	commod->suiv=reseau->commodites;
  reseau->commodites=commod;
  cellchaine = cellchaine->suiv;
  }
  return reseau;
}

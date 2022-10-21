#include "Chaine.h"

//Fonctions de création des structures

CellPoint *creer_cellpoint(double x, double y){
  //Fonction qui crée un cellpoint x et y donnée en paramètres
    CellPoint *point = (CellPoint*)malloc(sizeof(CellPoint));
    if (!point){
      printf("Erreur d'allocation cellpoint \n");
      return NULL;
    }
    point->x = x;
    point->y = y;
    point->suiv = NULL;
    return point;
}

CellChaine *creer_cellchaine(int num){
  //Fonction qui crée un cellchaine avec comme paramètre son numéro
    CellChaine *cell = malloc(sizeof(CellChaine));
    if (!cell){
      printf("Erreur d'allocation cellchaine \n");
      return NULL;
    }
    cell->numero = num;
    cell->points = NULL;
    cell->suiv = NULL;
    return cell;
}

Chaines* creer_chaines(int nb_chaine, int gamma){
  //Fonction qui crée une chaine avec comme paramètre son nombre de chaine total et son nombre maximal de fibres par cable gamma
  Chaines *chaine = malloc(sizeof(Chaines));
  if (!chaine){
    printf("Erreur d'allocation chaine\n");
    return NULL;
  }
  chaine->nbChaines = nb_chaine;
  chaine->gamma = gamma;
  chaine->chaines = NULL;
  return chaine;
}


//Fonctions d'insertions des structures
CellPoint *inserer_cellpoint(CellChaine *cc, double x, double y){
  //Fonction qui insère un cellpoint dans une liste chainee de chaines (cellchaine)
    if (!cc){
        printf("Cellchaine vide.\n");
        return NULL;
  }
    CellPoint *res = creer_cellpoint(x, y);
    res->suiv = cc->points;
    cc->points = res;
    return res;
}

CellChaine *inserer_cellchaine(Chaines *ptrc, int num){
  //Fonction qui insère une cellchaine dans l'ensemble des chaines
    if (!ptrc){
    printf("Chaine vide.\n");
    return NULL;
  }
    CellChaine *res = creer_cellchaine(num);
    res->suiv = ptrc->chaines;
    ptrc->chaines = res;
    return res;
}


//Fonctions de libération des structures

void free_cellpoint(CellPoint *point){
    CellPoint *stock;
    while(point){
        stock = point;
        point = point->suiv;
        free(stock);
    }
}

void free_cellchaine(CellChaine *cell){
  if(!cell){
    printf("Cellchaine vide\n");
    return;
  }
  while (cell){
    free_cellpoint(cell->points);
    CellChaine *stock=cell->suiv;
    free(cell);
    cell=stock;
  }
}

void free_chaines(Chaines *chaine){
  if(!chaine){
    printf("Chaine vide\n");
    return;
  }
  free_cellchaine(chaine->chaines);
  free(chaine);
}


//QUESTION 1.1
//Chaines* lectureChaines(FILE *f){
  /*Fonction transformant un fichier en structure Chaines*/
 /* Chaines *chaine;
  char buffer[256];
  char buffer2[256];
  char buffer3[256];
  int gamma, nb_chaines;
  double x,y;
  fgets(buffer, 256, f);
  //Lecture du nombre de chaines et de gamma
  if ((sscanf(buffer, "%s %d",buffer3, &nb_chaines)) != 2){
    printf("Erreur de format sur la lecture du nombre de chaines\n");
    return NULL;
  }
  fgets(buffer, 256, f);
  if ((sscanf(buffer, "%s %d",buffer3, &gamma)) != 2){
    printf("Erreur de format sur la lecture de gamma\n");
    return NULL;
  }
  chaine = creer_chaines(nb_chaines, gamma);
  //Lecture des coordonnées
  int i,j,nb_points;
    while(fgets(buffer, 256, f)){
        sscanf(buffer ,"%d %d %[^\n]\n", &i ,&nb_points,buffer2);
        CellChaine *c = inserer_cellchaine(chaine, i);
        j = 0;
        while(j < nb_points){
            sscanf(buffer2, " %5lf %5lf %[^\n]\n", &x, &y, buffer2);
            inserer_cellpoint(c, x, y);
            j++;
        }
    }
    return chaine;
}
*/

Chaines* lectureChaines(FILE *f){
    /* Initialisation des chaines */
	Chaines* c;

    int nbChain; //Nombre de chaine au total
    int Gamma; //Gamma

    /* Recuperation du nombre de chaine total et du gamma */
    fscanf(f, "NbChain: %d\nGamma: %d",&nbChain,&Gamma);
	c= creer_chaines(nbChain,Gamma);


    int nomChaine, nbPoints, i, j; 
	float x,y;
    j = 0;

    /* Recuperation des chaines et de leurs points */
    while (!feof(f) && j<nbChain){ //tant qu'on est pas a la fin du fichier et que le nombre de chaine est inf à nbChain

		//lecture des 2 premieres valeurs de la ligne
        fscanf(f,"\n%d %d",&nomChaine,&nbPoints); 
        CellChaine* cc = creer_cellchaine(nomChaine);
		//lecture des premières coordonnees + creation point
        fscanf(f," %f %f",&x,&y); 

        /* Creation d'un premier point */
        CellPoint* cp = creer_cellpoint(x,y);
        /* Creation des points suivants que l'on ajoutera à cp */
        i = 0;
        while(i < nbPoints-1){ //on continue jusqu'a la fin
            fscanf(f," %f %f",&x,&y);
            CellPoint* cp2 = creer_cellpoint(x,y);
            cp2->suiv = cp;
            cp = cp2;
            i++;
        }
        cc->points = cp;
        cc->suiv = c->chaines;
            c->chaines = cc;
        j++;
    }
    return c;
}




//Fonction intermédiaire à l'écriture
int compte_cellpoints(CellChaine *cellP){
  /*Fonction qui compte le nombre de points à partir de CellChaine*/
    int i = 0;
    CellPoint *ptr = cellP->points;
    while(ptr){
      i++;
      ptr = ptr->suiv;
    }
    return i;
}

//QUESTION 1.2
void ecrireChaines(Chaines *C, FILE *f){
  /*Ecrit dans un fichier une chaine en respectant le format d'origine*/
  fprintf(f,"NbChain: %d\n", C->nbChaines);
  fprintf(f,"Gamma: %d\n", C->gamma);
  CellPoint *ptrP;
  CellChaine *ptrC = C->chaines;
  int nb_cellP;
  int i = 0;
  while (ptrC){
    ptrP = ptrC->points;
    nb_cellP = compte_cellpoints(ptrC);
    fprintf(f,"%d %d",i, nb_cellP);
    while (ptrP){
      fprintf(f," %.2f %.2f", ptrP->x ,ptrP->y);
      ptrP = ptrP->suiv;
    }
    i++;
    fprintf(f,"\n");
    ptrC = ptrC->suiv;
  }
}


//QUESTION 1.3
void afficheChainesSVG(Chaines *C, char* nomInstance){
  //Fonction qui crée une representation graphique des instances
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
        precx=pcour->x;
        precy=pcour->y;
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

//Fonction intémerdiaire à la question 1.4
double distance(double x1, double y1, double x2, double y2){
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

//QUESTION 1.4
double longeurChaine(CellChaine *c){
  //Fonction qui calcule la longueur physique d’une chaîıne.
	double lng=0.0;
	while(c->points->suiv){
		lng+=distance(c->points->x,c->points->y,c->points->suiv->x,c->points->suiv->y);
		c->points=c->points->suiv;
	}
	return lng;
}

double longueurTotale(Chaines *C){
  //Fonction qui calcule la longueur physique totale des chaînes.
	double t=0.0;
	while(C-> chaines){
		t+=longeurChaine(C->chaines);
		C->chaines= C->chaines->suiv;
	}
	return t;
}

//QUESTION 1.5
int comptePointsTotal(Chaines *C){
  //Fonction qui donne le nombre total d’occurrences de points (les points en doubles sont comptés)
	int cpt=0;
	while(C->chaines){
		CellChaine* c=C->chaines;
		while(c->points){
			cpt++;
			c->points=c->points->suiv;
		}
		C->chaines=C->chaines->suiv;
	}
	return cpt;
}



//QUESTION 6.2
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax, int ymax){
  /*Fonction qui prend en paramètre le nombre de chaînes à créer, le nombre de points par chaîne et les coordonnees maximales des points.
  Pourchacune des chaînes, cette fonction doit créer aleatoirement nbPointsChaine points situes entre les points (0,0) et (xmax,ymax).*/
  //On crée et initialise la chaîne résultat
	Chaines* res=(Chaines*)malloc(sizeof(Chaines));
	if(res==NULL){
	    printf("Erreur d'allocation\n");
	    return NULL;
	}
	res->chaines=NULL;
	res->nbChaines=nbChaines;
	res->gamma=nbChaines;
	CellChaine* temp=NULL;
	for(int i=0; i<nbChaines; i++){
		CellChaine* cc=(CellChaine*)malloc(sizeof(CellChaine));
		cc->numero=i;
		cc->points=NULL;
		for(int j=0; j<nbPointsChaine ; j++){
      //Génération aléatoire des points x et y compris entre xmax et ymax
			int x= (rand()%(xmax));
			int y= (rand()%(ymax));
			CellPoint* cp=(CellPoint*)malloc(sizeof(CellPoint));
			cp->x=x+0.01;
			cp->y=y+0.01;
			cp->suiv=cc->points;
			cc->points=cp;
			cp=cp->suiv;
		}
		cc->suiv=temp;
		temp=cc;
	}
	res->chaines=temp;
	return res;
}

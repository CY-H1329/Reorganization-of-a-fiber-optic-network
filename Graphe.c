#include "Graphe.h"


//FONCTION DE LIBERATION D'UNE CELLULE ARETE
void free_Cell_arete(Cellule_arete* ca){
	if(!ca){
    	printf("Cellule arete vide\n");
    	return;
  	}
    while(ca){
    	free(ca->a);
    	Cellule_arete* stock=ca->suiv;
    	free(ca);
    	ca=stock;
  }
}

//FONCTION DE LIBERATION DES SOMMETS
void free_Sommet(Sommet* S){
	if(!S){
    	printf("Sommets vides\n");
    	return;
  	}
   	free_Cell_arete(S->L_voisin);
	free(S);
}


//FONCTION DE LIBERATION D'UN GRAPHE
void free_Graphe(Graphe* G){
	for(int i = 0 ; i < G->nbsom ; i++){
		free_Sommet(G->T_som[i]);
	}
	free(G);
}
	


//QUESTION 7.1
Graphe* creerGraphe(Reseau *R){
	//Fonction qui permet de créer un graphe correspondant au réseau R
	//On alloue le graphe
	Graphe *g=(Graphe*)malloc(sizeof(Graphe));
	if (g==NULL) {
		fprintf(stderr, "Erreur d'allocation\n");
		return NULL;
	}
	g->nbsom=R->nbNoeuds;
	g->gamma=R->gamma;
	g->nbcommod=nbCommodites(R);
	g->T_commod=(Commod*)malloc(sizeof(Commod)*g->nbcommod);
	g->T_som=(Sommet**)malloc(sizeof(Sommet*)*(g->nbsom));
	//Initialisation du tableau de pointeur sur sommet permettant de faire correspondre le numéro des noeuds à leur position dans le tableau de sommmets
	for (int i = 0; i < g->nbsom; i++) {
		g->T_som[i]=(Sommet*)malloc(sizeof(Sommet));
		g->T_som[i]->num=i+1;
		g->T_som[i]->L_voisin=NULL;
	}
	//Initialisation da la matrice permettant de gérer le parcours des voisins
	int mat[g->nbsom][g->nbsom];
	for(int i = 0 ; i < g->nbsom ; i++){
		for(int j = 0; j < g->nbsom ; j++){
			mat[i][j]=0;
		}
	}
	CellNoeud* cn=R->noeuds;
	//Parcours des cellnoeud du réseau R
	while(cn){
		Noeud* tmp=cn->nd;
		g->T_som[tmp->num-1]->x=tmp->x;
		g->T_som[tmp->num-1]->y=tmp->y;
		while(tmp->voisins){
			//Parcours des voisins de chaque cellnoeud
			CellNoeud* voisin=tmp->voisins;
			if(mat[tmp->num][voisin->nd->num-1]!=1){
				//Si le voisin n'est pas déjà parcouru on l'ajoute dans la matrice
				mat[tmp->num][voisin->nd->num-1]=1;
				mat[voisin->nd->num][tmp->num-1]=1;
				Arete* a=(Arete*)malloc(sizeof(Arete)); //On crée l'arête à stocker dans le graphe
				a->u=tmp->num;
				a->v=voisin->nd->num;
				Cellule_arete* ca=(Cellule_arete*)malloc(sizeof(Cellule_arete));
				// On insère l'arête dans une cellule_arête du tableau de sommet du graphe
				ca->a=a;
				ca->suiv=g->T_som[tmp->num-1]->L_voisin;
				g->T_som[tmp->num-1]->L_voisin=ca;
			}
			else{
				//Si le voisin est déjà parcouru une fois
				Cellule_arete* ca=(Cellule_arete*)malloc(sizeof(Cellule_arete));
				Cellule_arete* tmp2=g->T_som[voisin->nd->num-1]->L_voisin;
				//On ajoute dans la liste des voisins du sommet u et v du graphe mais sans allouer une deuxième arête
				while(tmp2){
					if((tmp2->a->u==tmp->num && tmp2->a->v==voisin->nd->num) || (tmp2->a->v==tmp->num && tmp2->a->u==voisin->nd->num)){
						break;
					}
					tmp2=tmp2->suiv;
				}
				ca->a=tmp2->a;
				ca->suiv=g->T_som[tmp->num-1]->L_voisin;
				g->T_som[tmp->num-1]->L_voisin=ca;
				}
			tmp->voisins=tmp->voisins->suiv;
		}
	cn=cn->suiv;
  }
	//Gestion des commodites du graphe
	CellCommodite* cc=R->commodites;
	int k=0;
	while(cc){
		Commod* c=(Commod*)malloc(sizeof(Commod));
		c->e1=cc->extrA->num;
		c->e2=cc->extrB->num;
		g->T_commod[k]=*c;
		k++;
		cc=cc->suiv;
	}
	return g;
}

//QUESTION 7.2
int nbArete(Graphe *G, int u, int v){
	//Fonction retournant le plus petit nombre d’arêtes d’une chaîne entre deux sommets u et v d’un graphe
    if(u==v){
			printf("Chemin vide\n");
			return 0;
		}
    int res=0;
    int* pcr =(int*)calloc(G->nbsom,sizeof(int));
    S_file *f = (S_file*)malloc(sizeof(S_file));
    Init_file(f);
    enfile(f, u);
	pcr[u-1]=1;
    pcr[v-1] = G->nbsom; //case d'indice du numéro du sommet que l'on veut atteindre
    while(!(estFileVide(f))){
        int temp = defile(f); // le sommet actuel est le premier sommet inseré FIFO
		Cellule_arete *voisinage = G->T_som[temp-1]->L_voisin;
        while(voisinage){
        	int voisin;
            if(voisinage->a->u == temp){
                voisin = voisinage->a->v;
			}
            else{
            	voisin = voisinage->a->u;
			}
			//Arrivé à ce stade voisin n'a pas encore été visité donc elle vaut 0
            if( pcr[voisin-1] == 0 ){
                pcr[voisin-1] = pcr[temp-1]+1;
				if(pcr[temp-1]==G->nbsom){
					res++;
				}
				else{
					res=pcr[temp-1];
				}
                enfile(f, voisin); //On l'ajoute en fin de file
				voisinage = voisinage->suiv;
            }
            else{
	            //On tombe sur le sommet de départ on passe au voisin suivant
				if(pcr[temp-1]==G->nbsom){
					res++;
				}
				else{
					res=pcr[temp-1];
				}
    	        if( voisin == v ){ //On arrive à destination
    	            if( res < pcr[v-1] ){ // Test du chemin le plus court ou non
    	                pcr[v-1]=res;
						break;
    	            }
    	            //Si ce n'est pas le plus court chemin on passe au voisin suivant
    	            else{
    	            	voisinage = voisinage->suiv;
    	            	continue;
    	          	}
				}
				else{
    	          	voisinage = voisinage->suiv;
    	        }
    	    }
		}
    }
	res=pcr[v-1];
    free(pcr);
	free(f);
    return res;
}

//QUESTION 7.3
ListeEntier* nbAreteListe(Graphe *G, int u, int v){
	/*Fonction qui calcul le plus petit nombre d’arêtes d’une chaîne entre deux sommets u et v d’un graphe et renvoie
	une liste d’entiers correspondant à cette chaîne.*/
	ListeEntier* e=(ListeEntier*)malloc(sizeof(ListeEntier));
	Init_Liste(e);
    if(u == v){
		ajoute_en_tete(e,v);
		return e;
	}
	int* pred =(int*)malloc(sizeof(int)*G->nbsom) ;
	for(int i = 0; i < G->nbsom ; i++){
		pred[i]=-1;
	}
	pred[u-1]=u-1;
    S_file *f = (S_file*)malloc(sizeof(S_file));
    Init_file(f);
    enfile(f, u);
    while(!(estFileVide(f))){
        int temp = defile(f); // le sommet actuel est le premier sommet inseré FIFO
		Cellule_arete *voisinage = G->T_som[temp-1]->L_voisin;
        while(voisinage){
            int voisin;
            if(voisinage->a->u == temp){
                voisin = voisinage->a->v;
			}
            else{
                voisin = voisinage->a->u;
			}
			if(pred[voisin-1]==-1){
				pred[voisin-1]=temp;
			}
			if( voisin == v ){
				f->tete=NULL;
				break;
			}
			else{
				enfile(f,voisin);
			}
			voisinage = voisinage->suiv;
		}
  	}
	int pr=v;
	ajoute_en_tete(e,pr);
	free(f);//On libere la file
	return e;
}

//QUESTION 7.4
int reorganiseReseau(Reseau *r){
	/*Fonction qui crée le graphe correspondant au reseau, qui calcule la plus courte chaîne pour chaque commoditée
	et qui retourne vrai si pour toute arête du graphe,le nombre de chaînes qui passe par cette arête est inferieur à γ, et faux sinon.*/
	int res=1;
	Graphe* G = creerGraphe(r);
	int gamma = r->gamma;
	Commod* commod=G->T_commod;
	int mat[G->nbsom][G->nbsom];
	for(int i = 0 ; i < G->nbsom ; i++){
		for(int j = 0; j < G->nbsom ; j++){
			mat[i][j]=0;
		}
	}
	for(int i = 0 ; i < G->nbcommod ; i++){
		ListeEntier* chaine = nbAreteListe(G,commod[i].e1,commod[i].e2);
		while((*chaine)->suiv){
			mat[((*chaine)->u)-1][((*chaine)->suiv->u)-1]=(mat[((*chaine)->u)-1][((*chaine)->suiv->u)-1])+1;
			mat[((*chaine)->suiv->u)-1][((*chaine)->u)-1]=(mat[((*chaine)->suiv->u)-1][((*chaine)->u)-1])+1;
			(*chaine)=(*chaine)->suiv;
		}
		desalloue(chaine);
	}
	for(int i = 0 ; i < G->nbsom ; i++){
		for(int j = 0; j < G->nbsom ; j++){
			if(mat[i][j]>=gamma){
				res=0;
			}
		}
	}
	return res;
}


/*void afficheGraphe(Graphe* g){
    printf("Sommets: %d\nCommo: %d\nGamma: %d\n",g->nbsom,g->nbcommod,g->gamma);
    printf("---Sommets---\n");
    for(int i = 0; i < g->nbsom; i++){
        printf("S%d (%.2f,%.2f) --\n",g->T_som[i]->num,g->T_som[i]->x,g->T_som[i]->y);
        Cellule_arete* ca = g->T_som[i]->L_voisin;
        while(ca){
            printf("{%d,%d} ",ca->a->u,ca->a->v);
            ca = ca->suiv;
        }
        printf("\n");
    }
    printf("---Comm---\n");
    Commod* tab = g->T_commod;
    for(int i = 0; i < g->nbcommod; i++){
        printf("[%d,%d]\n",(tab+i)->e1,(tab+i)->e2);
    }
}*/

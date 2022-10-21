#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"


void menuReseau(){
    printf("1-Utilisation des listes pour manipuler un reseau:\n");
    printf("2-Utilisation de la table de hachage pour manipuler un reseau:\n");
    printf("3-Utilisation d'un arbre pour manipuler un reseau:\n");
    printf("4-Sortie du programme\n");
    return;
}

//QUESTION 2.3
int main(int argc, char**argv){
  if (argc != 3){
    printf("3 arguments en parametres, Nom de l'executable - Nom du fichier source - Nom du fichier de destination format texte\n");
    return 1;
  }
  FILE *fr = fopen(argv[1], "r");
  Chaines *chaine = lectureChaines(fr);
  FILE *file = fopen(argv[2], "w");
  Reseau *R=NULL;
  Reseau *D=NULL;
  Reseau *B=NULL;
  int choix=0;
	do{
		printf("\n");
    char buffer[200];
  	menuReseau();
    printf("\n---------------------------------\n");
  	printf("Merci de bien vouloir mentionner votre choix : ");
    fgets(buffer, 200, stdin);
    sscanf(buffer,"%d",&choix);

  	while( choix < 0 || choix > 4 ){
      printf("\nAttention, votre choix n'est pas valide.\n");
      char buffer[200];
      menuReseau();
      printf("Merci de bien vouloir mentionner un autre chiffre compris entre 1 et 4 : ");
      fgets(buffer, 200, stdin);
      sscanf(buffer, "%d", &choix);
			printf("\n");
      }
		printf("\n");
    switch(choix){
      case 1:
        R=reconstitueReseauListe(chaine);
        printf("Reseau reconstitue par Liste Chainee\n");
        ecrireReseau(R, file);
        afficheReseauSVG(R,"Instance2");
        break;
      case 2:
		    B=reconstitueReseauHachage(chaine,100);
		    ecrireReseau(B, file);
		    afficheReseauSVG(B,"Instance3");
        break;
      case 3:
        D=reconstitueReseauArbre(chaine);
        printf("Reseau reconstitue par Arbre Quaternaire\n");
        afficheReseauSVG(D,"Instance4");
        ecrireReseau(D, file);
        break;
      case 4:
        free_chaines(chaine);
		fclose(fr);
        fclose(file);
        printf("Fin du programme\n");
        exit(1);
        break;

      }
    }
    while( choix != 0);
    	printf("\n---------------------------------\n");
      printf("Merci, et au revoir.\n");
  		if(chaine!=NULL){ // En cas d'oubli de libération des bibliothèques
  			free_chaines(chaine);
  		}
	if((fr!=NULL) && (file !=NULL)){
		fclose(fr);
		fclose(file);
	}
	/*if(R!=NULL){
		liberer_reseau(R);
	}
	if(B!=NULL){
		liberer_reseau(B);
	}
	if(D!=NULL){
		liberer_reseau(D);
	}*/
	fclose(fr);
	fclose(file);
	return 1;
}

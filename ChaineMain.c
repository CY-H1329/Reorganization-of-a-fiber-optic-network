#include "Chaine.h"

//QUESTION 1.2
int main(int argc, char **argv){
    if (argc != 3){
    printf("3 arguments en parametres !");
        exit(1);
    }
  //Test de la lecture d'un fichier
  FILE *ficsource = fopen(argv[1], "r");
  Chaines *chaine = lectureChaines(ficsource);

  //Test de l'écriture d'un fichier
  FILE *ficdest = fopen(argv[2], "w");
  ecrireChaines(chaine, ficdest);

  //Test de la QUESTION 1.3
  afficheChainesSVG(chaine,"Instance");

  //Libération de la chaine allouée
  free_chaines(chaine);

  //Fermeture des fichiers de test
  fclose(ficsource);
  fclose(ficdest);
  
  return 0;
}

#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "Graphe.h"

int main(int argc, char**argv){
	if (argc < 2 || argc > 4){
	printf("3 arguments en parametres : Nom de l'executable - Nom du fichier source - Nom du fichier de destination format texte\n");
	return 1;
	}
	clock_t temps_initial1;
	clock_t temps_final1;
	double temps_cpu1;
	clock_t temps_initial2;
	clock_t temps_final2;
	double temps_cpu2;
	clock_t temps_initial3;
	clock_t temps_final3;
	double temps_cpu3;
	Reseau *R=NULL;
	Reseau *B=NULL;
	Reseau *D;

	FILE *file1 = fopen(argv[1], "r");
	Chaines *chaine1 = lectureChaines(file1);
	FILE *file2 = fopen(argv[1], "r");
	Chaines *chaine2 = lectureChaines(file2);
	FILE *file3 = fopen(argv[1], "r");
	Chaines *chaine3 = lectureChaines(file3);

	FILE *file = fopen("fromage.txt","w");
	FILE* find = fopen(argv[2],"w");
	if(find==NULL){
		printf("Erreur dans l'ouverture de ficher\n");
        return 1;
    }
	for(int i=0; i<5001 ; i+=500){
		temps_initial1 = clock () ;
		R=reconstitueReseauListe(chaine1);
		temps_final1 = clock () ;
		temps_cpu1 = ((double)(temps_final1 - temps_initial1))/CLOCKS_PER_SEC;


		temps_initial2 = clock () ;
		B=reconstitueReseauHachage(chaine2,i);
		temps_final2 = clock () ;
		temps_cpu2 = ((double)(temps_final2 - temps_initial2))/CLOCKS_PER_SEC;


		temps_initial3 = clock () ;
		D=reconstitueReseauArbre(chaine3);
		temps_final3 = clock () ;
		temps_cpu3 = ((double)(temps_final3 - temps_initial3))/CLOCKS_PER_SEC;
		ecrireReseau(D,file);

		fprintf(find,"%f %f %f\n",temps_cpu1,temps_cpu2,temps_cpu3);
	}

	fclose(file1);
	fclose(file2);
	fclose(file3);
	fclose(file);
	fclose(find);

	
	/*FILE* f1=fopen("vitesses_Liste.txt","w");
	FILE* f2=fopen("vitesses_Hach_Arbre.txt","w");
	//FILE* f3=fopen("Lecture.txt","r");

	for(int i=1; i<=5001; i+=500){
		Chaines* c=generationAleatoire(i,100,5000,5000);
		//ecrireChaines(c,f2);
		//Chaines* d=lectureChaines(f3);
		Chaines* C1=c;
		Chaines* C2=c;
		Chaines* C3=c;

		temps_initial1 = clock () ;
		R=reconstitueReseauListe(C1);
		temps_final1 = clock () ;
		temps_cpu1 = ((double)(temps_final1 - temps_initial1))/CLOCKS_PER_SEC;
		fprintf(f1,"%d %f\n",i,temps_cpu1);


		temps_initial2 = clock () ;
		D=reconstitueReseauArbre(C2);
		temps_final2 = clock () ;
		temps_cpu2 = ((double)(temps_final2 - temps_initial2))/CLOCKS_PER_SEC;
		fprintf(f2,"%d %f ",i,temps_cpu2);

		for(int j=5; j<=501 ; j+=75){
			C3=c;
			temps_initial3 = clock () ;
			B=reconstitueReseauHachage(C3,j);
			temps_final3 = clock () ;
			temps_cpu3 = ((double)(temps_final3 - temps_initial3))/CLOCKS_PER_SEC;
			fprintf(f2,"%f ",temps_cpu3);
		}
		fprintf(f2,"\n");
	}
	fclose(f1);
	fclose(f2);
	//fclose(f3);*/


	srand(time(NULL));

	FILE* face= fopen(argv[1],"r");
	FILE* f4=fopen(argv[2],"w");
	Chaines* c=generationAleatoire(10,10,50,50);
	Chaines* C= lectureChaines(face);
	Reseau* Y=reconstitueReseauListe(c);
	ecrireReseau(Y, f4);
	Graphe* G=creerGraphe(Y);
	//afficheGraphe(G);
	int J=nbArete(G,8,4);
	printf("resultat=%d\n",J);

	ListeEntier* lc=nbAreteListe(G,5,8);
	
	int i=reorganiseReseau(Y);
	printf("%d\n",i);

	if(R!=NULL){
		liberer_reseau(R);
	}
	if(B!=NULL){
		liberer_reseau(B);
	}
	if(D!=NULL){
		liberer_reseau(D);
	}

	return 1;
}

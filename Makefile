CFLAGS = -g -ggdb -Wall -Wextra -pedantic -lm
CC = gcc

PROGRAMS = ChaineMain ReconstitueReseau Main

.PHONY:	all clean

.SUFFIX:

all: $(PROGRAMS)

Main: Main.o Reseau.o Hachage.o ArbreQuat.o Chaine.o SVGwriter.o Graphe.o Struct_Liste.o Struct_File.o
	$(CC) -o $@ $(CFLAGS) $^

ChaineMain: ChaineMain.o Chaine.o SVGwriter.o
	$(CC) -o $@ $(CFLAGS) $^

ReconstitueReseau: ReconstitueReseau.o SVGwriter.o Reseau.o Chaine.o Hachage.o ArbreQuat.o
	$(CC) -o $@ $(CFLAGS) $^

SVGwriter.o : SVGwriter.c SVGwriter.h
	gcc -c $(CFLAGS) SVGwriter.c

Chaine.o : Chaine.c Chaine.h SVGwriter.h
	gcc -c $(CFLAGS) Chaine.c

ChaineMain.o: ChaineMain.c Chaine.h SVGwriter.h
	gcc -c $(CFLAGS) ChaineMain.c

Reseau.o : Reseau.c Reseau.h Chaine.h SVGwriter.h
	gcc -c $(CFLAGS) Reseau.c

ReconstitueReseau.o: ReconstitueReseau.c Chaine.h SVGwriter.h Reseau.h Hachage.h ArbreQuat.h
	gcc -c $(CFLAGS) ReconstitueReseau.c

Hachage.o : Hachage.c Hachage.h Reseau.h Chaine.h SVGwriter.h
	gcc -c $(CFLAGS) Hachage.c

ArbreQuat.o : ArbreQuat.c ArbreQuat.h Reseau.h Chaine.h SVGwriter.h
	gcc -c $(CFLAGS) ArbreQuat.c

Main.o : Main.c ArbreQuat.h Hachage.h Reseau.h Chaine.h SVGwriter.h Graphe.h
	gcc -c $(CFLAGS) Main.c

Graphe.o : Graphe.c Graphe.h Reseau.h Chaine.h SVGwriter.h Struct_Liste.h Struct_File.h
	gcc -c $(CFLAGS) Graphe.c

Struct_Liste.o : Struct_Liste.c Struct_Liste.h
	gcc -c $(CFLAGS) Struct_Liste.c

Struct_File.o : Struct_File.c Struct_File.h
	gcc -c $(CFLAGS) Struct_File.c


clean:
	rm -f *.o *~ $(PROGRAMS)

CFLAGS= $(sdl2-config --cflags)
LDFLAGS= $(sdl2-config --libs)

all : prog


prog : main.o affichage_piano.o recherche_note.o frequentieltab.o temporeltab.o
	gcc -o prog main.o affichage_piano.o recherche_note.o frequentieltab.o temporeltab.o $$(sdl2-config --cflags --libs) -lgsl -lSDL2_ttf -lSDL2_mixer -lm

main.o : main.c affichage_piano.h recherche_note.h frequentieltab.h temporeltab.h
	gcc -o main.o -c -Wall main.c
    
affichage_piano.o : affichage_piano.c
	gcc -o affichage_piano.o -c -Wall affichage_piano.c $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_mixer
	
recherche_note.o : recherche_note.c
	gcc -o recherche_note.o -c -Wall recherche_note.c -lm
	

frequentieltab.o : frequentieltab.c
	gcc -o frequentieltab.o -c -Wall frequentieltab.c  -lm -lgsl
	
	
temporeltab.o : temporeltab.c
	gcc -o temporeltab.o -c -Wall temporeltab.c

	
	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf hello

/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include "temporeltab.h"
#include "frequentieltab.h"
#include "recherche_note.h"
#include "affichage_piano.h"

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
#define PI 3.1415926535897932385


//gcc -Wall -Wfatal-errors main_V2.c temporeltab.c recherche_note.c frequentieltab.c affichage_piano.c $(sdl2-config --cflags --libs) -lgsl -lm -lSDL2_mixemi -lSDL2_ttf


int main(int argc, char* argv[]) {

	/*-- Tableau temporel --*/
	
	char* filename = "500Hz.wav"; //494 en vrai
	
	int* pfe = malloc(sizeof(int)); //Pointeur vers fréquence d'échantillonnage
	unsigned int* ptaille = malloc(sizeof(unsigned int)); //Pointeur vers le nombre d'ech
	double* pkeyduration = malloc(sizeof(double)); //Pointeur vers la durée de la note
	
	double* tabt = NULL;
	tabt = temporeltab(filename, pfe, ptaille, pkeyduration);
	
	/*-- Tableau fréquentiel --*/
	
	int fe = *pfe; //Fréquence d'échantillonnage
	unsigned int taille = *ptaille; //Nombre d'échantillons temporels
	
	unsigned int* plongueur = malloc(sizeof(unsigned int)); //Pointeur du nombre d'ech en 2^
	
	double* abs_tabTF = NULL;
	abs_tabTF = frequentieltab(tabt,taille,plongueur);
	
	/*-- Recherche de la note --*/
	
	unsigned int longueur = *plongueur;
	
	unsigned int* ppos = malloc(sizeof(unsigned int));
	char* note = malloc(16 * sizeof(char));
	double* pf = malloc(sizeof(double));
	unsigned int* poctave = malloc(sizeof(unsigned int));
	
	recherche_note(fe, longueur, abs_tabTF, ppos, note, pf, poctave);
	
	/*-- Affichage dynamique de la note --*/
	
	double keyduration = *pkeyduration * 1000; //Durée de la note en ms
	unsigned int pos = *ppos;
	double f = *pf;
	unsigned int octave = *poctave;
		
	affichage_piano(pos, filename, fe, keyduration, note, f, octave);
	
	/*-- Libération --*/
	
	free(pfe);
	free(ptaille);
	free(pkeyduration);
	free(plongueur);
	free(ppos);
	free(note);
	free(pf);
	
	printf("----------\n\n");
	printf("Fin\n\n");
	printf("----------\n\n");
	
	return(0);
	
}
	
	

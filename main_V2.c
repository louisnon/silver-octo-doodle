/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include "temporeltab.h"
#include "frequentieltab.h"
#include "recherche_note.h"
#include "affichage.h"

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
#define PI 3.1415926535897932385


//gcc -Wall -Wfatal-errors main_V2.c temporeltab.c recherche_note.c frequentieltab.c affichage.c $(sdl2-config --cflags --libs) -lgsl -lm


int main(int argc, char* argv[]) {

	/*-- Tableau temporel --*/
	
	char* filename = "500Hz.wav"; //494 en vrai
	
	int* pfe = malloc(sizeof(int)); //Pointeur de la fréquence d'échantillonnage
	unsigned int* ptaille = malloc(sizeof(unsigned int)); //Pointeur du nombre d'ech
	
	
	double* tabt = NULL;
	tabt = temporeltab(filename,pfe,ptaille);
	
	/*-- Tableau fréquentiel --*/
	
	int fe = *pfe; //Fréquence d'échantillonnage
	unsigned int taille = *ptaille; //Nombre d'échantillons temporels

	unsigned int* plongueur = malloc(sizeof(unsigned int)); //Pointeur du nombre d'ech en 2^
	
	double* abs_tabTF = NULL;
	abs_tabTF = frequentieltab(tabt,taille,plongueur);
	
	/*-- Recherche de la note --*/
	
	unsigned int longueur = *plongueur;
	
	unsigned int* pcolor = malloc(sizeof(unsigned int));
	unsigned int* ppos = malloc(sizeof(unsigned int));
	
	recherche_note(fe, longueur, abs_tabTF, pcolor, ppos);
	
	/*-- Affichage dynamique de la note --*/
	
	unsigned int color = *pcolor;
	unsigned int pos = *ppos;
	
	affichage();

	return(0);
	
}
	
	

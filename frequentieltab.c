/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_errno.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
		
	
double* frequentieltab(double* tabt, unsigned int taille, unsigned int* plongueur) {

	
	unsigned int longueur = 1;
	unsigned int puissance = 0;
	int i;
	
	// L'algorithme de Cooley Tuckey fonctionne pour une puissance 
	// de 2 d'échantillons temporels
	
	while (taille > longueur) {
	
		longueur = longueur * 2;
		puissance = puissance + 1;
		
	}
	
	plongueur[0] = longueur;
	
	printf("----------\n\n");
	printf("Le fichier audio contient maintenant 2^%d = %d pour réaliser l'algorithme de la FFT\n\n",puissance,longueur);
	printf("----------\n\n");
	
	// Création des tableaux
	
	double* tabTF = NULL; //Tableau fréquentiel
	tabTF = calloc(2*longueur,sizeof(double));
	
	if (tabTF == NULL) {
	
		printf("Impossible d'allouer la mémoire pour le tableau fréquentiel\n");
		exit(1);
		
	}
	
	double* abs_tabTF = NULL; //Tableau fréquentiel en module
	abs_tabTF = calloc(longueur,sizeof(double));
	
	if (abs_tabTF == NULL) {
	
		printf("Impossible d'allouer la mémoire pour le tableau fréquentiel 																en module\n");
		exit(1);
		
	}
	
	// Remplissage des tableaux de la TF
	
	for (i = 0; i < taille; i++) {
	
		REAL(tabTF,i) = tabt[i];
		
	}
	
	
	gsl_fft_complex_radix2_forward(tabTF,1,longueur);

	
	for (i = 0; i < longueur; i++) {
	
		abs_tabTF[i] = sqrt(REAL(tabTF,i)*REAL(tabTF,i) + IMAG(tabTF,i)*IMAG(tabTF,i));
		
	}
	
	FILE* pf = fopen("frequentiel.txt","wb");	
		
	// Vérification du résultat de la TF
	
	for (i = 0; i < longueur; i++) {
				
		fprintf(pf,"%lf %lf\n",REAL(tabTF,i), IMAG(tabTF,i));
		
	}
			
	return(abs_tabTF);
	
}

/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>	
#include <stdbool.h>
#include <math.h>
#include <string.h>

	
double max(double* tab, int taille) {

	double M = tab[0];
	
	for (unsigned int i = 0; i < taille; i++) {
	
		if (M < tab[i]) {
		
			M = tab[i];
			
		}
		
	}

	return(M);
		
}

unsigned int shift(unsigned int indice, unsigned int longueur, double* abs_tabTF, double df) {
	
	unsigned int alpha = 10; //demi ton
	
	double middle = abs_tabTF[indice];
	bool valide = false;
	
	unsigned int indice_d = indice + 1; unsigned int indice_g = indice - 1;	
	
	while (indice_d < longueur && abs_tabTF[indice_d] > middle && (indice_d - indice) < alpha) {
	
		valide = true;
		middle = abs_tabTF[indice_d];
		indice_d++;
		
		
	}
	
	while (indice_g > -1 && abs_tabTF[indice_g] > middle && (indice - indice_g) < alpha) {
	
		valide = true;
		middle = abs_tabTF[indice_g];
		indice_d--;
		
	}
	
	double candidat1 = abs_tabTF[indice_d];
	double candidat2 = abs_tabTF[indice_g];
	
	if (candidat1 > candidat2 && valide == true) {
	
		return(indice_g);
		
	}
	
	else if (candidat1 <= candidat2 && valide == true) {
	
		return(indice_g);
		
	}
	
	else {
	
		return(indice);
		
	}
	
}	

double argmax(double fe, unsigned int longueur, double* abs_tabTF) {

	// Pas de fréquence
	double df = fe/longueur;
	
	printf("----------\n\n");
	printf("Le pas en fréquence pour la recherche de la note est df = %lf Hz\n\n",df);
	printf("----------\n\n");
	
	// https://fr.wikipedia.org/wiki/Fr%C3%A9quences_des_touches_du_piano
	// Intervalle de fréquences des touches de piano 
	//double fmin = 27.5;
	//double fmax = 4186.01;
		
	// Fréquence recherchée
	double f0;
		
	// Maximum du produit spectral et l'indice de tabTF associé
	double M0 = -1; double M;
	unsigned int IM0; 
		
	// Intermédiaire de calcul pour le produit spectral
	double ABS;
	
	unsigned int j;
	unsigned int i;
	unsigned int k;
	
	double seuil = max(abs_tabTF,longueur)/100;
	
	
	for (i = 1; i < longueur/2 + 1; i++) {
			
		M = 1;
		j = 1;
		
		do {
			
			k = shift(i * j, longueur, abs_tabTF, df);
			ABS = abs_tabTF[k];	
			M = M * ABS;
			j++;
			
		} while(i * j < longueur && ABS > seuil);
								
		// Principe de calcul du maximum
		if (M0 < M) {
				
			M0 = M;
			IM0  = i;
				
		}
		
	}
			
		
	// Fréquence de la note jouée
	f0 = IM0 * df;
	
	printf("----------\n\n");
	printf("La fréquence de la note jouée est : %lf Hz \n\n",f0);
	printf("----------\n\n");
		
	return(f0);
		
}

void recherche_note(double fe, unsigned int longueur, double* abs_tabTF, unsigned int* pcolor, unsigned int* ppos, char* note, double* pf, unsigned int* poctave) {

	double f0; //Fréquence de la note jouée
	f0 = argmax(fe, longueur, abs_tabTF);
	
	char nomnote[10];
	char nomnoteprec[10];
	unsigned int octave;
	unsigned int octaveprec;
	double frequencenote = 0;
	double frequencenoteprec;
	unsigned int color;
	unsigned int colorprec;
	unsigned int pos;
	unsigned int posprec;
	
	FILE* diconote = fopen("diconote.txt","r");

	while (f0 > frequencenote) {
	
		fscanf (diconote,"%d",&octave);
		fscanf (diconote,"%s",nomnote);
		fscanf (diconote,"%lf",&frequencenote);
		fscanf (diconote,"%d",&color);
		fscanf (diconote,"%d",&pos);
		
		frequencenoteprec = frequencenote;
		strcpy(nomnoteprec,nomnote);
		octaveprec = octave;
		colorprec = color;
		posprec = pos;
	
	}
	
	if ((f0 - frequencenoteprec) < (frequencenote - f0)) {
	
		frequencenote = frequencenoteprec;
		strcpy(nomnote,nomnoteprec);
		octave = octaveprec;
		color = colorprec;
		pos = posprec;
		
	}
	
	pcolor[0] = color;
	ppos[0] = pos;
	strcpy(note,nomnote);
	pf[0] = frequencenote;
	poctave[0] = octave;
	
	fclose(diconote);
	printf("----------\n\n");
	printf ("La note est : <%s> de frequence = %f Hz (octave %d)\n\n" ,nomnote  ,frequencenote,octave);
	printf("----------\n\n");
	
	char* colorchar;
	
	if (color) colorchar = "Blanc";
	else colorchar = "Noir";
	
	printf("----------\n\n");
	printf("La couleur de la note sur le piano est : %s\nLa position de la note sur le piano est : %d\n\n",colorchar,pos);
	printf("----------\n\n");
	
}	

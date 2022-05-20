/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535897932385

/*

Entrées : nom du fichier audio .wav à traiter, 2 pointeurs vers la fréquence d'échantillonnage et le nombre d'échantillons temporels du fichier audio pour réaliser un passage par adresse

Sorties : le tableau contenant tous les échantillons temporels du fichier audio

*/

/*----- Structures ----------------------------------------------------------------------------*/


struct wavfile { //définit la structure de l entete d un wave

	char id[4]; // doit contenir "RIFF"
	int totallength; // taille totale du fichier moins 8 octets
	char wavefmt[8]; // doit etre "WAVEfmt "
	int format; // 16 pour le format PCM
	short pcm; // 1 for PCM format
	short channels; // nombre de channels
	int frequency; // fréquence d'échantillonage
	int bytes_per_second; // nombre d'octets par seconde
	short bytes_by_capture; // nombre de bytes par échantillon
	short bits_per_sample; // nombre de bits par échantillon.
	char data[4]; // doit contenir "data"
	int bytes_in_data; // nombre de bytes de la partie data
	
};


/*----- Fin Structures ------------------------------------------------------------------------*/


/*----- Fonctions -----------------------------------------------------------------------------*/


//a(n) <- a(n)* (0.54+0.46cos(2pi (N/2-n)/N))
double hamming(unsigned int taille, int i) {

	double res;
	res = 0.54 + 0.46 * cos(2*PI*(taille/2 - i)/taille);
	return(res);
	
}

double* temporeltab(char* filename, int* pfe, unsigned int* ptaille, double* pkeyduration) {


/*----- Initialisation des variables ----------------------------------------------------------*/
	
	
	int fe;
	unsigned int nb_ech; //Nombre d'échantillons temporels
	unsigned int i; //Indice pour parcourir les différents tableaux
	float time; //Durée de l'audio
	
	
/*----- Fin Initialisation des variables ------------------------------------------------------*/


/*----- Sélection du fichier audio ------------------------------------------------------------*/


	printf("----------\n\n");
	printf("Nom du fichier choisi : %s\n\n",filename);
	printf("----------\n\n");
	
	
/*----- Fin Sélection du fichier audio---------------------------------------------------------*/


/*----- Ouverture du fichier audio (.wav) -----------------------------------------------------*/


	struct wavfile header; // Création du header
	
	FILE* wav = fopen(filename,"rb"); //Ouverture du fichier audio
	
	if (wav == NULL) {
		
		printf("Impossible d'ouvrir le fichier .wav soumis\n");
		printf("Rq : le fichier doit être un .wav\n");
		exit(1);
	
	}

	
/*----- Fin Ouverture du fichier audio --------------------------------------------------------*/


//*----- Lecture de l'entête et Enregistrement dans header ------------------------------------*/


	//Initialise le header par l'entête du fichier WAV
	//Vérifie que le fichier possède un entête compatible

	//Lecture du header
	if (fread(&header,sizeof(header),1,wav) < 1) {
		
		printf("Impossible de lire le header\n");
		exit(1);
	
	}
	
	//Lecture du format WAV
	if ( header.id[0] != 'R'|| header.id[1] != 'I'|| header.id[2] != 'F'|| header.id[3] != 'F' ) {
	
		printf("Le fichier soumis n'est pas au format .wav\n");
		exit(1);
	
	}
	
	//Vérification Mono
	if (header.channels != 1) {
		
		printf("Le fichier soumis n'est pas mono\n");
		exit(1);
	
	}
	
	//Fréquence d'échantillonnage
	fe = header.frequency;
	pfe[0] = fe;
	
	printf("----------\n\n");
	printf("Fréquence d'échantillonnage du fichier audio : %d Hz\n\n",fe);
	printf("----------\n\n");
	

/*----- Fin Lecture et Enregistrement ---------------------------------------------------------*/


/*----- Détermination de la taille des tableaux -----------------------------------------------*/

	nb_ech = (header.bytes_in_data/header.bytes_by_capture);
	
	ptaille[0] = nb_ech;
	
	printf("----------\n\n");
	printf("Le fichier audio contient %d échantillons\n\n",nb_ech);
	printf("----------\n\n");
	
	time = nb_ech*1./header.frequency;
	pkeyduration[0] = time;
	
	printf("----------\n\n");
	printf("Temps total du spectrogramme : %f s\n\n",time);
	printf("----------\n\n");
	

/*----- Fin Détermination des tailles ---------------------------------------------------------*/


/*----- Création des tableaux -----------------------------------------------------------------*/

	
	double* tabt = NULL; //Tableau de l'onde temporelle
	tabt = calloc(nb_ech,sizeof(double));
	
	if (tabt == NULL) {
	
		printf("Impossible d'allouer la mémoire du tableau de l'onde réelle\n");
		exit(1);
		
	}
	
	
/*----- Fin Création des tableaux -------------------------------------------------------------*/


/*----- Remplissage tableaux ------------------------------------------------------------------*/


	i = 0;	
	short value; //Variable qui va stocker les informatins lues dans le fichier .wav
	
	FILE* pt = fopen("temporel.txt","wb"); 	
	
	if (pt == NULL) {
	
		printf("Impossible d'ouvrir le fichier .txt de vérification des données temporelles\n");
		exit(1);
		
	}
	
	while(fread(&value,header.bytes_by_capture,1,wav) && i < nb_ech) {
	
		//Lecture et Enregistrement dans tab des échantillons 
		tabt[i] = value;
		
		//Fenêtrage de Hamming
		tabt[i] = tabt[i] * hamming(nb_ech,i);
		
		//Sauvegarde tabt dans temporel.txt pour vérification manuelle des données
		fprintf(pt,"%lf\n",tabt[i]);

		i++;
		
	}
	
	fclose(pt);
	
	printf("----------\n\n");
	printf("Nombre d'échantillons temporels lus : %d\n\n",i);
	printf("----------\n\n");
	

/*----- Fin Remplissage des tableaux ----------------------------------------------------------*/

	
	return(tabt);
	
}


/*----- Fin Fonctions -------------------------------------------------------------------------*/

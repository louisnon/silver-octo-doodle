#ifndef __TEMPORELTAB_H__
#define __TEMPORELTAB_H__

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

double hamming(double T, double t);

double* temporeltab(char* filename, int* pfe, unsigned int* pnb_ech);

#endif

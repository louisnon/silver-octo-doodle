#ifndef __RECHERCHE_NOTE_H__
#define __RECHERCHE_NOTE_H__

double max(double* tab, int taille);

unsigned int shift(unsigned int indice, unsigned int longueur, double* abs_tabTF, double df);

double argmax(double fe, unsigned int longueur, double* abs_tabTF);

void recherche_note(double fe, unsigned int longueur, double* abs_tabTF, unsigned int* pcolor, unsigned int* ppos, char* note, int* pf, unsigned int* poctave);

#endif

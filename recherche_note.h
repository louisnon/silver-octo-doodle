#ifndef __RECHERCHE_NOTE_H__
#define __RECHERCHE_NOTE_H__

double max(double* tab, int taille);

unsigned int shift(unsigned int indice, unsigned int longueur, double* abs_tabTF, double df);

double argmax(double fe, unsigned int longueur, double* abs_tabTF);

double absolue(double f1, double f2);

void recherche_note(double fe, unsigned int longueur, double* abs_tabTF, unsigned int* ppos, char* note, double* pf, unsigned int* poctave);

#endif

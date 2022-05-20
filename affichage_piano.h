#ifndef __AFFICHAGE_PIANO_H__
#define __AFFICHAGE_PIANO_H__

#include <SDL.h>

void SDL_ExitWithError1(const char* message);

void SDL_ExitWithError2(const char* message, SDL_Window* window);

void SDL_LimitFPS(unsigned int frame_limit);

void affichage_piano(unsigned int color, unsigned int pos, char* filename, int fe, double keyduration);

#endif

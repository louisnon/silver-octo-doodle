#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <SDL.h>

void SDL_ExitWithError1(const char* message);

void SDL_ExitWithError2(const char* message, SDL_Window* window);

void SDL_ExitWithError3(const char* message, SDL_Window* window, SDL_Renderer* renderer);

void affichage();

#endif

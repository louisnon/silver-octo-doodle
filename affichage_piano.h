#ifndef __AFFICHAGE_PIANO_H__
#define __AFFICHAGE_PIANO_H__

#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

void SDL_ExitWithError1(const char* message);

void Mix_ExitWithError1(const char* message);

void TTF_ExitWithError1(const char* message);

void SDL_ExitWithError2(const char* message, SDL_Window* window);

void Mix_ExitWithError2(const char* message, Mix_Chunk * background_sound);

void TTF_ExitWithError2(const char* message, TTF_Font * ourFont);

void TTF_ExitWithError3(const char* message, TTF_Font * ourFont, SDL_Surface * surfaceText);

void TTF_ExitWithError4(const char* message, TTF_Font * ourFont, SDL_Surface * surfaceText, SDL_Texture * textureText);

void SDL_LimitFPS(unsigned int frame_limit);

char* create_char(char* note, double f, unsigned int octave);

void affichage_piano(unsigned int pos, char* filename, int fe, double keyduration, char* note, double f, unsigned int octave);

#endif

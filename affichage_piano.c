/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


#define SCREENWIDTH 833
#define SCREENHEIGHT 600
#define FPS_LIMIT 16

/*----- Fonction annexes d'erreur -------------------------------------------------------------*/


void SDL_ExitWithError1(const char* message) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}

void Mix_ExitWithError1(const char* message) {

	SDL_Log("ERREUR : %s > %s\n", message, Mix_GetError());
	Mix_Quit();
	exit(EXIT_FAILURE);
	
}

void TTF_ExitWithError1(const char* message) {

	SDL_Log("ERREUR : %s > %s\n", message, TTF_GetError());
	TTF_Quit();
	exit(EXIT_FAILURE);
	
}

void SDL_ExitWithError2(const char* message, SDL_Window* window, SDL_Renderer* renderer) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}

void Mix_ExitWithError2(const char* message, Mix_Chunk * background_sound) {
	
	SDL_Log("ERREUR : %s > %s\n", message, Mix_GetError());
	Mix_FreeChunk(background_sound);
	Mix_Quit();
	exit(EXIT_FAILURE);
	
}

void TTF_ExitWithError2(const char* message, TTF_Font * ourFont) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	TTF_CloseFont(ourFont);
	TTF_Quit();
	exit(EXIT_FAILURE);
	
}

void TTF_ExitWithError3(const char* message, TTF_Font * ourFont, SDL_Surface * surfaceText) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_FreeSurface(surfaceText);
	TTF_CloseFont(ourFont);
	TTF_Quit();
	exit(EXIT_FAILURE);
	
}

void TTF_ExitWithError4(const char* message, TTF_Font * ourFont, SDL_Surface * surfaceText, SDL_Texture * textureText) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_DestroyTexture(textureText);
	SDL_FreeSurface(surfaceText);
	TTF_CloseFont(ourFont);
	TTF_Quit();
	exit(EXIT_FAILURE);
	
}
	
void SDL_LimitFPS(unsigned int frame_limit) {

	unsigned int ticks = SDL_GetTicks();	
	
	if (frame_limit < ticks) return;
	else if (frame_limit > ticks + FPS_LIMIT) SDL_Delay(FPS_LIMIT);
	else SDL_Delay(frame_limit - ticks);
	
		
}

char* create_char(char* note, int f, unsigned int octave) {

	char* f0 = calloc(16, sizeof(char)); // calloc obligatoire ici pour éviter les caractères parasites en fin de chaîne
	int power = 0;
	
	int rest = f;

	while (f > 0) {
	
		f = f/10;
		power++;
		
	}

	int denom;
	
	for (int i = 0; i < power; i++) {
		
		denom = pow(10, power - 1 - i);
		f0[i] = floor(rest/denom) + '0'; //Int To Char
		rest = rest%denom;
		
	}
	
	char* freq1 = "f = ";
	char* freq2 = " Hz";
	char* freq3 = " ; note : ";
	char* freq4 = " ; octave : ";
	//char* charoctave = octave + '0';
	
	char* buffer = malloc(128 * sizeof(char));
	
	strcat(strcpy(buffer, freq1), f0);
	strcat(buffer, freq2);
	strcat(buffer, freq3);
	strcat(buffer, note);
	strcat(buffer, freq4);
	//strcat(buffer, charoctave);	
	
	return(buffer);
	
}


/*----- Fin Fonction annexes d'erreur ---------------------------------------------------------*/
	

void affichage_piano(unsigned int color, unsigned int pos, char* filename, int fe, double keyduration, char* note, int f, unsigned int octave) {
	
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	
/*----- Lancement SDL ------------------------------------------------------------------------*/
	
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		SDL_ExitWithError1("Initialisation SDL échouée");
	
	
/*----- Lancement Module Son Mix -------------------------------------------------------------*/


	if (Mix_OpenAudio(fe, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)<0) 
		Mix_ExitWithError1("Initialisation Mix échouée");
	
	Mix_Chunk * background_sound = Mix_LoadWAV(filename);

	if (background_sound == NULL) Mix_ExitWithError1("Impossible de charger le son");
	

/*----- Lancement Module Police TTF -----------------------------------------------------------*/


	if (TTF_Init() == -1) TTF_ExitWithError1("Initialisation TTF échouée");
	
	TTF_Font * ourFont = TTF_OpenFont("unispace_bold.ttf",32);
	
	if (ourFont == NULL) TTF_ExitWithError1("Impossible de charger la police");
	
	
/*----- Création fenêtre + rendu  -------------------------------------------------------------*/
	
	
	if (SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, 0, &window, &renderer) != 0) 
		SDL_ExitWithError1("Impossible de créer la fénêtre et le rendu");
	
	
/*----- Suite Lancement Module Police TTF -----------------------------------------------------*/

	
	char* charnote = create_char(note, f, octave);
	
	SDL_Color textcolor = {255,255,255}; // On écrit en blanc
	SDL_Surface * surfaceText = TTF_RenderText_Solid(ourFont, charnote, textcolor);
	
	if (surfaceText == NULL) 
	TTF_ExitWithError2("Impossible de générer la surface de texte",ourFont);
						
	SDL_Texture * textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
					
	if (textureText == NULL) 
		TTF_ExitWithError3("Impossible de générer la texture du texte", ourFont, surfaceText);
							
	SDL_FreeSurface(surfaceText);
	
	
/*----- PROCESS -------------------------------------------------------------------------------*/


	SDL_bool program_launched = SDL_TRUE;
	
	/*-----
	
	unsigned int frame_limit = 0;
		
	// 60 FPS (1000/60)
		
	frame_limit = SDL_GetTicks() + FPS_LIMIT;
	SDL_LimitFPS(frame_limit); // Délai pour limiter à 60 fps
	frame_limit = SDL_GetTicks() + FPS_LIMIT;
	
	printf("Temps écoulé : %d ms\n",ticks);
		
		
	-----*/
	
	SDL_Rect rectangle;
	int i; 
	
	// Delay
	
	double duration = 1000;
	
	// Clavier
	
	int N_octaves = 8;
	int Nkeys_octave = 12;
	
	// Touches Blanches
	
	int N_keysb = 52;
	int w_keyb = 15;
	int h_keyb = 100;
	
	// Touches Noires
	
	int N_keysn = 36;
	int w_keyn = 12;
	int h_keyn = 65;
	
	// Tableau des abscisses des touches
	
	unsigned int** abscisses = NULL;
	abscisses = calloc(1*(N_keysb + N_keysn) ,sizeof(unsigned int*));
	
	if (abscisses == NULL) {
	
		printf("Impossible d'allouer la mémoire du tableau des abscisses\n");
		exit(1);
		
	}
	
	for (i = 0; i < N_keysb + N_keysn; i++) {
	
		abscisses[i] = calloc(2 ,sizeof(unsigned int));
		
		if (abscisses[i] == NULL) {
	
			printf("Impossible d'allouer la mémoire du tableau des abscisses\n");
			exit(1);
		
		}
	}

	
	FILE* pcp = fopen("piano.txt","wb"); //Vérifier les abscisses et les couleurs des touches
	
	while (program_launched) {

		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			
			switch(event.type) {
				

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					
					case SDLK_b:
						//printf("Touche B enfoncée\n");
						
						// Ecriture Texte
					

						rectangle.x = 10;
						rectangle.y = 10;
						rectangle.w = 200;
						rectangle.h = 30;
						
						if (SDL_RenderCopy(renderer, textureText, NULL, &rectangle) != 0) 
							TTF_ExitWithError4("Impossible de copier la texture dans le rendu", ourFont, surfaceText, textureText);
	
	
						// Octave 0
						
							// 2 Touches Blanches
						
						if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
							
						rectangle.x = 1;
						rectangle.y = 450;
						rectangle.w = w_keyb;
						rectangle.h = h_keyb;	
						
						abscisses[0][0] = rectangle.x;
						abscisses[0][1] = 1;
						
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);

							
						rectangle.x = 1 + (w_keyb + 1);
						rectangle.y = 450;
						rectangle.w = w_keyb;
						rectangle.h = h_keyb;	
						
						abscisses[2][0] = rectangle.x;
						abscisses[2][1] = 1;
						
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
							
							// 1 Touche Noire
							
						if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
							
						rectangle.x = 1 + 1 * (w_keyb + 1) - 2*w_keyb/5;
						rectangle.y = 450;
						rectangle.w = w_keyn;
						rectangle.h = h_keyn;
						
						abscisses[1][0] = rectangle.x;
						abscisses[1][1] = 0;
							
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
									
						// Octave 1 à 7
						
						for (i = 0; i < N_octaves - 1; i++) {	
							
							// Touches Blanches
							
							
							if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) ;
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[3 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[3 + i * Nkeys_octave][1] = 1;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + (w_keyb + 1);
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[5 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[5 + i * Nkeys_octave][1] = 1;
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 2 * (w_keyb + 1);
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[7 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[7 + i * Nkeys_octave][1] = 1;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);								
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 3 * (w_keyb + 1);
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[8 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[8 + i * Nkeys_octave][1] = 1;
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 4 * (w_keyb + 1);
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[10 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[10 + i * Nkeys_octave][1] = 1;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 5 * (w_keyb + 1);
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[12 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[12 + i * Nkeys_octave][1] = 1;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 6 * (w_keyb + 1);
							rectangle.y = 450;
							rectangle.w = w_keyb;
							rectangle.h = h_keyb;
								
							abscisses[14 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[14 + i * Nkeys_octave][1] = 1;	
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							// Touches Noires
							
							
							if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + (w_keyb + 1) - 2*w_keyb/5;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
								
							abscisses[4 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[4 + i * Nkeys_octave][1] = 0;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + (w_keyb + 1) + (w_keyb + 1) - 3*w_keyb/10;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
								
							abscisses[6 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[6 + i * Nkeys_octave][1] = 0;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);	
								
								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 3 * (w_keyb + 1) + (w_keyb + 1) - w_keyb/2;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
								
							abscisses[9 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[9 + i * Nkeys_octave][1] = 0;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);	

								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 4 * (w_keyb + 1) + (w_keyb + 1) - w_keyb/3;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
								
							abscisses[11 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[11 + i * Nkeys_octave][1] = 0;
								
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);

								
							rectangle.x = 1 + 2 * (w_keyb + 1) + (i * (N_octaves - 1)) * (w_keyb + 1) + 5 * (w_keyb + 1) + (w_keyb + 1) - w_keyb/4;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
								
							abscisses[13 + i * Nkeys_octave][0] = rectangle.x;
							abscisses[13 + i * Nkeys_octave][1] = 0;	
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
		
							
						}
							
						
						// Dernier octave
						
			
							// Touche Blanche
							
							
						if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
							SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
								
						rectangle.x = 1 + (N_keysb - 1) * (w_keyb + 1);
						rectangle.y = 450;
						rectangle.w = w_keyb;
						rectangle.h = h_keyb;
								
						abscisses[N_keysb + N_keysn - 1][0] = rectangle.x;
						abscisses[N_keysb + N_keysn - 1][1] = 1;
								
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
							SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);	
							
							
						// Liseret Rouge
							
							
						if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)  	 	
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
							
						rectangle.x = 1;
						rectangle.y = 449;
						rectangle.w = SCREENWIDTH;
						rectangle.h = 1;
						
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
							
						// Liseret Noir
							

						if (SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE) != 0) 			
							SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
								
						rectangle.x = 1;
						rectangle.y = 447;
						rectangle.w = SCREENWIDTH;
						rectangle.h = 2;
							
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 					 			
							SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
							
						// Liseret Gris
							
						
						if (SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE) != 0) 			
							SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
								
						rectangle.x = 1;
						rectangle.y = 445;
						rectangle.w = SCREENWIDTH;
						rectangle.h = 2;
							
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
							SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
						
						SDL_RenderPresent(renderer);	
						SDL_Delay(duration);
							
						// Touche en surbrillance
						
							// Vérification des abscisses et des couleurs 
							
						for (i = 0; i < N_keysb + N_keysn; i ++) {
						
							fprintf(pcp,"%d %d\n", abscisses[i][0], abscisses[i][1]);
							
						}
						
						unsigned int keyabscisse = abscisses[pos][0];
						unsigned int R_neighborcolor = 2; // différents de 0 et 1
						unsigned int L_neighborcolor = 2; 
						unsigned int R_neighborpos = 0; // différents des abscisses des touches de piano
						unsigned int L_neighborpos = 0; 
												
						if (pos + 1 < N_keysb + N_keysn) {
						
							R_neighborcolor = abscisses[pos + 1][1];
							R_neighborpos = abscisses[pos + 1][0];
							
						}
						
						if (pos - 1 > 0) {
						
							L_neighborcolor = abscisses[pos - 1][1];
							L_neighborpos = abscisses[pos - 1][0];
							
						}
						
						
						if (color == 1) {
							
							if (R_neighborcolor == 0 && L_neighborcolor == 0) { // 2 voisins noirs
						 
								
								if (SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
										
								if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
										SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
									

								rectangle.x = R_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									    	
									    	
								rectangle.x = L_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								// Son
			
													
								SDL_RenderPresent(renderer);	
								
								if (Mix_PlayChannel(1,background_sound,0) == -1) 
									Mix_ExitWithError2("Impossible de jouer le son",background_sound);
									
								SDL_Delay(keyduration);

								
								
								// Retour à l'état initial
				

								if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
										
								if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
										SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
									

								rectangle.x = R_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									    	
									    	
								rectangle.x = L_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									    
									    	
								SDL_RenderPresent(renderer);
									    	
							}
								
							else if (R_neighborcolor == 1 && L_neighborcolor == 0) { // voisin droite blanc et voisin gauche noir
							
							
								if (SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
										
								if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
										SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
									    	
									    	
								rectangle.x = L_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
								
								// Son
			
														
								SDL_RenderPresent(renderer);	
								
								if (Mix_PlayChannel(1,background_sound,0) == -1) 
									Mix_ExitWithError2("Impossible de jouer le son",background_sound);
									
								SDL_Delay(keyduration);
															
								
								// Retour à l'état initial
				

								if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
										
								if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
										SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
									    	
									    	
								rectangle.x = L_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									    
									    	
								SDL_RenderPresent(renderer);
								
							}
							
							else if (R_neighborcolor == 0 && L_neighborcolor == 1) { // voisin droite noir et voisin gauche blanc
						 
								
								if (SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
										
								if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
										SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
									

								rectangle.x = R_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);

								
								// Son
			
														
								SDL_RenderPresent(renderer);	
								
								if (Mix_PlayChannel(1,background_sound,0) == -1) 
									Mix_ExitWithError2("Impossible de jouer le son",background_sound);
									
								SDL_Delay(keyduration);
															
								
								// Retour à l'état initial
				

								if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
										
								if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
										SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
									

								rectangle.x = R_neighborpos;
								rectangle.y = 450;
								rectangle.w = w_keyn;
								rectangle.h = h_keyn;
									
									
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									    	SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									    
									    	
								SDL_RenderPresent(renderer);
								
							}
								
							else if (R_neighborcolor == 1 && L_neighborcolor == 1) { // 2 voisins blancs
							
							
								if (SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
										
								
								// Son
			
														
								SDL_RenderPresent(renderer);	
								
								if (Mix_PlayChannel(1,background_sound,0) == -1) 
									Mix_ExitWithError2("Impossible de jouer le son",background_sound);
									
								SDL_Delay(keyduration);
																
								
								// Retour à l'état initial
				

								if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
									SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
														
								rectangle.x = keyabscisse;
								rectangle.y = 450;
								rectangle.w = w_keyb;
								rectangle.h = h_keyb;
											
								if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
									SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									    
									    	
								SDL_RenderPresent(renderer);
								
							}
							
						}
						
						else if (color == 0) {
						
							// Touches Noires
							
							if (SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE) != 0) 
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
													
							rectangle.x = keyabscisse;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
										
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									
							SDL_RenderPresent(renderer);
							
														
							// Son
								
	
							if (Mix_PlayChannel(1,background_sound,0) == -1) 
									Mix_ExitWithError2("Impossible de jouer le son",background_sound);
									
							SDL_Delay(keyduration);

							
							
							// Retour à l'état initial
			

							if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
								SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);	
													
							rectangle.x = keyabscisse;
							rectangle.y = 450;
							rectangle.w = w_keyn;
							rectangle.h = h_keyn;
										
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
									
							
							SDL_RenderPresent(renderer);
							
						}						
							
						SDL_Delay(duration);
						
						continue;
						
						
					
					default:
						continue;
						
					}
						
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
				
				default:
					break;
					
			}			
								
		}
	
	}
	
	
/*----- Libérations ---------------------------------------------------------------------------*/
	
	
	fclose(pcp);
	free(abscisses);
	
	
	TTF_Quit();
	
	
	Mix_FreeChunk(background_sound);
	Mix_Quit();
	
	
	SDL_DestroyTexture(textureText);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


/*----- Fin -----------------------------------------------------------------------------------*/
	
	
	printf("----------\n\n");
	printf("Voici le piano\n\n");
	printf("----------\n\n");
	
}

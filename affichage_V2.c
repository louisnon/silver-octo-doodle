/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>


#define SCREENWIDTH 833
#define SCREENHEIGHT 600
#define FPS_LIMIT 16

/*----- Fonction annexes d'erreur -------------------------------------------------------------*/


void SDL_ExitWithError1(const char* message) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}

void SDL_ExitWithError2(const char* message, SDL_Window* window, SDL_Renderer* renderer) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}

void SDL_LimitFPS(unsigned int frame_limit) {

	unsigned int ticks = SDL_GetTicks();	
	
	if (frame_limit < ticks) return;
	else if (frame_limit > ticks + FPS_LIMIT) SDL_Delay(FPS_LIMIT);
	else SDL_Delay(frame_limit - ticks);
	
		
}


/*----- Fin Fonction annexes d'erreur ---------------------------------------------------------*/
	


int main(int argc, char* argv[]) {

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	
/*----- Lancement SDL ------------------------------------------------------------------------*/
	
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		SDL_ExitWithError1("Initialisation SDL échouée");
	

/*----- Création fenêtre + rendu  -------------------------------------------------------------*/
	
	
	if (SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, 0, &window, &renderer) != 0) 
		SDL_ExitWithError1("Impossible de créer la fénêtre et le rendu");
	
	
/*---------------------------------------------------------------------------------------------*/


	SDL_bool program_launched = SDL_TRUE;
	//unsigned int frame_limit = 0;
	
	/*-----*/
	
	// 60 FPS (1000/60)
		
	/*frame_limit = SDL_GetTicks() + FPS_LIMIT;
	SDL_LimitFPS(frame_limit); // Délai pour limiter à 60 fps
	frame_limit = SDL_GetTicks() + FPS_LIMIT;
	
	printf("Temps écoulé : %d ms\n",ticks);*/
		
		
	/*-----*/
	
	while (program_launched) {
	
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
		
			switch(event.type) {
				
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					
					case SDLK_b:
						printf("Vous avez appuyer sur B\n");
						int i; 
						SDL_Rect rectangle;
						
						
						// Touches Blanches
						
						
						int N_keys = 52;
						int w_key = 15;
						int h_key = 100;
						i = 0;
						
						if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
							SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
						
						//if (SDL_RenderDrawLine(renderer, 50, 50, 800, 500) != 0) 
								//SDL_ExitWithError2("Impossible de dessiner une ligne", window, renderer);
						
						for (i = 0; i < N_keys; i++) {
						
							rectangle.x = 1 + i * (w_key + 1);
							rectangle.y = 450;
							rectangle.w = w_key;
							rectangle.h = h_key;
							
						
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
						}
						
						
						// Touches Noires
						
						
						int w_keyp = 12;
						int h_keyp = 65;
						i = 3;
						
						if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
							SDL_ExitWithError2("Impossible de charger la couleur pour le rendu", window, renderer);
						
						if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
							SDL_ExitWithError2("Chargement couleur rendu impossible", window, renderer);

						// Seule


						rectangle.x = 1 + 1 * (w_key + 1) - 2*w_key/5;
						rectangle.y = 450;
						rectangle.w = w_keyp;
						rectangle.h = h_keyp;
						
						
						if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
						    		SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
						    		
						    
						while (i < N_keys) {
						
						
							// Paires
							
							
							rectangle.x = 1 + i * (w_key + 1) - 2*w_key/5;
							rectangle.y = 450;
							rectangle.w = w_keyp;
							rectangle.h = h_keyp;
							
						
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
							rectangle.x = 1 + (i + 1) * (w_key + 1) - 3*w_key/10;
							rectangle.y = 450;
							rectangle.w = w_keyp;
							rectangle.h = h_keyp;
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
							
							// Triplets
							
							
							rectangle.x = 1 + (i + 3) * (w_key + 1) - w_key/2;
							rectangle.y = 450;
							rectangle.w = w_keyp;
							rectangle.h = h_keyp;
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
							rectangle.x = 1 + (i + 4) * (w_key + 1) - w_key/3;
							rectangle.y = 450;
							rectangle.w = w_keyp;
							rectangle.h = h_keyp;
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
							rectangle.x = 1 + (i + 5) * (w_key + 1) - w_key/4;
							rectangle.y = 450;
							rectangle.w = w_keyp;
							rectangle.h = h_keyp;
							
							if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
								SDL_ExitWithError2("Impossible de dessiner un rectangle", window, renderer);
							
							i = i + 7;
							
						}
						
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
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
/*----- Fin -----------------------------------------------------------------------------------*/
	
	
	printf("----------\n\n");
	printf("Voici le piano\n\n");
	printf("----------\n\n");
	
	return(EXIT_SUCCESS);
	
}

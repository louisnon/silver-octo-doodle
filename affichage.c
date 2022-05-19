/* Louis Colette Groupe 8 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define SCREENWIDTH 833
#define SCREENHEIGHT 600

// gcc -Wall -Wfatal-errors affichage.c $(sdl2-config --cflags --libs)


/*----- Fonction annexes d'erreur -------------------------------------------------------------*/


void SDL_ExitWithError1(const char* message) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}

void SDL_ExitWithError2(const char* message, SDL_Window* window) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}

void SDL_ExitWithError3(const char* message, SDL_Window* window, SDL_Renderer* renderer) {

	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();			
	exit(EXIT_FAILURE);
	
}


/*----- Fin Fonction annexes d'erreur ---------------------------------------------------------*/
	

void affichage() {


	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	
/*----- Lancement SDL ------------------------------------------------------------------------*/
	
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		SDL_ExitWithError1("Initialisation SDL échouée");
	

/*----- Création fenêtre ---------------------------------------------------------------------*/
	
	
	window = SDL_CreateWindow("Première fenêtre SDL 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, 0);
	
	if (window == NULL) 
		SDL_ExitWithError1("Création fenêtre échouée");
	
	
/*----- Création rendu -----------------------------------------------------------------------*/


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	
	if (renderer == NULL) 
		SDL_ExitWithError2("Création rendu échouée", window);
	
	
/*----- Création contenu ---------------------------------------------------------------------*/
	
	
	/*if (SDL_RenderDrawPoint(renderer, 100, 450) != 0) {
	
		SDL_Log("ERREUR : Impossible de dessiner un point > %s\n", SDL_GetError());
		return(EXIT_FAILURE);
		//SDL_ExitWithError("Impossible de dessiner un point");
	
	}*/

	
	int i; 
	SDL_Rect rectangle;
	
	
	// Touches Blanches
	
	
	int N_keys = 52;
	int w_key = 15;
	int h_key = 100;
	i = 0;
	
	if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
		SDL_ExitWithError3("Impossible de charger la couleur pour le rendu", window, renderer);
	
	//if (SDL_RenderDrawLine(renderer, 50, 50, 800, 500) != 0) 
			//SDL_ExitWithError3("Impossible de dessiner une ligne", window, renderer);
	
	for (i = 0; i < N_keys; i++) {
	
		rectangle.x = 1 + i * (w_key + 1);
		rectangle.y = 450;
		rectangle.w = w_key;
		rectangle.h = h_key;
		
	
		if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
	}
	
	
	// Touches Noires
	
	
	int w_keyp = 12;
	int h_keyp = 65;
	i = 3;
	
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
		SDL_ExitWithError3("Impossible de charger la couleur pour le rendu", window, renderer);
	
	    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) 
        SDL_ExitWithError3("Chargement couleur rendu impossible", window, renderer);

        // Seule


        rectangle.x = 1 + 1 * (w_key + 1) - 2*w_key/5;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        
        
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            		SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
            		
            
	while (i < N_keys) {
	
	
		// Paires
		
		
		rectangle.x = 1 + i * (w_key + 1) - 2*w_key/5;
		rectangle.y = 450;
		rectangle.w = w_keyp;
		rectangle.h = h_keyp;
		
	
		if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
		rectangle.x = 1 + (i + 1) * (w_key + 1) - 3*w_key/10;
		rectangle.y = 450;
		rectangle.w = w_keyp;
		rectangle.h = h_keyp;
		
		if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
		
		// Triplets
		
		
		rectangle.x = 1 + (i + 3) * (w_key + 1) - w_key/2;
		rectangle.y = 450;
		rectangle.w = w_keyp;
		rectangle.h = h_keyp;
		
		if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
		rectangle.x = 1 + (i + 4) * (w_key + 1) - w_key/3;
		rectangle.y = 450;
		rectangle.w = w_keyp;
		rectangle.h = h_keyp;
		
		if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
		rectangle.x = 1 + (i + 5) * (w_key + 1) - w_key/4;
		rectangle.y = 450;
		rectangle.w = w_keyp;
		rectangle.h = h_keyp;
		
		if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
		i = i + 7;
		
	}
	
	// Liseret Rouge
	
	
	if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)  	 	
		SDL_ExitWithError3("Impossible de charger la couleur pour le rendu", window, renderer);
	
	rectangle.x = 1;
	rectangle.y = 449;
	rectangle.w = SCREENWIDTH;
	rectangle.h = 1;
	
	if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
		SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
	
	
	// Liseret Noir
	

	if (SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE) != 0) 			SDL_ExitWithError3("Impossible de charger la couleur pour le rendu", window, renderer);
		
	rectangle.x = 1;
	rectangle.y = 447;
	rectangle.w = SCREENWIDTH;
	rectangle.h = 2;
	
	if (SDL_RenderFillRect(renderer, &rectangle) != 0) 					 			SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
		
	
	// Liseret Gris
	
	
	if (SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE) != 0) 			SDL_ExitWithError3("Impossible de charger la couleur pour le rendu", window, renderer);
		
	rectangle.x = 1;
	rectangle.y = 445;
	rectangle.w = SCREENWIDTH;
	rectangle.h = 2;
	
	if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
		SDL_ExitWithError3("Impossible de dessiner un rectangle", window, renderer);
	

/*----- Interlude ----------------------------------------------------------------------------*/
	
	
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	
	
/*----- Libérations --------------------------------------------------------------------------*/
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
/*----- Fin ----------------------------------------------------------------------------------*/
	
	
	printf("----------\n\n");
	printf("Voici le piano\n\n");
	printf("----------\n\n");


}
	


	
	
	

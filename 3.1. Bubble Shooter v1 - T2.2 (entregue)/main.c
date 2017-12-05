/*
 * T2.2 - Comp I - 2017.2
 * 2017/11/01
 *
 * Alunos:
 * Lucas Camilo da Cunha		DRE: 117212300
 * Rafael de Aguiar Ferreira	DRE: 117196643
 * Ryan Oliveira Braz			DRE: 117205468
 * 
 * main.c
 *
 * Este programa exibe uma imagem no centro inferior da tela.
 * Ela se move com âgulo de 45º ou 135º, decidido aleatoriamente,
 * assim que é detectado o clique esquerdo do mouse.
 * Ao colidir com uma parede, a imagem irá ser refletida, até
 * chegar ao teto, e parar.
 */
 
/*Using SDL, SDL_image, standard IO, and strings*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
 * Constants
 */

/*Screen dimension constants*/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int false = 0;
const int true = 1;

const int IMAGE_WIDTH = 61;
const int IMAGE_HEIGHT = 61;

typedef struct _NPC  {
	int posX;
	int posY;
	int stepX;
	int stepY;
	SDL_Surface* image;
	int imgW;
	int imgH;
} NPC;

/*
 * Global Variables
 */

/*The window we'll be rendering to*/
SDL_Window* gWindow = NULL;

/*The imagem character*/
NPC ball;
  
/*The surface contained by the window*/
SDL_Surface* gScreenSurface = NULL;

/*Current displayed PNG image*/
SDL_Surface* gJPGSurface = NULL;

/*
 * function prototypes
 */

/*Starts up SDL and creates window*/
int init();

/*Loads media*/
int loadMedia();

/*Frees media and shuts down SDL*/
void closing();

/*Loads individual image*/
SDL_Surface* loadSurface( char *path );

/*Create NPC*/
NPC createNPC( int posX, int posY, int stepX, int stepY, SDL_Surface *image);

/*Move NPC*/
void moveNPC(NPC *p);


int main( int argc, char* args[] ) {
	SDL_Rect srcRect, dstRect;
	SDL_Event e;/*Event handler*/
	int quit = false;/*Main loop flag*/

	int pri=1; /* SÓ O PRIMEIRO CLIQUE TEM VALIDADE */

	/*Start up SDL and create window*/
	if( !init() ) {
		printf( "Failed to initialize!\n" );
		return 1;
	}
	
	/*Load media*/
	if( !loadMedia() ) {
		printf( "Failed to load media!\n" );
		return 2;
	}
	/*Create NPC*/
	ball = createNPC(
					(SCREEN_WIDTH - IMAGE_WIDTH)/2, 
					(SCREEN_HEIGHT - IMAGE_HEIGHT), 
					0, 
					0, 
					gJPGSurface);
	
   

	/*While application is running*/
	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			switch (e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(e.button.button == SDL_BUTTON_LEFT)
						if(pri){
							ball.stepX = rand() % 2 ? -1: 1;
							ball.stepY = rand() % 2 ? -1: 1;
							pri = 0;
						}
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) {
						quit = true;
					}
					break;
			}
		}
			
		/*Fill the surface white*/
		SDL_FillRect( gScreenSurface, NULL, 
							  SDL_MapRGB( gScreenSurface->format, 
							  0xFF, 0xFF, 0xFF ) );

		moveNPC(&ball);

		srcRect.x = 0; srcRect.y = 0;
		srcRect.w = IMAGE_WIDTH;
		srcRect.h = IMAGE_HEIGHT;
		dstRect.x = ball.posX;
		dstRect.y = ball.posY;
			
		if( SDL_BlitSurface( ball.image, &srcRect, 
									 gScreenSurface, &dstRect ) < 0 ) {
			printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
			quit = true;
		}
			
		/*Update the surface*/
		SDL_UpdateWindowSurface( gWindow );
				
		/* Not so good solution, depends on your computer*/
		SDL_Delay(5);
	}

	/*Free resources and closing SDL*/
	closing();

	return 0;
}


void moveNPC(NPC *p) {
	p->posX += p->stepX;
	p->posY += p->stepY;
	
	if ( (p->posX + IMAGE_WIDTH > SCREEN_WIDTH) ||
		 (p->posX < 0) ) {
		p->stepX = -p->stepX;
		p->posX += p->stepX; 
	}
	if (p->posY + IMAGE_HEIGHT > SCREEN_HEIGHT) {
		p->stepY = -p->stepY;
		p->posY += p->stepY;
	}
	if (p->posY < 0) {
		p->stepX = 0;
		p->stepY = 0;
		/*main(0, NULL);*/
	}
}


/*Create NPC*/
NPC createNPC( int posX, int posY, int stepX, int stepY, 
			   SDL_Surface *image) {
	NPC p;
	
	p.posX = posX;
	p.posY = posY;
	p.stepX = stepX;
	p.stepY = stepY;
	p.image = image;
	return p;
}

int init() {
	/*Initialization flag*/
	int success = true;

	srand(time(NULL));

	/*Initialize SDL*/
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else {
		/*Create window*/
		gWindow = SDL_CreateWindow( "SDL Tutorial: 06_moving_images", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else {
			/*Initialize JPG and PNG loading */
			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = false;
			}
			else {
				/*Get window surface*/
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}
	}

   

	return success;
}

int loadMedia() {
	/*Loading success flag*/
	int success = true;
	/*uint32_t colorKey;*/
	
	/*Load PNG surface*/
	gJPGSurface = loadSurface( "./circle.jpeg" );
	if( gJPGSurface == NULL ) {
		printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
		success = false;
	} 
	return success;
}

void closing() {
	/*Free loaded image*/
	SDL_FreeSurface( gJPGSurface );
	gJPGSurface = NULL;

	/*Destroy window*/
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	/*Quit SDL subsystems*/
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( char *path ) {
	/*The final optimized image*/
	SDL_Surface* optimizedSurface = NULL;

	/*Load image at specified path*/
	SDL_Surface* loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else {
		/*Convert surface to screen format*/
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL ) {
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		/*Get rid of old loaded surface*/
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}
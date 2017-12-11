#include "../1.dados.h"

#include "2.partida.h"
#include "3.partida.h"

Surface botaoMenu;
Surface botaoExit;

void printBola(byte cor, int x, int y);
// Tamanho Hud: (648,75)
//Tamanho Menu: (x é 5 de distancia do exit [checar propriedades])
//Tamanho Exit: (54 por 54)
//Tamanho VidaCover (91,19) (inicia em: 193,422)

bool desenhandoPartida = false;

void partidaView(){
	desenhandoPartida = true;
	
	//Fill the surface white
	SDL_FillRect( screenSurface, NULL,
						  SDL_MapRGB( screenSurface->format,
						  0xFF, 0xFF, 0xFF ) );

	printSurface(screenSurface, partidaBg[bgIndex], 0, 0, 648, 480);
	//printf("%d",bgIndex);

	printSurface(screenSurface, partidaHud, 0, 405, 648, 75);

	printSurface(screenSurface, botaoExit, 594, 426, 54, 54);

	printSurface(screenSurface, botaoMenu, 535, 426, 50, 24);

	//println("%s",scoreString);

	//msgPontos= TTF_RenderText_Solid( fonte, scoreString, ttfCor);
	//printSurface(screenSurface,msgPontos,0,0,tam.tela.x/2,tam.tela.y/2);
/*
	//Fill the surface white
	SDL_FillRect( gScreenSurface, NULL,
							SDL_MapRGB( gScreenSurface->format,
							fundo.R, fundo.G, fundo.B ));
*/

	for(int y=0;y<linhastotal;y++)
		for(int x=0;x<colunas;x++)
			if(existe(x,y))
				printBola(matriz[y][x].cor, matriz[y][x].x, matriz[y][x].y);
	if(!estourando)
		printBola(tiro.cor, tiro.x, tiro.y);

	printScore();
	//Update the surface
	SDL_UpdateWindowSurface( janela );
	desenhandoPartida = false;
}

void printBola(byte cor, int x, int y){
	printSurface(screenSurface, sprites[cor], x, y, tam.bola.x, tam.bola.y);
}

void printScore(void){
	fonte = TTF_OpenFont("./font/fonteFolks.ttf",20);

	SDL_Rect msgRect;

	ttfCor.r=244; ttfCor.g=244; ttfCor.b=0;

	msgRect.x = tam.tela.x*3/4-20;
	msgRect.y = tam.tela.y-30;
	msgRect.w = 150;
	msgRect.h = 40;

	msgPontos = TTF_RenderText_Solid( fonte, scoreString, ttfCor);
	SDL_BlitSurface(msgPontos, NULL, screenSurface, &msgRect);

	//printSurface(screenSurface,msgPontos,0,0,tam.tela.x/2,tam.tela.y/2);
	SDL_FreeSurface(msgPontos);
	TTF_CloseFont(fonte);
}

/* ETAPA DE INICIALIZAÇÃO DO **CONTROLE** */
bool carregarMidia(void){//iu
}
bool iniciarSDL(void){//iu
}
void iniciarInterface(void){//iu
}

/* ETAPA DE MECÂNICA */
void moverSeta(){
}

/* ETAPA DE FINALIZAÇÃO */

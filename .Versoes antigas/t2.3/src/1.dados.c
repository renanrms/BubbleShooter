#include "1.dados.h"

/* GLOBAIS */
const Coordenadas campo = {colunas, linhas}, npc = {37, 37}, tela = {/*629*/647, 480};//tamanhos
Coordenadas velocidade;
Bola gradeBola[linhas][colunas];
Tiro tiro;
SDL_Surface* gcolorSurface[6];

/* Global Variables */
SDL_Window* gWindow = NULL; //The window we'll be rendering to
//SDL_Surface* imagem; //The imagem character
SDL_Surface* gScreenSurface = NULL; //The surface contained by the window
SDL_Surface* gJPGSurface = NULL; //Current displayed PNG image

bool quit = false; //Main loop flag

bool iniciarJogo(void){//iniciar globais; preparar jogo
}

/*
bool insere(Bola b, Coordenadas pos){
}
bool remover(Bola b, Coordenadas pos){
}
*/

int getLinha(Bola b){
	return (int) b.x/npc.x;
}

int getColuna(Bola b, int linha){
	return (int) (linha%2 ? b.y-npc.y/2 : b.y)/npc.y;
}
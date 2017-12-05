#ifndef CABECALHO
	#define CABECALHO

	/* LIBS EXTERNAS */
	#include <stdio.h>
	#include <string.h>
	#include <time.h>
	#include <math.h>

	/* LIBS PERSONALIZADAS */
	#include "../lib/lib.h"
	#include "../lib/terminal.h"
	#include "../lib/iu.h"
	#include "../lib/debug.h"

	/* CONSTANTES */
	#define linhas 15
	#define colunas 30
	#define ncores 6

	/* Global Variables */
	extern Janela janela; //The window we'll be rendering to
	extern Surface screenSurface; //The surface contained by the window
	extern Surface gJPGSurface; //Current displayed PNG image
	extern Surface gcolorSurface[ncores]; //Vetor de imagens :^)

	extern const Coordenadas campo;//tamanhos

	/* ERROS */
	//#define
#endif

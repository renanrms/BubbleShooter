/*#ifndef CABECALHO
	#include "0.cabecalho.h"
	
#else
*/


#include "0.cabecalho.h"
#ifndef DADOS //evitar inclusões cíclicas ("guarda de cabeçalho")
	#define DADOS
//#ifndef TIPOS //evitar inclusões cíclicas ("guarda de cabeçalho")
//	#define TIPOS

	#include "1.dados.h"
	
	/* TIPOS */
	typedef struct{
		int x,y;
	} Coordenadas;

	typedef struct _Bola{
		char cor;
		struct _Bola *vizinhos[6];
		int x,y;
		bool morreu;
	} Bola;

	typedef struct{
		char cor;
		float x,y;
		struct{
			float x,y;
		}vel;
	} Tiro;

//#endif

//#ifndef DADOS //evitar inclusões cíclicas ("guarda de cabeçalho")
//	#define DADOS

	/* PROTÓTIPOS */
	
	bool iniciarJogo(void);//iniciar globais; preparar jogo

	bool insere(Bola b, Coordenadas pos);
	bool remover(Bola b, Coordenadas pos);

	int getLinha(Bola b);
	int getColuna(Bola b, int linha);

#endif
//#endif

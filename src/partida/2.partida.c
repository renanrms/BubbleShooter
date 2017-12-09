#include "../1.dados.h"
#include "../1.mecanica.h"

#include "2.partida.h"
#include "3.partida.h"

#include "../menu/2.menu.h"
#include "../3.debug.h"

/*
Este arquivo contém a parte de Controle do programa mais relacionada à lógica do jogo.
*/

/*

void jogo(void){
	bool acabou = false;
	while(!acabou){
		while(!iuf.mouse.clicou()){
			while(!iuf.mouse.moveu());
			moverSeta();
		}
		Coordenadas pos = atirar();//"atirar()" retorna as Coordenadas da Bola que foi lançada
		if(match(pos)){//verifica, recursivamente, se há mais de 2 bolas da mesma cor que "pos"
			verifica(pos);//marca, recursivamente, como "morreu" todas as bolas
			explodir(pos);//explode todas as bolas marcadas, e filhas órfãs
		}
	}
}

Coordenadas atirar(){
	bool desalojada=true;
	Coordenadas dest;//destino

	while(desalojada){
		move();
		dest.x = getColuna(tiro, dest.y = getLinha(tiro));

		if(habitavel(dest)){//verifica se, para essa casa, há um pai (acima) na estrutura)
			while(tiro.y > npc.y){
				move(); pausa();
			}
			insere(tiro, dest);
			desalojada = false;
		}
		else pausa();
	}
	return dest;
}

bool habitavel(Coordenadas pos){
	if(l) //verifica se há pais disponíveis
	else //guardar na primeira linha msm
}

bool match(Coordenadas bola){
}

void move(void){
}

*/

voidvoid partidaLoop;
int x, y;

void partida(void){

	on.screenRefresh = partidaView;
	on.click = partidaOnClick;
	on.mouseMove = partidaOnMouseMove;

	botaoExit = partidaExit0;
	botaoMenu = partidaMenu0;

	//println("%d",sortear());

	iniciarJogo();

	//TODO debug
	exibeMatriz(
		lambda(
			char*, (Bola b) {
				char* saida;
				saida = malloc(sizeof(char)*10);

				/* COORDENADAS NA TELA */
				//sprintf(saida,"%d,%d",b.x,b.y);

				/* COORDENADAS NA MATRIZ (getLinha/getColuna) */
				if(existe(getLinha(b.y),getColuna(b.x,b.y)))
				sprintf(saida,"%d,%d",getColuna(b.x,b.y),getLinha(b.y));

				/* COR */
				//sprintf(saida,"%d",b.cor);

				/* EXISTE */
				//sprintf(saida,"%d",b.existe);

				return saida;
			}
		)
	);

	//TODO debug
	x = getColuna(tiro.x,tiro.y);
	y = getLinha(tiro.y);
	printnl();
	println("%d,%d",x,y);
	printnl();

	//printint((int)obter(16,8));
	//printnl();


	/*
	while(true){
		println("%d,%d",x,y);
		while(x == getColuna(tiro.x,tiro.y) && y == getLinha(tiro.y));
	}
	*/

	//While application is running
	on.run = partidaLoop;
}

Coordenadas destino = {-1,-1};
void partidaLoop(void){
	moveNPC();
	//TODO debug
	if(x != getColuna(tiro.x,tiro.y) || y != getLinha(tiro.y)){
		x = getColuna(tiro.x,tiro.y);
		y = getLinha(tiro.y);
	}



	//printnl();
	//println("%d,%d",x,y);

	if(habitavel(x,y)){
		if(colisao(&matriz[y][x-1],&tiro) ||
			 colisao(&matriz[y][x+1],&tiro) ||
			 colisao(&matriz[y-1][x],&tiro) ||
			 colisao(&matriz[y+1][x],&tiro)){
			//printf("%d %d %d\n%d %d %d\n%d %d %d\n",matriz[y-1][x-1].cor,matriz[y-1][x].cor,matriz[y-1][x+1].cor,matriz[y][x-1].cor,matriz[y][x].cor,matriz[y][x+1].cor,matriz[y+1][x-1].cor,matriz[y+1][x].cor,matriz[y+1][x+1].cor);
			insere(x,y,tiro.cor);
			//printf("%d %d %d\n%d %d %d\n%d %d %d\n",matriz[y-1][x-1].cor,matriz[y-1][x].cor,matriz[y-1][x+1].cor,matriz[y][x-1].cor,matriz[y][x].cor,matriz[y][x+1].cor,matriz[y+1][x-1].cor,matriz[y+1][x].cor,matriz[y+1][x+1].cor);
			//println("a");
			iniciarTiro();
			on.click = partidaOnClick;
		}
		if(x%2){
			if(colisao(&matriz[y-1][x+1],&tiro) ||
				 colisao(&matriz[y+1][x+1],&tiro)){
			//	printf("%d %d %d\n%d %d %d\n%d %d %d\n",matriz[y-1][x-1].cor,matriz[y-1][x].cor,matriz[y-1][x+1].cor,matriz[y][x-1].cor,matriz[y][x].cor,matriz[y][x+1].cor,matriz[y+1][x-1].cor,matriz[y+1][x].cor,matriz[y+1][x+1].cor);
				insere(x,y,tiro.cor);
				//printf("%d %d %d\n%d %d %d\n%d %d %d\n",matriz[y-1][x-1].cor,matriz[y-1][x].cor,matriz[y-1][x+1].cor,matriz[y][x-1].cor,matriz[y][x].cor,matriz[y][x+1].cor,matriz[y+1][x-1].cor,matriz[y+1][x].cor,matriz[y+1][x+1].cor);
				//println("b");
				iniciarTiro();
				on.click = partidaOnClick;
			}
		}
		else{
			if(colisao(&matriz[y-1][x-1],&tiro) ||
				 colisao(&matriz[y+1][x-1],&tiro)){
				//printf("%d %d %d\n%d %d %d\n%d %d %d\n",matriz[y-1][x-1].cor,matriz[y-1][x].cor,matriz[y-1][x+1].cor,matriz[y][x-1].cor,matriz[y][x].cor,matriz[y][x+1].cor,matriz[y+1][x-1].cor,matriz[y+1][x].cor,matriz[y+1][x+1].cor);
				insere(x,y,tiro.cor);
				//printf("%d %d %d\n%d %d %d\n%d %d %d\n",matriz[y-1][x-1].cor,matriz[y-1][x].cor,matriz[y-1][x+1].cor,matriz[y][x-1].cor,matriz[y][x].cor,matriz[y][x+1].cor,matriz[y+1][x-1].cor,matriz[y+1][x].cor,matriz[y+1][x+1].cor);
				//println("c");
				iniciarTiro();
				on.click = partidaOnClick;
			}
		}
	}
	else if(!((int)tiro.y%tam.bola.y) || !((int)tiro.x%tam.bola.x)) println("nao habitavel");
			//println("a");

			//Bola* b = obter(getColuna(tiro.x,tiro.y), getLinha(tiro.y));
			//println("b");

/*
			if(destino.x != -1 && existe(x,y)){//se finalmente tem abrigo, mas já saiu dele
				insere(destino.x,destino.y,tiro.cor);

			/*
			Bola* k = obter(destino.x,destino.y);
			if(k){
				println("dentro da matriz");
				if(k->existe)
					println("existe");
			}
			println("parecer do existe(): %s",existe(x,y)?"sim":"não");
			*/
/*
			destino.x = -1;
			destino.y = -1;
			iniciarTiro();
			on.click = partidaOnClick;

			exibeMatriz(
				lambda(
					char*, (Bola b) {
						char* saida;
						saida = malloc(sizeof(char)*10);

						/* COORDENADAS NA TELA */
						//sprintf(saida,"%d,%d",b.x,b.y);

						/* COORDENADAS NA MATRIZ (getLinha/getColuna) */
						//sprintf(saida,"%d,%d",getColuna(b.x,b.y),getLinha(b.y));

						/* COR */
						//sprintf(saida,"%d",b.cor);

						/* EXISTE */
	/*					sprintf(saida,"%d",b.existe);

						return saida;
					}
				)
			);
		}


		else if(habitavel(x,y)){
			//println("habitável");

			//if(destino.x == -1){//se a bola ainda está desabrigada, os problemas acabaram!
				destino.x = x;
				destino.y = y;
			//}

			/*oi();
			Bola n = *b;
			oi();
			distancia(n,tiro);
			*/

			/*
			if(colidiu(1,y) || colidiu(x-1,y) || colidiu(x,y+1) || colidiu(x,y-1)){
				insere(x,y,tiro.cor);
				//oi();
			}

			if(x%2){
				if(colidiu(x+1,y+1) || colidiu(x,y-1)){
					insere(x,y,tiro.cor);
					//oi();
				}
			}
			else
				if(colidiu(x-1,y+1) || colidiu(x,y-1)){
					insere(x,y,tiro.cor);
					//oi();
				}

			*/

			/*||existe(x-1,y))
				return true;
			if(existe(x,y+1)||existe(x,y-1))
				return true;
			if(x%2){
				if(existe(x+1,y+1)||existe(x,y-1))
					return true;
			}
			else{
				if(existe(x-1,y+1)||existe(x,y-1))
					return true;
			}*/

			//sleep(3);
	/*	}
		else
			println("não-habitável");

		/*
		if(existe(b)){

			//println("c");
			//println("Cor: %d",b->cor);

			char cor[10];

			switch (b->cor){
				case 0:
					sprintf(cor,"%s","blue");
					break;
				case 1:
					sprintf(cor,"%s","red");
					break;
				case 2:
					sprintf(cor,"%s","cian");
					break;
				case 3:
					sprintf(cor,"%s","green");
					break;
				case 4:
					sprintf(cor,"%s","pink");
					break;
				case 5:
					sprintf(cor,"%s","yellow");
					break;
			}

			println("Cor: %s",cor);

			//sleep(3);
			char c;
			scanf("%c",&c);
			//println("d");
		}
		*/
//	}

	if(on.run == menu) return;
	else SDL_Delay(5);//Not so good solution, depends on your computer
}

bool iniciarJogo(void){//iniciar globais; preparar jogo
	preencher();

	//Create NPC
	iniciarTiro();
}

/* Create NPC */
void iniciarTiro(void){
	tiro.x = (tam.tela.x - tam.bola.x)/2;
	tiro.y = tam.tela.y - tam.bola.y;
	tiro.vel.x = 0;
	tiro.vel.y = 0;
	tiro.cor = sortear();
}

void moveNPC() {

	//printf("%d, %d\n",tiro.vel.x,tiro.vel.y);

	tiro.x += tiro.vel.x;
	tiro.y += tiro.vel.y;

	if ( (tiro.x + tam.bola.x > tam.tela.x) ||
		 (tiro.x < 0) ) {
		tiro.vel.x = -tiro.vel.x;
		tiro.x += tiro.vel.x;
	}
	if (tiro.y + tam.bola.y > tam.tela.y) {
		tiro.vel.y = -tiro.vel.y;
		tiro.y += tiro.vel.y;
	}

	if (tiro.y < 0) {
		/*tiro.vel.x = 0;
		tiro.vel.y = 0;*/
		//main(0, NULL);
		quit = true;
	}
}

void partidaOnClick(){
	//println("Clicou!");
	Coordenadas pos = getMousePos();
	//printf("\n%d,%d\n",x,y);
	if(pos.x>=594 && pos.x<=648 && pos.y>=426 && pos.y<=480){
		on.stop();
		return;
	}
	else if(pos.x>=535 && pos.x<=589 && pos.y>=426 && pos.y<=450){
		on.run = menu;
		return;
	}
	if(pos.y>419)pos.y=419;
	pos.x -= (tam.tela.x)/2;
	pos.y -= (tam.tela.y)-((tam.bola.y)/2);

	double d = sqrt( pow(pos.x,2) + pow(pos.y,2) );

	tiro.vel.x = pos.x/d;
	tiro.vel.y = pos.y/d;

	on.click = NULL;//TODO experimenta tirar essa linha
}

void partidaOnMouseMove(Coordenadas pos){
	//135,85 257,200
	//54,54 594,426

	if(pos.x>=594 && pos.x<=648 && pos.y>=426 && pos.y<=480){
		botaoExit = partidaExit1;
	}
	else if(pos.x>=535 && pos.x<=589 && pos.y>=426 && pos.y<=450){
		botaoMenu = partidaMenu1;
	}
	else{
		botaoExit = partidaExit0;
		botaoMenu = partidaMenu0;
	}
	return;
}
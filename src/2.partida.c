#include "1.dados.h"
#include "1.mecanica.h"

#include "2.partida.h"
#include "3.partida.h"

#include "3.debug.h"

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

void partida(void){

	on.screenRefresh = partidaView;
	on.click = partidaOnClick;

	//println("%d",sortear());

	iniciarJogo();
	
	
	exibeMatriz(
		lambda(
			char*, (Bola b) {
				char* saida;
				saida = malloc(sizeof(char)*10);
				
				/* COORDENADAS NA TELA */
				sprintf(saida,"%d,%d",b.x,b.y);
				
				/* COORDENADAS NA MATRIZ (getLinha/getColuna) */
				//sprintf(saida,"%d,%d",getColuna(b.x,b.y),getLinha(b.y));
				
				/* COR */
				//sprintf(saida,"%d",b.cor);
				
				/* EXISTE */
				//sprintf(saida,"%d",b.existe);
			
				return saida;
			}
		)
	);
	
	//TODO debug
	int x = getColuna(tiro.x,tiro.y), y = getLinha(tiro.y);
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
	while( !quit ) {
		moveNPC();
	
		//TODO debug
		if(x != getColuna(tiro.x,tiro.y) || y != getLinha(tiro.y)){
			x = getColuna(tiro.x,tiro.y);
			y = getLinha(tiro.y);
			
			printnl();
			println("%d,%d",x,y);
			
			//println("a");
			
			Bola* b = obter(getColuna(tiro.x,tiro.y), getLinha(tiro.y));
			//println("b");
			if(b){
				//println("%d %sexiste em %d,%d", b, b->existe?"":"não ",b->x,b->y);
				if(b->existe){
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
					
					sleep(3);
					//println("d");
				}
			}
		}
		
		//Not so good solution, depends on your computer
		SDL_Delay(5);
	}
}

void partidaOnClick(){
	//println("Clicou!");
	int x, y;
	SDL_GetMouseState(&x,&y);
	//printf("\n%d,%d\n",x,y);

	x -= (tam.tela.x)/2;
	y -= (tam.tela.y)-((tam.bola.y)/2);

	double d = sqrt( pow(x,2) + pow(y,2) );

	tiro.vel.x = x/d;
	tiro.vel.y = y/d;

	on.click = NULL;//TODO experimenta tirar essa linha
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

/* Create NPC */
void createNPC( int x, int y, int velx, int vely, byte cor) {
	tiro.x = x;
	tiro.y = y;
	tiro.vel.x = velx;
	tiro.vel.y = vely;
	tiro.cor = cor;
}

bool iniciarJogo(void){//iniciar globais; preparar jogo
	preencher();

	//Create NPC
	createNPC(
		(tam.tela.x - tam.bola.x)/2,
		(tam.tela.y - tam.bola.y),
		0,
		0,
		sortear()
	);
}

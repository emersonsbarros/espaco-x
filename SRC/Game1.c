#include <allegro.h>
#include <time.h>

void init();
void deinit();
void menu();
void options();
void atirar();
void colisao();
void equacao();
void perdeu();
void explosao();
void explosao2();
void escolha();
void inimigos();
void abertura();
void lazer();
void expl();
void winner();
void loser();
void escnave();
BITMAP *buffer;                                     				//Define o ponteiro "buffer"
BITMAP *background[10];												//Define o ponteiro "background"
BITMAP *nave[3];													//Define o ponteiro "nave"
BITMAP *inimigo[15];                                    			//Define o ponteiro "inimigo"
BITMAP *bomba[16];                                    				//Define o ponteiro "explosao"
int xnave[] = {550, 490, 570};
int ynave[] = {500, 500, 500};
int back = 0;                                                       //Variavel que define qual background estará na tela
int ini = 1;                                            			//IMPORTANTE: VARIAVEL QUE DEFINE QUAL NAVE INIMIGA PODE SER ACERTADA
int a = 0, b = 0, c = 0;
int score = 0;
int e = 0;                                                          //Variavel que define qual nave foi escolhida
int p = 10;
float nivel = 1.0;
float xini = 15.0, yini = 40.0;


typedef struct _TIRO{
    int px;
    int py;
    int vx;
    int vy;
    int ativo;
    int vida;
} TIRO;

TIRO tiro;

int main() {

	init();
	equacao();
	abertura();
	
	clock_t tempo;
   	float FPS = 15.0;//Limitadores de FPS
   	tempo = clock();
	menu();
	buffer = create_bitmap(1280,720);                   			//O Buffer cria um Bitmap de 1280x720
	background[0] = load_bitmap("background.bmp", NULL);   			//O background recebe a imagem
	background[1] = load_bitmap("background1.bmp", NULL);   		//O background recebe a imagem
	background[2] = load_bitmap("background2.bmp", NULL);   		//O background recebe a imagem
	background[3] = load_bitmap("background3.bmp", NULL);   		//O background recebe a imagem
	background[4] = load_bitmap("background4.bmp", NULL);   		//O background recebe a imagem
	background[5] = load_bitmap("background5.bmp", NULL);   		//O background recebe a imagem
	background[6] = load_bitmap("background6.bmp", NULL);   		//O background recebe a imagem
	background[7] = load_bitmap("background7.bmp", NULL);   		//O background recebe a imagem
	
	//Iniciando Background
    draw_sprite(screen, background[back], 0, 0);          			//Coloca a imagem na tela
    draw_sprite(buffer, background[back], 0, 0);          			//Coloca a imagem na tela

    //Iniciando Nave
    nave[0] = load_bitmap("nave1.bmp", NULL);          				//A Nave recebe a imagem
    nave[1] = load_bitmap("nave2.bmp", NULL);          				//A Nave recebe a imagem
    nave[2] = load_bitmap("nave3.bmp", NULL);          				//A Nave recebe a imagem

	//iniciando inimigos

	inimigo[10] = load_bitmap("Inimigos.bmp", NULL);
    inimigo[11] = load_bitmap("Inimigos1.bmp", NULL);
    inimigo[12] = load_bitmap("Inimigos2.bmp", NULL);
    inimigo[13] = load_bitmap("Inimigos3.bmp", NULL);
	escolha();
	while (!key[KEY_ESC]) {
        //vsync();
		//readkey();                                                //Sem essa função, a tela atualiza sozinha.
		if ( (double)(clock() - tempo) >= 1000/FPS ) {
			if (yini >= ynave[e] - 100){
				perdeu();
			}

	        if (key[KEY_RIGHT])
         	{
				if (e == 0){
					if (xnave[e] < 1140){                          	//Limita até aonde o tanque vai
						xnave[e] += 40;								//Muda a nave de posição
					}
				}
				if (e == 1){
                    	if (xnave[e] < 1100){                       //Limita até aonde o tanque vai
						xnave[e] += 40;								//Muda a nave de posição
					}
				}
				if (e == 2){
					if (xnave[e] < 1190){                          	//Limita até aonde o tanque vai
						xnave[e] += 40;								//Muda a nave de posição
					}
				}
			}
	        if (key[KEY_LEFT])
	        {
                if (e == 0){
					if (xnave[e] > -50){                            //Limita até aonde o tanque vai
					xnave[e] -= 40;                            		//Muda a nave de posição
					}
				}
				if (e == 1){
                	if (xnave[e] > -75){                            //Limita até aonde o tanque vai
					xnave[e] -= 40;                            		//Muda a nave de posição
					}
				}
				if (e == 2){
					if (xnave[e] > -50){                            //Limita até aonde o tanque vai
					xnave[e] -= 40;                            		//Muda a nave de posição
					}
				}
			}
			if (key[KEY_SPACE])
			{
				lazer();
				atirar();
			}

			char txt[15]; sprintf(txt,"x + %d = %d", b, a);			//Inicializa o texto
			char txt2[15]; sprintf(txt2,"Pontos = %d", score);		//Inicializa o texto
			blit(buffer, screen, 0,0,0,0,1280,720);					//Limpa a tela
	       	clear_bitmap(buffer);									//Limpa a tela
			xini = 15.0;
			yini += nivel;

			if (p == 10){
				p++;
			}
			else {
				if (p == 11){
					p++;
				}
				else {
					if (p == 12){
						p++;
					}
					else {
						if (p == 13){
							p = 10;
						}
					}
				}
			}
			draw_sprite(buffer, background[back], 0, 0);			//Coloca a imagem na tela
			draw_sprite(screen, nave[e], xnave[e],ynave[e]);     	//Põe a nave na tela
			textout(screen,font,txt,600,450,makecol(255,0,0));  	//Exibe o texto
			textout(screen,font,txt2,5,5,makecol(255,0,0));  		//Exibe o texto
			draw_sprite(screen, inimigo[p], 15,yini); 				//Põe a nave na tela
	        tempo = clock();
		}
	}

	deinit();
	return 0;

}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1280, 720, 0, 0); //WINDOWSED / FULLSCREEN
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

	/* add other initializations here */
}

void menu(){

    BITMAP *menu[4];                                    			//Define o ponteiro "menu"
    int xpos = 250;
    int ypos = 270;
    int i = 1;
    int j = 2;
    buffer = create_bitmap(1280,720);                   			//O Buffer cria um Bitmap de 1280x720
	background[0] = load_bitmap("background.bmp", NULL);   			//O background recebe a imagem
	background[1] = load_bitmap("background1.bmp", NULL);   		//O background recebe a imagem
	background[2] = load_bitmap("background2.bmp", NULL);   		//O background recebe a imagem
	background[3] = load_bitmap("background3.bmp", NULL);   		//O background recebe a imagem
	background[4] = load_bitmap("background4.bmp", NULL);   		//O background recebe a imagem
	background[5] = load_bitmap("background5.bmp", NULL);   		//O background recebe a imagem
	background[6] = load_bitmap("background6.bmp", NULL);   		//O background recebe a imagem
	background[7] = load_bitmap("background7.bmp", NULL);   		//O background recebe a imagem
	draw_sprite(screen, background[back], 0, 0);          			//Coloca a imagem na tela
    draw_sprite(buffer, background[back], 0, 0);          			//Coloca a imagem na tela

    menu[0] = load_bitmap("mnuNewGame.bmp", NULL);
    menu[1] = load_bitmap("mnuNewGameM.bmp", NULL);
    menu[2] = load_bitmap("mnuOptions.bmp", NULL);
    menu[3] = load_bitmap("mnuOptionsM.bmp", NULL);
    draw_sprite(screen, menu[i], xpos,ypos);
    ypos += 100;
    xpos +=15;
    draw_sprite(screen, menu[j], xpos,ypos);

	while (!key[KEY_ENTER])
	{
		readkey();
        if (key[KEY_UP])
		{
			if(i < 1 && j > 2)
			{
				i++;
				j--;
				xpos = 250;
				ypos = 270;
			    blit(buffer, screen, 0,0,0,0,1280,720);     		//Limpa a tela
	           	clear_bitmap(buffer);                       		//Limpa a tela
	           	draw_sprite(buffer, background[back], 0, 0);      	//Coloca a imagem na tela
				draw_sprite(screen, menu[i], xpos,ypos);
			    ypos += 100;
			    xpos +=15;
			    draw_sprite(screen, menu[j], xpos,ypos);
			}
		}
        if (key[KEY_DOWN])
		{
           	if(i > 0 && j < 3)
			{
				i--;
				j++;
                xpos = 250;
				ypos = 270;
			    blit(buffer, screen, 0,0,0,0,1280,720);     		//Limpa a tela
	           	clear_bitmap(buffer);                       		//Limpa a tela
	           	draw_sprite(buffer, background[back], 0, 0);      	//Coloca a imagem na tela
				draw_sprite(screen, menu[i], xpos,ypos);
			    ypos += 100;
			    xpos +=15;
			    draw_sprite(screen, menu[j], xpos,ypos);
			}
		}
	}
	if (i == 0 && j == 3){
		options();
	}
}



void options(){

    buffer = create_bitmap(1280,720);                   			//O Buffer cria um Bitmap de 1280x720
	draw_sprite(screen, background[back], 0, 0);          			//Coloca a imagem na tela
    draw_sprite(buffer, background[back], 0, 0);          			//Coloca a imagem na tela
    char txt[120][100];
	sprintf(txt[0],"Espaco-X:", NULL);																							//Inicializa o texto
	sprintf(txt[1],"Algumas naves do imperio inimigo te encontraram. O escudo nao permite que voce as destruam, ", NULL);		//Inicializa o texto
	sprintf(txt[2],"mas a unica nave a vista destruira todas as outras, caso seja encontrada. Voce conseguiu ", NULL);			//Inicializa o texto
	sprintf(txt[3],"interceptar um sinal e pode encontrar essa nave apenas descobrindo a logica. Agora, esta em ", NULL);		//Inicializa o texto
	sprintf(txt[4],"suas maos.", NULL);																							//Inicializa o texto
	sprintf(txt[5],"" , NULL);
	sprintf(txt[6],"Como jogar:" , NULL);
	sprintf(txt[7],"O Espaco-X nao e um jogo de nave comum, ele possui 10 inimigos, cada um representa um algarismo." , NULL);
	sprintf(txt[8],"Cada erro faz com que os inimigos se aproximem mais." , NULL);
	sprintf(txt[9],"Acertar o inimigo correto destroi todas as naves alem de lhe render 100 pontos." , NULL);
	sprintf(txt[10],"Ao acertar uma certa quantidade de inimigos, voce passa de nivel, dificultando o jogo." , NULL);
	sprintf(txt[11],"Sua pontuacao fica no canto superior esquerdo e a equacao no centro da tela." , NULL);
	sprintf(txt[12],"" , NULL);
	sprintf(txt[13],"Comandos:" , NULL);
	sprintf(txt[14],"Seta para a direita: Move a nave para a direita." , NULL);
	sprintf(txt[15],"Seta para a esquerda: Move a nave para a esquerda" , NULL);
	sprintf(txt[16],"Barra de espaço: Atira" , NULL);
	sprintf(txt[17],"ESC: Termina o jogo" , NULL);
	sprintf(txt[18],"Boa diversao!" , NULL);
	sprintf(txt[19],"" , NULL);
	sprintf(txt[20],"Pressione  'Espaco' para voltar." , NULL);
	int i = 0;
	int y = 200;
	while (i <= 20){
		textout(screen,font,txt[i],200,y - 100,makecol(255,255,255));   	//Exibe o texto
		i++;
		y += 20;
	}
    

	while (!key[KEY_SPACE]){

	}

	menu();

}
void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
void atirar(){
    tiro.vida = 0; 													// Quando tempo ele ficara na tela?									// Posicao do tiro (eixo X)
    tiro.py = ynave[e];  											// Posicao do tiro (eixo Y)
    int local1 = ((ini * 125) + 15) + 30;           				// Define a posição inicial da colisão
    int local2 = (local1 + 125) - 50;               				// Define a posição final da colisão
    int i = 0;
    if (e == 0){
        tiro.px = xnave[e] + 90;
	}
	else {
	    if (e == 1){
			tiro.px = xnave[e] + 150;
		}
		else {
			if (e == 2){
		        tiro.px = xnave[e] + 60;

			}
		}
	}
    
	while (tiro.vida <= 19){
        blit(buffer, screen, 0,0,0,0,1280,720);     				//Limpa a tela
       	clear_bitmap(buffer);                       				//Limpa a tela
       	draw_sprite(buffer, background[back], 0, 0);      			//Coloca a imagem na tela
       	draw_sprite(screen, nave[e], xnave[e],ynave[e]);     		//Põe a nave na tela
       	if (tiro.py > yini + 125){
        	circlefill(buffer, tiro.px, tiro.py, 5, makecol(255, 0, 0));
			draw_sprite(screen, inimigo[p], xini, yini); 				//Põe a nave na tela
		}
        tiro.py -= 20;												//Velocidade em Y (deslocamento do tiro)
    	tiro.vida += 1;                             				//Contador do "While"

        if (tiro.py <= 105){
			if ((tiro.px >= local1 ) && (tiro.px <= local2 )){
				colisao();
	        	tiro.vida = 25;
        	}
	        else{
				inimigos();
				c += 1;
			}
  }
		if (c == 3){
	        draw_sprite(screen, inimigo[p], xini,yini);   			//Põe os inimigos na tela
			perdeu();
		}
   	}
	blit(buffer, screen, 0,0,0,0,1280,720);     					//Limpa a tela
   	clear_bitmap(buffer);                       					//Limpa a tela
   	draw_sprite(buffer, background[back], 0, 0);      				//Coloca a imagem na tela
   	draw_sprite(screen, nave[e], xnave[e],ynave[e]);     			//Põe a nave na tela
}
void colisao(){
	int i = 0;
	int x = -50.0;
	int y = yini - 50.0;
	int k = 0;
	float l = 15.0;
	int m = 0;
	score += 100;

	explosao2();
	winner();
    blit(buffer, screen, 0,0,0,0,1280,720);     					//Limpa a tela
	clear_bitmap(buffer);                       					//Limpa a tela
	draw_sprite(buffer, background[back], 0, 0);      				//Coloca a imagem na tela
	draw_sprite(screen, nave[e], xnave[e],ynave[e]);     			//Põe a nave na tela
	
	while (!key[KEY_ENTER]){
		readkey();
    	textout(screen, font, "Acertou a nave desprotegida! Tecle 'Enter' para continuar", 400,350, makecol(255,0,0 ) );
    	char txt[15]; sprintf(txt,"x + %d = %d", b, a);				//Inicializa o texto
		char txt2[15]; sprintf(txt2,"Pontos = %d", score);			//Inicializa o texto
		textout(screen,font,txt,600,450,makecol(255,0,0));  		//Exibe o texto
		textout(screen,font,txt2,5,5,makecol(255,0,0));  			//Exibe o texto
    	if (score == 300){
			nivel = 2.0;
			textout(screen, font, "Nivel 2", 600,365, makecol(255,0,0 ) );
			back = 1;
		}
		if (score == 500){
			nivel = 4.0;
			textout(screen, font, "Nivel 3", 600,365, makecol(255,0,0 ) );
			back = 2;
		}
		if (score == 600){
			nivel = 5.0;
			textout(screen, font, "Nivel 4", 600,365, makecol(255,0,0 ) );
			back = 3;
		}
		if (score == 700){
			nivel = 6.0;
			textout(screen, font, "Nivel 5", 600,365, makecol(255,0,0 ) );
			back = 4;
		}
		if (score == 800){
			nivel = 10.0;
			textout(screen, font, "Nivel 6", 600,365, makecol(255,0,0 ) );
			back = 5;
		}
		if (score == 900){
			nivel = 16.0;
			textout(screen, font, "Nivel 7", 600,365, makecol(255,0,0 ) );
			back = 6;
		}
		if (score == 1000){
			nivel = 20.0;
			textout(screen, font, "Nivel MAX", 600,365, makecol(255,0,0 ) );
			back = 7;
		}
	}
	equacao();
	yini = 40.0;
	c = 0;
}
void equacao(){
 	//srand(time(NULL));
	ini = rand() % 10;
 	//srand(time(NULL));
	b = rand() % 10;
	while(ini + b > 9){

	        textout(screen, font, "Calculando Equacao", 570,5, makecol(255,0,0 ) );
	        //srand(time(NULL));
			ini = rand() % 10;
			//srand(time(NULL));
			b = rand() % 10;

	}
	a = ini + b;
}
void perdeu(){

    clock_t tempo;
   	float FPS = 15.0;
   	tempo = clock();
	explosao(xnave[e] - 40, ynave[e] - 30);
	blit(buffer, screen, 0,0,0,0,1280,720);     					//Limpa a tela
	clear_bitmap(buffer);                       					//Limpa a tela
	draw_sprite(buffer, background[back], 0, 0);      				//Coloca a imagem na tela

	draw_sprite(screen, inimigo[p], 15,yini); 						//Põe a nave na tela
	loser();

	while (!key[KEY_ENTER]){

		textout(screen, font, "Voce perdeu! Tecle 'Enter' para comecar novamente", 450,350, makecol(255,0,0 ) );
		char txt[15]; sprintf(txt,"x + %d = %d", b, a);				//Inicializa o texto
		char txt2[15]; sprintf(txt2,"Score = %d", score);			//Inicializa o texto
		textout(screen,font,txt,5,5,makecol(255,0,0));  			//Exibe o texto
		textout(screen,font,txt2,5,20,makecol(255,0,0));  			//Exibe o texto
		if ( (double)(clock() - tempo) >= 1000/FPS ) {
			if (p == 10){
				p++;
			}
			else {
				if (p == 11){
					p++;
				}
				else {
					if (p == 12){
						p++;
					}
					else {
						if (p == 13){
							p = 10;
						}
					}
				}
			}
			blit(buffer, screen, 0,0,0,0,1280,720);     			//Limpa a tela
	        clear_bitmap(buffer);                       			//Limpa a tela
	        draw_sprite(buffer, background[back], 0, 0);      		//Coloca a imagem na tela
			draw_sprite(screen, inimigo[p], 15,yini); 				//Põe a nave na tela
	        tempo = clock();
		}
	}
	c = 0;
    yini = 40.0;
	score = 0;
	nivel = 1.0;
	back = 0;
}
void explosao(int x, int y){
    expl();
	int m = 0;
 	clock_t tempo;
   	float FPS = 15.0;
   	tempo = clock();
    bomba[0] = load_bitmap("c1.bmp", NULL);
    bomba[1] = load_bitmap("c2.bmp", NULL);
    bomba[2] = load_bitmap("c3.bmp", NULL);
    bomba[3] = load_bitmap("c4.bmp", NULL);
    bomba[4] = load_bitmap("c5.bmp", NULL);
	bomba[5] = load_bitmap("c6.bmp", NULL);
	bomba[6] = load_bitmap("c7.bmp", NULL);
	bomba[7] = load_bitmap("c8.bmp", NULL);
	bomba[8] = load_bitmap("c9.bmp", NULL);
	bomba[9] = load_bitmap("c10.bmp", NULL);
	bomba[10] = load_bitmap("c11.bmp", NULL);

	while(m < 10){
        if ( (double)(clock() - tempo) >= 1000/FPS ) {
            			if (p == 10){
				p++;
			}
			else {
				if (p == 11){
					p++;
				}
				else {
					if (p == 12){
						p++;
					}
					else {
						if (p == 13){
							p = 10;
						}
					}
				}
			}

        	blit(buffer, screen, 0,0,0,0,1280,720);     			//Limpa a tela
			clear_bitmap(buffer);                       			//Limpa a tela
			draw_sprite(buffer, background[back], 0, 0);      		//Coloca a imagem na tela
	        draw_sprite(screen, bomba[m], x, y);
	        draw_sprite(screen, inimigo[p], 15,yini); 				//Põe a nave na tela
	        m++;
	        tempo = clock();
		}
	}
}
void escolha(){
	int i = 0;
	nave[0] = load_bitmap("nave1.bmp", NULL);          				//A Nave recebe a imagem
    nave[1] = load_bitmap("nave2.bmp", NULL);          				//A Nave recebe a imagem
    nave[2] = load_bitmap("nave3.bmp", NULL);          				//A Nave recebe a imagem
	while(!key[KEY_ENTER]){
        blit(buffer, screen, 0,0,0,0,1280,720);     				//Limpa a tela
		clear_bitmap(buffer);                       				//Limpa a tela
		draw_sprite(buffer, background[back], 0, 0);      			//Coloca a imagem na tela
		draw_sprite(screen, nave[i], xnave[i],250);         		//Põe a nave na tela
		textout(screen, font, "Use as teclas para a 'Direita', 'Esquerda' e 'Enter' para escolher.", 380,500, makecol(255,0,0 ) );

		readkey();

		if (key[KEY_RIGHT]){
			if (i < 2){
				i++;
				draw_sprite(screen, nave[i], xnave[i],250);         //Põe a nave na tela
			}
		}
		if (key[KEY_LEFT]){
			if (i > 0){
				i--;
				draw_sprite(screen, nave[i], xnave[i],250);         //Põe a nave na tela
			}
		}
		e = i;
	}
	escnave();
}
void inimigos(){
    clock_t tempo;
   	float FPS = 45.0;
   	tempo = clock();
	int o = 0;
   	while (o < 100){
        if ( (double)(clock() - tempo) >= 1000/FPS ) {
			yini +=10;
			o += 10;
			draw_sprite(screen, inimigo[p], xini,yini); 				//Põe a nave na tela
			tempo = clock();
		}
	}
}
void explosao2(){
    expl();
    clock_t tempo;
   	float FPS = 15.0;
   	tempo = clock();
    int i = 0;
	int x = -50.0;
	int y = yini - 50.0;
	int k = 0;
	float l = 140.0;
	int m = 0;
	int q = 0;

	bomba[0] = load_bitmap("c1.bmp", NULL);
    bomba[1] = load_bitmap("c2.bmp", NULL);
    bomba[2] = load_bitmap("c3.bmp", NULL);
    bomba[3] = load_bitmap("c4.bmp", NULL);
    bomba[4] = load_bitmap("c5.bmp", NULL);
	bomba[5] = load_bitmap("c6.bmp", NULL);
	bomba[6] = load_bitmap("c7.bmp", NULL);
	bomba[7] = load_bitmap("c8.bmp", NULL);
	bomba[8] = load_bitmap("c9.bmp", NULL);
	bomba[9] = load_bitmap("c10.bmp", NULL);
	bomba[10] = load_bitmap("c11.bmp", NULL);
 	
	blit(buffer, screen, 0,0,0,0,1280,720);     					//Limpa a tela
	clear_bitmap(buffer);                       					//Limpa a tela
	draw_sprite(buffer, background[back], 0, 0);      				//Coloca a imagem na tela
 	draw_sprite(screen, inimigo[p], 15,yini); 						//Põe a nave na tela
 	while(m < 10){
        if ( (double)(clock() - tempo) >= 1000/FPS ) {
            blit(buffer, screen, 0,0,0,0,1280,720);     			//Limpa a tela
			clear_bitmap(buffer);                       			//Limpa a tela
			draw_sprite(buffer, background[back], 0, 0);      		//Coloca a imagem na tela
	        draw_sprite(screen, bomba[m], -50, y);
	        draw_sprite(screen, bomba[m], 75, y);
	        draw_sprite(screen, bomba[m], 200, y);
	        draw_sprite(screen, bomba[m], 325, y);
	        draw_sprite(screen, bomba[m], 450, y);
	        draw_sprite(screen, bomba[m], 575, y);
	        draw_sprite(screen, bomba[m], 700, y);
	        draw_sprite(screen, bomba[m], 825, y);
	        draw_sprite(screen, bomba[m], 950, y);
	        draw_sprite(screen, bomba[m], 1075, y);
	        draw_sprite(screen, nave[e], xnave[e],ynave[e]);     	//Põe a nave na tela
	        m++;
	        tempo = clock();
		}
	}
}
void abertura(){

	SAMPLE *som;
   	som = load_sample("Abertura1.wav");
   	play_sample(som, 255, 128, 1000, FALSE);
   	
}
void lazer(){

	SAMPLE *som;
   	som = load_sample("laser.wav");
   	play_sample(som, 255, 128, 1000, FALSE);

}
void expl(){

	SAMPLE *som;
   	som = load_sample("boom.wav");
   	play_sample(som, 255, 128, 1000, FALSE);

}
void winner(){

	SAMPLE *som;
   	som = load_sample("winner.wav");
   	play_sample(som, 255, 128, 1000, FALSE);

}
void loser(){

	SAMPLE *som;
   	som = load_sample("loser.wav");
   	play_sample(som, 255, 128, 1000, FALSE);

}
void escnave(){

	SAMPLE *som;
   	som = load_sample("affair.wav");
   	play_sample(som, 255, 128, 1000, FALSE);

}

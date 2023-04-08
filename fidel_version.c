#include<stdio.h>
#include<stdlib.h>
#include "trilha.h"
#include "library.h"
#include <time.h>

int jogar_dado(int n);
void verificarJogador(int njogadores, trilha p[]);
int print_efeito(int p);
void verificarGanhador(int p, int *vencedor, int classificacao[], int *lugar,
int jogador, int *faltam);
int armadilhas[8] = {4, 10, 15, 18, 34, 42, 46, 54}; //enumeração de todas as armadilhas (os numeros representam as posições)
int ativaArmadilha[4] = {}; //algumas armadilhas precisam ser ativadas antes de pegar algum jogador. esse vetor armazena seelas foram ativadas (1) ou não (0). A relação da ordem está assim: [0] é 4, [1] é 18, [2] é 34 e [3] é 42
int armadilhaFoiUsada[8] = {}; // armazena o status sobre se a armadilha oi usada ou não. A relação da ordem é a mesma da indicada no vetor armadilhas

int main(){
    
    int p1 = 0, p2 = 0, p3 = 0, p4 = 0, njogadores = 0, restantes, comando, posicao;
    int temp, vencedor = 0, classificacao[4] = {0}, lugar = 0;
    trilha p[4];
    //Definicao de jogadores. Deve ser entre 2 a 4 jogadores.
    while((njogadores < 2)||(njogadores > 4)){
        printf("Nº de jogadores:");
        scanf("%d", &njogadores);
        if(njogadores < 2){
            printf("Numero insuficiente. Deve haver pelo menos 2 jogadores\n");
        }else if(njogadores > 4){
            printf("Ha jogadores demais. Deve haver ate 4 jogadores\n");
        }
    }
    //Inicializacao dos vetores de cada jogador na biblioteca trilha.h
    for(int i = 0; i < njogadores; i++){
        inicio(&p[i]);
    }
    restantes = njogadores;
    /*Inicio do jogo. A partida sera realizada ate o penultimo jogador completar
    o tabuleiro*/
    while(restantes > 1){
        //Looping que intercala os jogadores
        for(int i = 0; i < njogadores; i++){
            /*Jogador 1. Verifica se ainda nao completou o jogo e se ainda ha mais
            um jogador na partida*/
            if((i==0)&&(restantes > 1)){
                if(valorUltimo(&p[i]) > 58){
                    continue;
                }else{
                    comando = 0;
                    /*Inicio da jogada. O jogador recebe sua posicao atual e 
                    pode decidir se ira jogar os dados ou se ira verificar a posi-
                    cao de um jogador a sua escolha. A sua jogada termina apenas
                    quando os dados forem jogados*/
                    printf("\nVez do jogador %d\n", i+1);
                    p1 = valorUltimo(&p[i]);
                    printf("Voce esta na casa %d\n\n", p1);
                    while(comando != 1){
                        printf("Digite que deseja fazer\n");
                        printf("1 - Jogar dado\n2 - Verificar posicao de um jogador\n");
                        scanf("%d", &comando);
                        switch(comando){
                            case 1 :
                                p1 += jogar_dado(0);
                                /*Jogador ganha apenas se tirar o valor exato para
                                atingir a ultima casa. Caso contrario, o valor "ex-
                                cedente" sera subtraido da ultima posicao para de-
                                finir sua posicao atual*/
                                if(p1 > 59){
                                    int sobra = p1 - 59;
                                    p1 = 59 - sobra;
                                }
                                //Recebe o efeito da casa no qual caiu
                                p1 = print_efeito(p1);
                                //Insere a casa atual na sua trilha
                                insere(&p[i], p1);
                                //Recebe a nova posicao e encerra sua jogada
                                printf("Sua nova posicao: %d\n", p1);
                                //Verifica se o jogador terminou o  jogo.
                                verificarGanhador(p1, &vencedor, classificacao,
                                &lugar, i+1, &restantes);
                                printf("Aperte ENTER para continuar\n");
                                getchar(); // Aguarda o usuário apertar ENTER
                                printf("\n\n\n\n\n\n\n\n");
                                break;
                        
                            case 2 :
                                verificarJogador(njogadores, p);
                                break;
                            
                            default :
                                printf("Comando invalido\n\n");
                                break;
                        }
                    }
                    
                }
            }
            /*Os outros "if"s presentes nesse looping seguem o mesmo procdimento
            explicado paa o jogador 1*/
            if((i==1)&&(restantes > 1)){
                if(valorUltimo(&p[i]) > 58){
                    continue;
                }else{
                    comando = 0;
                    printf("\nVez do jogador %d\n", i+1);
                    p2 = valorUltimo(&p[i]);
                    printf("Voce esta na casa %d\n\n", p2);
                    
                    while(comando != 1){
                        printf("Digite que deseja fazer\n");
                        printf("1 - Jogar dado\n2 - Verificar posicao de um jogador\n");
                        scanf("%d", &comando);
                        switch(comando){
                            case 1 :
                                p2 += jogar_dado(0);
                                if(p2 > 59){
                                    int sobra = p2 - 59;
                                    p2 = 59 - sobra;
                                }
                                p2 = print_efeito(p2);
                                insere(&p[i], p2);
                                printf("Sua nova posicao: %d\n", p2);
                                verificarGanhador(p2, &vencedor, classificacao,
                                &lugar, i+1, &restantes);
                                printf("Aperte ENTER para continuar\n");
                                getchar();
                                printf("\n\n\n\n\n\n\n\n");                                
                                break;
                        
                            case 2 :
                                verificarJogador(njogadores, p);
                                break;
                            
                            default :
                                printf("Comando invalido\n\n");
                                break;
                        }
                    }
                    
                }
            }
            if((i==2)&&(restantes > 1)){
                 if(valorUltimo(&p[i]) > 58){
                     continue;
                }else{
                    comando = 0;
                    printf("\nVez do jogador %d\n", i+1);
                    p3 = valorUltimo(&p[i]);
                    printf("Voce esta na casa %d\n", p3);
                    while(comando != 1){
                        printf("Digite que deseja fazer\n");
                        printf("1 - Jogar dado\n2 - Verificar posicao de um jogador\n");
                        scanf("%d", &comando);
                        switch(comando){
                            case 1 :
                                p3 += jogar_dado(0);
                                if(p3 > 59){
                                    int sobra = p3 - 59;
                                    p3 = 59 - sobra;
                                }
                                p3 = print_efeito(p3);
                                insere(&p[i], p3);
                                printf("Sua nova posicao: %d\n", p3);
                                verificarGanhador(p3, &vencedor, classificacao,
                                &lugar, i+1, &restantes);
                                printf("Aperte ENTER para continuar\n");
                                getchar();
                                printf("\n\n\n\n\n\n\n\n");                                
                                break;
                        
                            case 2 :
                                verificarJogador(njogadores, p);
                                break;
                            
                            default :
                                printf("Comando invalido\n\n");
                                break;
                        }
                    }
                    
                }
            }
            if((i==3)&&(restantes > 1)){
                 if(valorUltimo(&p[i]) > 58){
                    continue;
                }else{
                    comando = 0;
                    printf("\nVez do jogador %d\n", i+1);
                    p4 = valorUltimo(&p[i]);
                    printf("Voce esta na casa %d\n", p4);
                    while(comando != 1){
                        printf("Digite que deseja fazer\n");
                        printf("1 - Jogar dado\n2 - Verificar posicao de um jogador\n");
                        scanf("%d", &comando);
                        switch(comando){
                            case 1 :
                                p4 += jogar_dado(0);
                                if(p4 > 59){
                                    int sobra = p4 - 59;
                                    p4 = 59 - sobra;
                                }
                                p4 = print_efeito(p4);
                                insere(&p[i], p4);
                                printf("Sua nova posicao: %d\n", p4);
                                verificarGanhador(p4, &vencedor, classificacao,
                                &lugar, i+1, &restantes);
                                printf("Aperte ENTER para continuar\n");
                                getchar();
                                printf("\n\n\n\n\n\n\n\n");                                
                                break;
                        
                            case 2 :
                                verificarJogador(njogadores, p);
                                break;
                            
                            default :
                                printf("Comando invalido\n\n");
                                break;
                        }
                    }
                    
                }
            }
        }
    }
    //Adiciona o jogador que na concluiu a jogatina a classificacao final.
    for(int i = 0; i < njogadores; i++){
        if((valorUltimo(&p[i])) < 59){
            classificacao[lugar] = i+1;
            lugar++;
        }
    }
    //Exibe a classificacao final e a trilha percorrida por cada jogador no tabuleiro 
    printf("Fim de jogo!\nO vencedor foi o jogador %d, Parabens!\n", vencedor);
    printf("classificacao final:\n");
    for(int i = 0; i < njogadores; i++){
        printf("%dº Lugar: %d\n", i+1, classificacao[i]);
    }
    for(int i = 0; i < njogadores; i++){
        printf("Caminho do jogador %d:\n 0 ", i+1);
        while(!vazio(&p[i])){
            printf("- %d ", valorInicio(&p[i]));
            int trash = retira(&p[i]);
        }
        fim(&p[i]);
        printf("\n");
    }
return 0;
}


int print_efeito(int p){
	//Jogador recebe um efeito a depender da posicao em que "caiu" no tabuleiro.
	if ((p == 3) ||(p == 9) || (p == 14) ||
 (p == 25) || (p == 40) || (p == 44)){
		printf("Parabens! Voce avanca duas casas, sua nova posicao e %d\n", p+2);
		return p+2;
}
	else if( (p ==8) || (p == 20) || (p == 27) ||
(p == 36) || (p == 41) || (p ==55)){
		printf("Que pena, voce recua duas casas\n");
		return p-2;
	}
    else if(p == 29){
		printf("Que sorte! Voce achou um buraco de minhoca e se teletransportou para a casa 39\n");
		return 39;
	}
    else if(p == 39){
		printf("Que sorte! Voce achou um buraco de minhoca e se teletransportou para a casa 49\n");
		return 49;
	}
    else if(p == 49){
		printf("Que pena! Voce achou um buraco de minhoca e se teletransportou para a casa 39\n");
		return 39;
	}
	else if( (p==4 && ativaArmadilha[0] && !armadilhaFoiUsada[0]) || (p == 10 && !armadilhaFoiUsada[1]) || (p == 15 && !armadilhaFoiUsada[2]) || (p==18 && ativaArmadilha[1] && !armadilhaFoiUsada[3]) || (p==34 && ativaArmadilha[2] && !armadilhaFoiUsada[4]) || (p==42 && ativaArmadilha[3] && !armadilhaFoiUsada[5]) || (p == 46 && !armadilhaFoiUsada[6]) || (p == 54 && !armadilhaFoiUsada[7]) ){
      int v;
      if(p == 4 || p==10 || p == 15 || p == 34){
        v = 1;
      }else if(p == 18 || p == 46 || p == 48){
        v = 2;
      }else{
        v = 3;
      }
    for(int i=0; i<8; i++){
      if(armadilhas[i] == p){
        armadilhaFoiUsada[i] = 1;
      }
    }
      printf("Opa, você caiu na armadilha. Volte %d casas", v);
      p -= v;
  }else if(p == 4 && !ativaArmadilha[0]|| p == 18 && !ativaArmadilha[1]|| p == 34 && !ativaArmadilha[2]|| p == 42 && !ativaArmadilha[3]){
    if(p==4){
      ativaArmadilha[0] = 1;
    }else if(p==18){
      ativaArmadilha[1] = 1;
    }
    else if(p==34){
      ativaArmadilha[2] = 1;
    }else if(p==42){
      ativaArmadilha[3] = 1;
    }

    printf("Você acabou de colocar uma armadilha!");
  }
	/*else if(p==(24 || 33 || 43 || 58)){
		printf("Voce acabou caindo em um buraco negro e por conta disso perde uma rodada");
	}*/
	return p;
}
void verificarJogador(int njogadores, trilha p[]){
    //Escolha de qual jogador se quer verifcar a posicao atual.
    int posicao = 0;
    while((posicao > njogadores)||(posicao < 1)){
        printf("Qual jogador eseja verificar?\n");
        scanf("%d", &posicao);
            if((posicao > njogadores)||(posicao < 1)){
                printf("Comando invalido\n\n");
                continue;
            }else{
                printf("O jogador %d se encontra na posicao %d\n\n", posicao, valorUltimo(&p[posicao - 1]));
            }
    }
    return;
}
void verificarGanhador(int p, int *vencedor, int classificacao[], int *lugar,
int jogador, int *faltam){
    /*Analisa se o jogador atingiu a casa final. Caso  positivo, verifica qual a 
    sua posicao final na partida. Caso negaativo, sai da funcao sem realizar qual-
    quer efeito*/
    if(p == 59){
        if(!(*vencedor)){
            printf("Parabens! Voce venceu o jogo!\n");
            *vencedor = jogador;
        }else{
            printf("Voce terminou o jogo!\n");}
        
        classificacao[*lugar] = jogador;
        *lugar += 1;
        *faltam -= 1;
    }
}
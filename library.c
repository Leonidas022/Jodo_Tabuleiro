#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//Função que retorna o número tirado no dado
int jogar_dado(int n) {
	printf("Aperte ENTER para jogar o dado\n");
    getchar(); // Aguarda o usuário apertar ENTER
    getchar(); // Lê o caractere ENTER que foi digitado pelo usuário
    srand(time(NULL));
    n = (rand()%6 + 1);
    printf("O valor tirado foi %d.\n", n);
	
    return n;
}
/*int print_efeito(int p){
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
}*/

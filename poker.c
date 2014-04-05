#include <stdio.h>
#include <stdlib.h>

int J=11;
int Q=12;
int K=13;
int A=14;

typedef struct tCarta{
	int valor;
	char naipe;
} tCarta;

typedef struct tMao{
	tCarta cartas[5];
	int pontos;
}tMao;

void troca (tCarta *x, tCarta *y) {
	tCarta aux=*x;
	*x=*y;
	*y=aux;
	return;
} //função auxiliar para ordenação de mão

void ordenaMao(tMao* mao,int n){
	int i;
	if (n==1) {
		return;
	}
	for(i=0;i<n-1;i++){ 
		if(mao->cartas[i].valor > mao->cartas[i+1].valor) {
			troca(&mao->cartas[i],&mao->cartas[i+1]);		
		}
	}
	ordenaMao(mao,n-1);
	return;
} //função de ordenação da mão (todas as funções levam em consideração que a mão foi previamente ordenada)

int maiorCarta(tMao j1, tMao j2){
	if(j1.cartas[4].valor>j2.cartas[4].valor){
		return 1;
	}else if(j2.cartas[4].valor>j1.cartas[4].valor){
		return 2;
	}
	return 0;
}//verifica qual mão tem a maior carta, retorna 0 empate, 1 jogador 1 e 2 jogador 2

int temPar(tMao mao) {
	int i;
	for(i=0;i<4;i++){
		if(mao.cartas[i].valor==mao.cartas[i+1].valor){
			return 1;
		}
	}
	return 0;
} //verifica se existe par 0 = falso, 1 = verdadeiro

int doisPares(tMao mao){
	int i;
	for(i=0;i<4;i++){
		if(mao.cartas[i].valor==mao.cartas[i+1].valor){
			break;
		}
	}
	i+=2;
	for(;i<4;i++){
		if(mao.cartas[i].valor==mao.cartas[i+1].valor){
			return 1;
		}
	}
	return 0;
	
	
}

int temTrinca(tMao mao){
	int i;
	if(temPar(mao)){
		for (i=0;i<3;i++){
			if((mao.cartas[i].valor==mao.cartas[i+1].valor)&&(mao.cartas[i].valor==mao.cartas[i+2].valor)){
				return 1;
			}
		}
	}
	return 0;
} //verifica se existe trinca 0 = falso, 1 = verdadeiro

int temQuadra(tMao mao){
	if (temTrinca(mao)){
		if((mao.cartas[0].valor==mao.cartas[3].valor)||(mao.cartas[1].valor==mao.cartas[4].valor)){
			return 1;
		}
	}
	return 0;
} //verifica se existe quadra 0 = falso, 1 = verdadeiro

int temStraigth(tMao mao){
	int i;
	for(i=0;i<4;i++){
		if(mao.cartas[i].valor!=((mao.cartas[i+1].valor)-1)){
			return 0;
		}
	}
	return 1;
} //verifica se as cartas estão em sequencia 0 = falso, 1 = verdadeiro

int temFlush(tMao mao){
	int i;
	for(i=0;i<4;i++){
		if(mao.cartas[i].naipe!=mao.cartas[i+1].naipe){
			return 0;
		}
	}
	mao.pontos=6;
	return 1;
} //verifica se todas as cartas são do mesmo naipe 0 = falso, 1 = verdadeiro

int temFullHouse(tMao mao){
	if(((mao.cartas[0].valor==mao.cartas[1].valor)&&(mao.cartas[1].valor==mao.cartas[2].valor)&&(mao.cartas[3].valor==mao.cartas[4].valor))||((mao.cartas[0].valor==mao.cartas[1].valor)&&(mao.cartas[2].valor==mao.cartas[3].valor)&&(mao.cartas[3].valor==mao.cartas[4].valor))){
		return 1;
	}
	return 0;
} //verifica se é um fullHouse 0 = falso, 1 = verdadeiro

int temStraigthFlush(tMao mao){
	if(temStraigth(mao)&&temFlush(mao)){
		return 1;
	}
	return 0;
} //verifica se é um StraoghtFlush 0 = falso, 1 = verdadeiro

int temRoyalFlush(tMao mao){
	if(mao.cartas[4].valor==14&&temStraigthFlush(mao)){
		return 1;
	}
	return 0;
} //verifica se é um Royal Flush 0 = falso, 1 = verdadeiro


int main(int argc,char** argv) {
	tMao jogador1,jogador2;
	int maior=0;
	
	//Na linha abaixo adiciona as cartas 2,3,4,5,6,7,8,9,10,J,Q,K e A e os naipes letras C P O E
	jogador1.cartas[0].valor=2;
	jogador1.cartas[0].naipe='C';
	jogador1.cartas[1].valor=3;
	jogador1.cartas[1].naipe='E';
	jogador1.cartas[2].valor=7;
	jogador1.cartas[2].naipe='P';
	jogador1.cartas[3].valor=5;
	jogador1.cartas[3].naipe='O';
	jogador1.cartas[4].valor=9;
	jogador1.cartas[4].naipe='C';
	
	jogador2.cartas[0].valor=A;
	jogador2.cartas[0].naipe='C';
	jogador2.cartas[1].valor=K;
	jogador2.cartas[1].naipe='O';
	jogador2.cartas[2].valor=Q;
	jogador2.cartas[2].naipe='P';
	jogador2.cartas[3].valor=J;
	jogador2.cartas[3].naipe='E';
	jogador2.cartas[4].valor=A;
	jogador2.cartas[4].naipe='O';
	//Aqui terminam as cartas 
	
	jogador1.pontos=0;
	jogador2.pontos=0;
	
	ordenaMao(&jogador1,5);
	ordenaMao(&jogador2,5);

	if(temPar(jogador1)) jogador1.pontos=2;
	if(temPar(jogador2)) jogador2.pontos=2;
	
	if(doisPares(jogador1)) jogador1.pontos=3;
	if(doisPares(jogador2)) jogador2.pontos=3;
	
	if(temTrinca(jogador1)) jogador1.pontos=4;
	if(temTrinca(jogador2)) jogador2.pontos=4;
	
	if(temStraigth(jogador1)) jogador1.pontos=5;
	if(temStraigth(jogador2)) jogador2.pontos=5;
	
	if(temFlush(jogador1)) jogador1.pontos=6;
	if(temFlush(jogador2)) jogador2.pontos=6;
	
	if(temFullHouse(jogador1)) jogador1.pontos=7;
	if(temFullHouse(jogador2)) jogador2.pontos=7;
	
	if(temQuadra(jogador1)) jogador1.pontos=8;
	if(temQuadra(jogador2)) jogador2.pontos=8;
	
	if(temStraigthFlush(jogador1)) jogador1.pontos=9;
	if(temStraigthFlush(jogador2)) jogador2.pontos=9;
	
	if(temRoyalFlush(jogador1)) jogador1.pontos=10;
	if(temRoyalFlush(jogador2)) jogador2.pontos=10;
	
	if(jogador1.pontos==0&&jogador2.pontos==0){
		maior=maiorCarta(jogador1,jogador2);
		if(maior==1) jogador1.pontos=1;
		else if(maior==2) jogador2.pontos=1;
		
	}

	if (jogador1.pontos>jogador2.pontos){
		printf("Jogador 1!");
	} else if(jogador1.pontos<jogador2.pontos) {
		printf("Jogador 2!");
	} else {
		printf("EMPATE!");
	}
	
	return 0;
}

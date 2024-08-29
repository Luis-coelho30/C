#include "Booleano.h"
#include <stdlib.h>
#include <stdio.h>

#define MaxQ 10
#define sinal -1
#define ghost 255 

typedef struct{
	int	inicio;
	int	fim;
	unsigned char Vetor[MaxQ];
} Fila;

Fila criarFilaVazia();
bool FilaVazia(Fila);
int acessarPrimeiro(Fila);
Fila pushFila(Fila,int);
Fila popFila(Fila);
Fila esvaziarFila(Fila);
int obterTamanho(Fila); 
void mostrarFila(Fila);

int main() {
	Fila Q = criarFilaVazia();
	Q = pushFila(Q, 3);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	Q = pushFila(Q, 12);
	mostrarFila(Q);
	Q = popFila(Q);
	mostrarFila(Q);
	Q = pushFila(Q, 122);
	mostrarFila(Q);
	return 0;
}

Fila criarFilaVazia() {
	Fila Q;
	Q.inicio=sinal;
	Q.fim=sinal;
	
	return Q;
}

bool FilaVazia(Fila Q) {
	bool vazio=FALSE;
	
	if(Q.inicio==sinal)
		vazio=TRUE;	
		
	return vazio;
}

int acessarPrimeiro(Fila Q) {
	int el = ghost;
	
	if(Q.inicio!=sinal)
		el = Q.Vetor[Q.inicio];
		
	return el;
}

Fila pushFila(Fila Q, int y) {
	int seg;
	seg = (Q.fim+1)%MaxQ;
	
	if(seg!=Q.inicio) {
		Q.Vetor[seg] = y;
		if(Q.inicio==sinal) Q.inicio = seg;
		Q.fim = seg;
	}
	
	return Q;
}

Fila popFila(Fila Q) {
	if(Q.inicio!=sinal) { //Se a fila nao estiver vazia
		if(Q.inicio==Q.fim) { //Se houver apenas um elemento 
			Q.inicio = sinal;
			Q.fim = sinal;
		}
		else {
			int seg = (Q.inicio+1)%MaxQ;
			Q.inicio = seg;		
		}
	}

	return Q;	
}

Fila esvaziarFila(Fila Q) {
	Q.inicio=sinal;
	Q.fim=sinal;
	
	return Q;
}

int obterTamanho(Fila Q) {
	int tamanho = 0;
	if(Q.inicio!=sinal) {
		int pos = (Q.inicio+1)%MaxQ;
		int i;
		tamanho++;
		for(i=pos; i!=Q.inicio; i=(i+1)%MaxQ) {
			tamanho++;
		}
	}
	
	return tamanho;
} 

void mostrarFila(Fila Q) {
	printf("\n");
	
	if(Q.inicio!=sinal) {
		int pos = Q.inicio;
		int i;
		do {
			printf("%d\t", Q.Vetor[pos]);
			pos = (pos+1)%MaxQ;	
				
		}while(pos!=(Q.fim+1)%MaxQ);
	}
	
	else {
		printf("Fila Vazia");
	}
	
	printf("\n");
}

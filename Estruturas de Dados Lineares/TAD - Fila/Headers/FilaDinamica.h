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
} FilaC;

typedef FilaC *Fila;

Fila criarFilaVazia();
bool FilaVazia(Fila );
int acessarPrimeiro(Fila );
void pushFila(Fila , int y);
void popFila(Fila );
void esvaziarFila(Fila );
int obterTamanho(Fila ); 
void mostrarFila(Fila );

Fila criarFilaVazia() {
	Fila A = (Fila)malloc(sizeof(Fila));
	A->fim=sinal;
	A->inicio=sinal;
	
	return A;
}

bool FilaVazia(Fila Q) {
	bool vazia = FALSE;
	if(Q->inicio==sinal)
		vazia = TRUE;
		
	return vazia;
}

int acessarPrimeiro(Fila Q) {
	int el = ghost;
	if(Q->inicio!=sinal) {
		el = Q->Vetor[Q->inicio];
	}
	
	return el;
}

void pushFila(Fila Q, int y) {
	int seg = (Q->fim+1)%MaxQ;
	if(seg!=Q->inicio) {
		Q->Vetor[seg] = y;
		if(Q->inicio==sinal)	
			Q->inicio = seg;
		Q->fim=seg;
	}
}

void popFila(Fila Q) {
	int seg = (Q->inicio+1)%MaxQ;
	if(Q->inicio!=sinal) {
		if(Q->inicio==Q->fim) {
			Q->fim=sinal;
			Q->inicio=sinal;
		}
		else {
			Q->inicio=seg;
		}
	}
}

void esvaziarFila(Fila Q) {
	Q->fim=sinal;
	Q->inicio=sinal;
}

int obterTamanho(Fila Q) {
	int cont=0;
	if(Q->inicio!=sinal) {
		int pos = Q->inicio;
		do {
			cont++;
			pos = (pos+1)%MaxQ;
		}while(pos!=(Q->fim+1)%MaxQ);	
	}
	
	return cont;
}

void mostrarFila(Fila Q) {
	printf("\n");
	if(Q->inicio!=sinal) {
		int pos = Q->inicio;
		do {
			printf("%d\t", Q->Vetor[pos]);
			pos = (pos+1)%MaxQ;
		}while(pos!=(Q->fim+1)%MaxQ);	
	}
	else{
		printf("Lista Vazia");
	}
	printf("\n");
}

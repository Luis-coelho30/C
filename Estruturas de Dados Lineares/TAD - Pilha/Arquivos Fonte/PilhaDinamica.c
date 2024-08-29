#include "Booleano.h"
#include <stdio.h>
#include <stdlib.h>

#define MaxPilha 5
#define sinal 0
#define fantasma '$'

typedef struct {
	int topo;
	unsigned char Vetor[MaxPilha];
}PilhaC;

typedef PilhaC *Pilha;

Pilha criarPilha();
bool PilhaVazia(Pilha);
unsigned char acessarPilha(Pilha);
void pushPilha(Pilha, unsigned char);
void popPilha(Pilha);
void esvaziarPilha(Pilha);
void mostrarPilha(Pilha);
int obterProfundidade(Pilha);
void inverter(Pilha);
void copy(Pilha, Pilha);

Pilha criarPilha() {
	Pilha ap = (Pilha)malloc(sizeof(Pilha));
	ap->topo = sinal;
	
	return ap;
}

bool PilhaVazia(Pilha A) {
	bool Vazio=FALSE;
	if(A->topo==sinal)
		Vazio=TRUE;
		
	return Vazio;
}

unsigned char acessarPilha(Pilha A) {
	unsigned char topo = fantasma;
	if(A->topo!=sinal)
		topo = A->Vetor[A->topo];
	
	return topo;
}

void pushPilha(Pilha A, unsigned char el) {
	int local;
	
	if(A->topo<MaxPilha-1){
		local = A->topo + 1;
		A->Vetor[local] = el;
		A->topo = local;
	}	
}

void popPilha(Pilha A) {
	if(A->topo!=sinal)
		A->topo = A->topo - 1;
}

void esvaziarPilha(Pilha A) {
	if(A->topo!=sinal)
		A->topo = sinal;
}

void mostrarPilha(Pilha A) {
	int i;
	for(i = A->topo; i!=sinal; i--) 
		printf("%c\n", A->Vetor[i]);
}

int obterProfundidade(Pilha A) {
	int tamanho;
	tamanho = A->topo;
	return tamanho;
}

void copy(Pilha Orig, Pilha Dest) {
	int i;
	Dest->topo=Orig->topo;
	for(i=1; i<=Orig->topo; i++)
		Dest->Vetor[i]=Orig->Vetor[i];
}

void inverter(Pilha A) {
	
	int i = 1, j = A->topo;
	unsigned char copia;
	while(i<j) {
		copia = A->Vetor[j];
		A->Vetor[j] = A->Vetor[i];
		A->Vetor[i] = copia; 
		i++;
		j--;
	}
}

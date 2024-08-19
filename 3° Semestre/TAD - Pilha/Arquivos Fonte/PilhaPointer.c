#include "Booleano.h"
#include <stdio.h>
#include <stdlib.h>

#define MaxPilha 10
#define sinal 0
#define fantasma '$'

typedef struct {
	int topo;
	unsigned char Vetor[MaxPilha];
}Pilha;

void criarPilha(Pilha *A);
bool PilhaVazia(Pilha *A);
unsigned char acessarPilha(Pilha *A);
void pushPilha(Pilha *A, unsigned char el);
void popPilha(Pilha *A);
void esvaziarPilha(Pilha *A);
void mostrarPilha(Pilha *A);
int obterProfundidade(Pilha *A);
int obterTamanho();
void copy(Pilha *Orig, Pilha *Dest);
void inverter(Pilha *A);

void criarPilha(Pilha *A) {
	A->topo = sinal;
}

bool PilhaVazia(Pilha *A) {
	bool Vazio=FALSE;
	if(A->topo==sinal)
		Vazio=TRUE;
		
	return Vazio;
}

unsigned char acessarPilha(Pilha *A) {
	unsigned char topo = fantasma;
	if(A->topo!=sinal)
		topo = A->Vetor[A->topo];
	
	return topo;
}

void pushPilha(Pilha *A, unsigned char el) {
	int local;
	
	if(A->topo<MaxPilha-1){
		local = A->topo + 1;
		A->Vetor[local] = el;
		A->topo = local;
	}	
}

void popPilha(Pilha *A) {
	if(A->topo!=sinal)
		A->topo = A->topo - 1;
}

void esvaziarPilha(Pilha *A) {
	if(A->topo!=sinal)
		A->topo = sinal;
}

void mostrarPilha(Pilha *A) {
	int i;
	for(i = A->topo; i>=1; i--) //(i = A->topo; i>=1; i--)
		printf("%c\n", A->Vetor[i]);
}

int obterProfundidade(Pilha *A) {
	int tamanho;
	tamanho = A->topo;
	return tamanho;
}

void copy(Pilha *Orig, Pilha *Dest) {
	
	int i;
	Dest->topo=Orig->topo;
	for(i=1; i<=Orig->topo; i++)
		Dest->Vetor[i]=Orig->Vetor[i];
	
}

void inverter(Pilha *A) {
	
	int i=1, j = A->topo;
	char aux;
	while(i<j) {
		aux = A->Vetor[i];
		A->Vetor[i]=A->Vetor[j];
		A->Vetor[j]=aux;
		i++;
		j--;
	}
}

int obterTamanho() {
	return MaxPilha-1;
}


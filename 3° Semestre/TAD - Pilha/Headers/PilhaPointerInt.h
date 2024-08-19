#include "Booleano.h"
#include <stdio.h>
#include <stdlib.h>

#define MaxPilha 101
#define sinal 0
#define fantasma -36

typedef struct {
	int topo;
	int Vetor[MaxPilha];
}Pilha;

void criarPilha(Pilha *A);
bool PilhaVazia(Pilha *A);
unsigned char acessarPilha(Pilha *A);
void pushPilha(Pilha *, int);
void popPilha(Pilha *A);
void esvaziarPilha(Pilha *A);
void mostrarPilha(Pilha *A);
int obterProfundidade(Pilha *A);
int obterTamanho();
void copy(Pilha *Orig, Pilha *Dest);
void inverter(Pilha *A);
void criarPilhaEmbaralhada(Pilha *A, int n);
void inverterParte(Pilha *A, int n);
int contarPilha(Pilha *A, int n);

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
	int topo = fantasma;
	if(A->topo!=sinal)
		topo = A->Vetor[A->topo];
	
	return topo;
}

void pushPilha(Pilha *A, int elem) {
	int local;
	
	if(A->topo<MaxPilha-1){
		local = A->topo + 1;
		A->Vetor[local] = elem;
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
		printf("%d\n", A->Vetor[i]);
}

int obterProfundidade(Pilha *A) {
	int tamanho;
	tamanho = A->topo;
	return tamanho;
}

void copy(Pilha *Orig, Pilha *Dest) {
	int i;
	Dest->topo = Orig->topo;
	for(i=1; i<=obterProfundidade(Orig); i++)
		Dest->Vetor[i] = Orig->Vetor[i];
	
}

void inverter(Pilha *A) {
	int i=1, j=obterProfundidade(A);
	int aux;
	while(i<j) {
		aux = A->Vetor[j];
		A->Vetor[j] = A->Vetor[i];
		A->Vetor[i] = aux;
		i++;
		j--;
	}
}

int obterTamanho() {
	return MaxPilha-1;
}

//Para pancakeSort
void criarPilhaEmbaralhada(Pilha *A, int n) {
	A->topo=n;
	int V[101];
	int rd;
	int aux;
	srand(time(NULL));
	int i;
	for(i=1; i<=n; i++)
		V[i]=i;
	
	do {
		rd = rand()%n + 1;
		aux = V[n];
		V[n] = V[rd];
		V[rd] = aux;
		n--;
	}while(n!=1);
	
	for(i=1; i<=A->topo; i++) {
		A->Vetor[i] = V[i];
	}
}

void inverterParte(Pilha *A, int n) {
	int i = A->topo - n + 1, j=A->topo;
	int aux;
	while(i<j) {
		aux = A->Vetor[j];
		A->Vetor[j] = A->Vetor[i];
		A->Vetor[i] = aux;
		i++;
		j--;
	}
}

int contarPilha(Pilha *A, int n) {
	int i=1, pos=0;
	while(i<=A->topo && A->Vetor[i]!=n) {
		i++;
	}
	if(A->Vetor[i]==n) 
		pos=A->topo - i;
		
	return pos;
}

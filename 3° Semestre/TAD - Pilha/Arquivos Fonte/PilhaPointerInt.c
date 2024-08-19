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
//treino
void subPilhaTopo(Pilha *A, Pilha *B, int n);
void subPilhaInicio(Pilha *A, Pilha *B, int n);
void subPilhaInt(Pilha *A, Pilha *B, int inicio, int fim);
//PancakeSort
void criarPilhaEmbaralhada(Pilha *A, int n);
void inverterParte(Pilha *A, int n);
int contarPilha(Pilha *A, int n);

int main() {
	
	Pilha A;
	criarPilha(&A);
	Pilha B;
	criarPilha(&B);
	Pilha C;
	criarPilha(&C);
	Pilha D;
	criarPilha(&D);
	pushPilha(&A, 1);
	pushPilha(&A, 5);
	pushPilha(&A, 1);
	pushPilha(&A, 3);
	pushPilha(&A, 7);
	mostrarPilha(&A);
	subPilhaTopo(&A, &B, 3);
	subPilhaInicio(&A, &C, 3);
	subPilhaInt(&A, &D, 2, 4);
	printf("\nA\n");
	mostrarPilha(&A);
	printf("\nB\n");
	mostrarPilha(&B);
	printf("\nC\n");
	mostrarPilha(&C);
	printf("\nD\n");
	mostrarPilha(&D);
	printf("\nTamanho A = %d\n", obterProfundidade(&A));
	printf("\nTamanho B = %d\n", obterProfundidade(&B));
	printf("\nTamanho C = %d\n", obterProfundidade(&C));
	printf("\nTamanho D = %d\n", obterProfundidade(&D));
	return 0;
}

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

void subPilhaTopo(Pilha *A, Pilha *B, int n) {
	/*
	int cont=0;
	Pilha Aux;
	criarPilha(&Aux);
	while(cont!=n) {
		pushPilha(&Aux, acessarPilha(A));
		popPilha(A);
		cont++;
	}
	while(PilhaVazia(&Aux)==FALSE) {
		pushPilha(A, acessarPilha(&Aux));
		pushPilha(B, acessarPilha(&Aux));
		popPilha(&Aux);
	}*/
	
	int inicio, j=0;
	for(inicio=A->topo - n + 1; inicio<=A->topo; inicio++) {
		j++;
		B->Vetor[j]=A->Vetor[inicio];
	}
	B->topo=j;
}

void subPilhaInicio(Pilha *A, Pilha *B, int n) {
	/*
	int cont=0;
	Pilha Aux;
	criarPilha(&Aux);
	while(PilhaVazia(A)==FALSE) {
		pushPilha(&Aux, acessarPilha(A));
		popPilha(A);
	}
	while(PilhaVazia(&Aux)==FALSE) {
		while(cont!=n) {
			pushPilha(A, acessarPilha(&Aux));
			pushPilha(B, acessarPilha(&Aux));
			cont++;
			popPilha(&Aux);
		}
		if(PilhaVazia(&Aux)==FALSE) {
			pushPilha(A, acessarPilha(&Aux));
			popPilha(&Aux);
		}
	}*/
	
	int inicio;
	for(inicio=1; inicio<=n; inicio++) {
		B->Vetor[inicio]=A->Vetor[inicio];
	}
	B->topo=n;
}

void subPilhaInt(Pilha *A, Pilha *B, int inicio, int fim) {
	Pilha Aux;
	criarPilha(&Aux);
	int cont;
	int tamanhoOriginal=obterProfundidade(A);
	cont=0;
	while(cont!=(tamanhoOriginal - inicio + 1)) {
		pushPilha(&Aux, acessarPilha(A));
		popPilha(A);
		cont++;
	}
	cont=0;
	while(PilhaVazia(&Aux)==FALSE) {
		while(cont!=fim-inicio+1) {
			pushPilha(A, acessarPilha(&Aux));
			pushPilha(B, acessarPilha(&Aux));
			popPilha(&Aux);
			cont++;
		}
		if(PilhaVazia(&Aux)==FALSE) {
			pushPilha(A, acessarPilha(&Aux));
			popPilha(&Aux);
		}
	}
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
	/*
	int i = A->topo - n + 1, j=A->topo;
	int aux;
	while(i<j) {
		aux = A->Vetor[j];
		A->Vetor[j] = A->Vetor[i];
		A->Vetor[i] = aux;
		i++;
		j--;
	}
	*/
	if(n>1) {
		Pilha Aux1, Aux2;
		criarPilha(&Aux1);
		criarPilha(&Aux2);
		while(obterProfundidade(&Aux1)!=n){
			pushPilha(&Aux1, acessarPilha(A));
			popPilha(A);
		}
		while(obterProfundidade(&Aux2)!=n){
			pushPilha(&Aux2, acessarPilha(&Aux1));
			popPilha(&Aux1);
		}
		while(PilhaVazia(&Aux2)==FALSE){
			pushPilha(A, acessarPilha(&Aux2));
			popPilha(&Aux2);
		}
	}
}

int contarPilha(Pilha *A, int n) {
	int i=A->topo, pos=0;
	while(i>=1 && A->Vetor[i]!=n) {
		i--;
	}
	if(A->Vetor[i]==n) 
		pos=A->topo - i + 1;
		
	return pos;
}

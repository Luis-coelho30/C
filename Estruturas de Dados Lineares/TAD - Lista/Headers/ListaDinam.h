#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"

#define MAX 101

typedef struct {
	int tamanho;
	char Vetor[MAX];
}ListaC;

typedef ListaC *Lista;

Lista criarLista();
int obterTamanho(Lista);
void mostrarLista(Lista);
void inserir(Lista, char);
void remover(Lista);
void reverse(Lista);
void copy(Lista, Lista);

Lista criarLista() {
	Lista A = (Lista) malloc(sizeof(Lista));
	A->tamanho=0;
	
	return A;
}

int obterTamanho(Lista A) {
	int tamanho = A->tamanho;
	return tamanho;
}

void mostrarLista(Lista A){
	int i;
	if(A->tamanho>0)
		for(i=1; i<=A->tamanho; i++)
			printf("%c\t", A->Vetor[i]);
			
	else
		printf("Lista Vazia\n");
}

void inserir(Lista A, char el) {
	int local;
	if(A->tamanho<MAX-1) {
		local = A->tamanho + 1;
		A->Vetor[local] = el;
		A->tamanho = local;
	}
}

void remover(Lista A) {
	int tamanho = 0;
	if(A->tamanho>0)
		tamanho = A->tamanho - 1;
	
	A->tamanho = tamanho;
}

void reverse(Lista A) {
	int i=1, j=A->tamanho;
	char store;
	while(i<j) {
		store = A->Vetor[j];
		A->Vetor[j] = A->Vetor[i];
		A->Vetor[i] = store;
		i++;
		j--;
	}
}

void copy(Lista Orig, Lista Dest) {
	int i;
	Dest->tamanho = Orig->tamanho;
	for(i=1; i<=Orig->tamanho; i++)
		Dest->Vetor[i] = Orig->Vetor[i]; 
}

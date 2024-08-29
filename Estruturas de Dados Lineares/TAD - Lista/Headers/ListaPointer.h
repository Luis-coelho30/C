#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"

#define MAX 101

typedef struct {
	int tamanho;
	char vetor[MAX];
}Lista;

void criarLista(Lista *A);
int obterTamanho(Lista *A);
void mostrarLista(Lista *A);
void inserir(Lista *A, char el);
void remover(Lista *A);
void reverse(Lista *A);
void inserirPos(Lista *A, char el, int pos);
void removeElemento(Lista *A, char el);

void criarLista(Lista *A) {
	A -> tamanho = 0;
}

int obterTamanho(Lista *A) {
	int tamanho = A->tamanho;
	
	return tamanho;
}

void mostrarLista(Lista *A){
	int i;
	if(A->tamanho>0)
		for(i=1; i<=A->tamanho; i++)
			printf("%c\t", A->vetor[i]);
			
	else
		printf("Lista Vazia\n");
}

void inserir(Lista *A, char el) {
	int local;
	if(A->tamanho<MAX-1) {
		local = A->tamanho + 1;
		A->vetor[local] = el;
		A->tamanho = local;
	}
}

void remover(Lista *A) {
	int tamanho = 0;
	if(A->tamanho>0)
		tamanho = A->tamanho - 1;
	
	A->tamanho = tamanho;
}

void reverse(Lista *A) {
	int i = 1, j=A->tamanho;
	char copia;
	while(i<j) {
		copia = A->vetor[j];
		A->vetor[j] = A->vetor[i];
		A->vetor[i] = copia;
		i++;
		j--;
	}
}

void inserirPos(Lista *A, char el, int pos) {
	int i;
	if(pos>0 && pos<=A->tamanho)
		if(A->tamanho<MAX-1) {
			for(i=A->tamanho; i>=pos; i--)
				A->vetor[i+1]=A->vetor[i];
			A->vetor[pos]=el;
			A->tamanho = A->tamanho + 1;
		}
}

void removeElemento(Lista *A, char el) {
	int i = 1, j = A->tamanho;
	int cont = 0;

	while (i < j) {
    	if (A->vetor[i] == el && A->vetor[j] != el) {
    	    // Troca os elementos i e j
    	    int temp = A->vetor[i];
    	    A->vetor[i] = A->vetor[j];
    	    A->vetor[j] = temp;
    	    i++;
    	    j--;
    	} 
		
		else if (A->vetor[j] == el) { //Se o final for um elemento
    	    j--;
    	} 
		
		else { 
    	    i++;
    	}
	}

	int n;
	for(n = 1; A->vetor[n]!=el; n++) {
		cont++;
	}

	A->tamanho = cont;
}

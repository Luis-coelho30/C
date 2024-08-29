#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"

#define MAX 101

typedef struct {
	int tamanho;
	char vetor[MAX];
}Lista;

Lista criarLista();
int obterTamanho(Lista A);
void mostrarLista(Lista A);
Lista inserir(Lista A, char el);
Lista remover(Lista A);
Lista reverse(Lista A);
Lista copy(Lista A);
Lista construirLista(Lista A, int tam);
Lista extend(Lista Fonte, Lista Alvo);
Lista inserirPos(Lista A, int pos, char el);
Lista removeElemento(Lista A, char el);

Lista criarLista() {
	Lista A;
	A.tamanho = 0;
	return A;
}

int obterTamanho(Lista A) {
	int tamanho = A.tamanho;
	return tamanho;
}

void mostrarLista(Lista A){
	int i;
	printf("\n");
	if(A.tamanho>0)
		for(i=1; i<=A.tamanho; i++)
			printf("%c\t", A.vetor[i]);
			
	else
		printf("Lista Vazia\n");
	printf("\n");
}

Lista inserir(Lista A, char el) {
	int local;
	if(A.tamanho<MAX-1) {
		local = A.tamanho + 1;
		A.vetor[local] = el;
		A.tamanho = local;
	}
	return A;
}

Lista remover(Lista A) {
	int tamanho = 0;
	if(A.tamanho>0)
		tamanho = A.tamanho - 1;
	
	A.tamanho = tamanho;
	return A;
}

Lista reverse(Lista A) {
	int i = 1, j=A.tamanho;
	char copia;
	while(i<j) {
		copia = A.vetor[j];
		A.vetor[j] = A.vetor[i];
		A.vetor[i] = copia;
		i++;
		j--;
	}
	return A;
}

Lista copy(Lista A) {
	int i;
	Lista B;
	B.tamanho = A.tamanho;
	
	if(A.tamanho>0)
		for(i=1; i<=A.tamanho; i++) {
			B.vetor[i]=A.vetor[i];
		}
	return B;
}

Lista construirLista(Lista A, int tam) {
	int i;
	for(i=1; i<=tam; i++) {
		A.vetor[i]=64 + i;
		A.tamanho = A.tamanho + 1;
	}
	return A;
}

Lista extend(Lista Fonte, Lista Alvo) {
	int tamanho = Alvo.tamanho;
	Alvo.tamanho = Alvo.tamanho + Fonte.tamanho;
	int i, j=0;
	for(i=tamanho+1; i<=Alvo.tamanho; i++) {
		j++;
		Alvo.vetor[i]=Fonte.vetor[j];
	}
	return Alvo;
}

Lista inserirPos(Lista A, int pos, char el) {
	int i;
	if(pos>0 && pos<=A.tamanho)
		if(A.tamanho<MAX-1) {
			for(i=A.tamanho; i>=pos; i--)
				A.vetor[i+1]=A.vetor[i];
			A.vetor[pos]=el;
			A.tamanho = A.tamanho + 1;
		}
	return A;
}

Lista removeElemento(Lista A, char el) {
	int i = 1, j = A.tamanho;
	int cont = 0;

	while (i < j) {
    	if (A.vetor[i] == el && A.vetor[j] != el) {
    	    // Troca os elementos i e j
    	    int temp = A.vetor[i];
    	    A.vetor[i] = A.vetor[j];
    	    A.vetor[j] = temp;
    	    i++;
    	    j--;
    	} 
		
		else if (A.vetor[j] == el) { //Se o final for um elemento
    	    j--;
    	} 
		
		else { 
    	    i++;
    	}
	}

	int n;
	for(n = 1; A.vetor[n]!=el; n++) {
		cont++;
	}

	A.tamanho = cont;
	return A;
}

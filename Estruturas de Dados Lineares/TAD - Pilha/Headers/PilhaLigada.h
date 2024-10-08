//Tipo abstrato de dados Pilha implementado por meio de uma lista simplesmente ligada sem cabeca.
#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"
#define ghost -1

typedef struct Celula{
        int item;
        struct Celula* next;
}Celula;

typedef Celula* Pilha;

Pilha criarPilhaVazia();                   	
bool verPilhaVazia(Pilha);             
int obterProfundidade(Pilha);              		
void mostrarPilha(Pilha);
int peek(Pilha);              						
void push(Pilha*, int);           	
void pop(Pilha*);
void esvaziaPilha(Pilha*);

Pilha criarPilhaVazia() {
	Pilha A;
	A=NULL;
	
	return A;
}            
       	
bool verPilhaVazia(Pilha A) {
	bool vazia = FALSE;
	
	if(A==NULL)
		vazia=TRUE;
		
	return vazia;
}            

int obterProfundidade(Pilha ap) {
	Celula *p = ap;
	int cont=0;
	while(p!=NULL) {
		cont++;
		p = p->next;
	}
	
	return cont;
}              	

void mostrarPilha(Pilha ap) {
	Celula *p = ap;
	printf("\n");
	while(p!=NULL) {
		printf("%d\n", p->item);
		p = p->next;
	}	
	printf("\n");
}   

int peek(Pilha ap) {
	Celula *p = ap;
	int elemento = ghost;
	if(p!=NULL) {
		elemento = p->item;
	}
	return elemento;
}   
		
void push(Pilha *ap, int y) {
	Celula *nova = (Celula*)malloc(sizeof(Celula));
	nova->item=y;
	nova->next = *ap;
	*ap = nova;
}

void pop(Pilha *ap) {
	Celula *aux = *ap;
	if(aux!=NULL) {
		*ap = aux->next;
		free(aux);
	}
}

void esvaziaPilha(Pilha *ap) {
	Celula *p = *ap;
	Celula *aux;
	while(p!=NULL) {
		aux = p;
		p = p->next;
		free(aux);
	}	
	*ap=NULL;
}
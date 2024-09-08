#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"
#define ghost -1

typedef struct Cel{
    void *item;
    struct Cel* next;
}Cel;

typedef Cel* Pilha;

Pilha criarPilhaVazia();                   	
bool verPilhaVazia(Pilha);             
int obterProfundidade(Pilha);              		
void *peek(Pilha);              						
void push(Pilha*, void *);           	
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
	Cel *p = ap;
	int cont=0;
	while(p!=NULL) {
		cont++;
		p = p->next;
	}
	
	return cont;
}              	

void *peek(Pilha ap) {
	Cel *aux;
    void *valor;
    aux = ap; 
    if (aux == NULL) 
        valor = NULL;
    else 
        valor = aux->item;
    return valor;
}   
		
void push(Pilha *ap, void *y) {
	Cel *nova = (Cel*)malloc(sizeof(Cel));
	nova->item=y;
	nova->next = *ap;
	*ap = nova;
}

void pop(Pilha *ap) {
	Cel *aux = *ap;
	if(aux!=NULL) {
		*ap = aux->next;
		free(aux);
	}
}

void esvaziaPilha(Pilha *ap) {
	Cel *p = *ap;
	Cel *aux;
	while(p!=NULL) {
		aux = p;
		p = p->next;
		free(aux);
	}	
	*ap=NULL;
}
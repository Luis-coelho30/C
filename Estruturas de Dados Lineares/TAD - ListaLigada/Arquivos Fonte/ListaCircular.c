#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"
#define ghost -1

typedef struct Celula{
        int item;
        struct Celula* next;
}Celula;

typedef Celula* Lista;

/* INTERFACE */

Lista criarLista();                   	
bool verListaVazia(Lista);             
int obterTamanho(Lista);              	
int localizarElemento(Lista, int);		

//Acesso
void mostrarLista(Lista);              				
int obterElemento(Lista, int);			

//Manipulacao
void inserir(Lista*, int);           	
void inserirUltimo(Lista*, int);
void remover(Lista*);
void removerUltimo(Lista*);		

int main() {
	Lista A = criarLista();
	inserir(&A, 12);
	inserir(&A, 133);
	inserirUltimo(&A, 122);
	mostrarLista(A);
	removerUltimo(&A);
	mostrarLista(A);
	printf("\n%d\n", A->next->next->item);
	return 0;
}

Lista criarLista() {
	Lista A;
	A = NULL;
	
	return A;
}          	
bool verListaVazia(Lista ap) {
	bool vazia = FALSE;
	
	if(ap==NULL)
		vazia = TRUE;
		
	return vazia;	
}             

int obterTamanho(Lista ap) {
	Celula *p;
	int tamanho=0;
	p = ap;
	if(ap!=NULL) {
		do {
			tamanho++;
			p = p->next;
		}while(p!=ap);	
	}
	
	return tamanho;
}             	

int localizarElemento(Lista ap, int y) {
	Celula *p;
	int local=0;
	p = ap;
	
	if(p!=NULL) {
		if(p->item==y) {
			local++;
		}
		else {
			p = p->next;	
			while(p!=ap && p->item!=y) {
				local++;
				p = p->next;
			}	
		}
	}
	
	return local;
}	

void mostrarLista(Lista ap) {
	Celula *p;
	printf("\n");
	p = ap;
	
	if(ap!=NULL) {
		do {
			printf("%d\t", p->item);
			p = p->next;	
		}while(p!=ap);
	}
	else
		printf("Lista Vazia.");
		
	printf("\n");
}              				

int obterElemento(Lista ap, int y) {
	Celula *p;
	int el=ghost;
	int cont=0;
	p = ap;
	
	if(p!=NULL) {
		
		if(y==1) {
			el=p->item;
		}
		
		else {
			cont++;
			p = p->next;	
			while(p!=ap && cont!=y) {
				p = p->next;
				cont++;
			}
			if(cont==y) 
				el=p->item;		
		}
	}
	
	return el;
}

void inserir(Lista *ap, int y) {
	Celula *nova = malloc(sizeof(Celula));
    nova->item = y;
    
    if (*ap == NULL) {
        nova->next = nova;
        *ap = nova;
    } else {
        Celula *p = *ap;
        while (p->next != *ap) {
            p = p->next;
        }
        nova->next = *ap;
		p->next = nova;
        *ap = nova;
    }
}

void inserirUltimo(Lista *ap, int y) {
	Celula *nova = malloc(sizeof(Celula));
    nova->item = y;
    
    if (*ap == NULL) {
        nova->next = nova;
        *ap = nova;
    } else {
        Celula *p = *ap;
        while (p->next != *ap) {
			p = p->next;
        }
        p->next = nova;
        nova->next = *ap;
    }
}

void remover(Lista *ap) {
	if(*ap!=NULL) {
		Celula *p = *ap;
		if(p->next==*ap) {
			*ap = NULL;
			free(p);
		}
		else {
        	while (p->next != *ap) {
				p = p->next;
        	}
			Celula *prim = *ap;
			p->next = prim->next; //Ultimo aponta para o segundo
			*ap = p->next;	//Primeiro elemento vira o apontado pelo ultimo	  	
			free(prim); //Apaga o primeiro elemento
		}
    } 
}

void removerUltimo(Lista *ap) {
	if(*ap!=NULL) {
		Celula *p = *ap;
		if(p->next==*ap) {
			*ap = NULL;
			free(p);
		}
		else {
			Celula *prev;
			while(p->next!=*ap) {
				prev = p;
				p = p->next;
			}
			prev->next = p->next;
			free(p);
		}
    } 
}

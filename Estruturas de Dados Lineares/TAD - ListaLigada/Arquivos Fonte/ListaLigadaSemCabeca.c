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
Celula* buscarElemento(Lista, int);

//Manipulacao
void inserir(Lista*, int);           	
void inserirUltimo(Lista*, int);
void remover(Lista*);
void removerUltimo(Lista*);
void esvaziaLista(Lista*);
void removeDesordenado(Lista*);  	
void inserirOrdenado(Lista*, int);	//Exclusivamente em listas ordenadas		
void trocarCelulas(Lista*,Celula*,Celula*); //As celulas estao na lista

bool verificarIgual(Lista, Lista);  //Para listas sem duplicatas

int main() {
	Lista A = criarLista();		Lista B = criarLista();
	inserir(&A, 26);			inserir(&B, 26);
	inserir(&A, 44);			inserir(&B, 56);
	inserir(&A, 56);			inserir(&B, 44);
	inserir(&A, 12);			inserir(&B, 12);
	mostrarLista(A);			mostrarLista(B);

	printf("A lista A %s a lista B ", verificarIgual(A, B) ? "eh igual" : "nao eh igual");
	
	return 0;
}

Lista criarLista() {
	Lista A;
	A=NULL;
	
	return A;
}            
       	
bool verListaVazia(Lista A) {
	bool vazia = FALSE;
	
	if(A==NULL)
		vazia=TRUE;
		
	return vazia;
}            

int obterTamanho(Lista ap) {
	Celula *p = ap;
	int cont=0;
	while(p!=NULL) {
		cont++;
		p = p->next;
	}
	
	return cont;
}              	

int localizarElemento(Lista ap, int y) {
	Celula *p = ap;
	int cont=0, pos=0;
	while(p!=NULL && p->item!=y) {
		cont++;
		p = p->next;
	}
	if(p!=NULL)
		pos = cont+1;
		
	return pos;
}	

void mostrarLista(Lista ap) {
	Celula *p = ap;
	printf("\n");
	while(p!=NULL) {
		printf("%d\t", p->item);
		p = p->next;
	}	
	printf("\n");
}            
				
int obterElemento(Lista ap, int y) {
	Celula *p = ap;
	int cont=1;
	int el=ghost;
	while(p!=NULL && cont!=y) {
		cont++;
		p = p->next;
	}
	if(p!=NULL) {
		el = p->item;	
	}
		
		
	return el;
}	
		
Celula* buscarElemento(Lista ap, int y) {
	Celula *p = ap;
	Celula *alvo = NULL;
	while(p!=NULL && p->item!=y) {
		p = p->next;
	}
	if(p!=NULL)
		alvo = p;
		
	return alvo;
}

void inserir(Lista *ap, int y) {
	Celula *nova = malloc(sizeof(Celula));
	nova->item=y;
	nova->next = *ap;
	*ap = nova;
}

void inserirUltimo(Lista *ap, int y) {
	Celula *nova = malloc(sizeof(Celula));
	nova->item=y;
	nova->next = NULL;
	
	Celula *p = *ap;
	if(p!=NULL) {
		while(p->next!=NULL) {
			p = p->next;
		}
		p->next = nova;
	}
	
	else {
		*ap = nova;
	}
}

void remover(Lista *ap) {
	Celula *aux = *ap;
	if(aux!=NULL) {
		*ap = aux->next;
		free(aux);
	}
}

void removerUltimo(Lista *ap) {
	if(*ap!=NULL) {
		Celula *atual = *ap;
		if(atual->next!=NULL) {
			Celula *prev = atual;
			atual = atual->next;
			while(atual->next!=NULL) {
			prev = atual;
			atual = atual->next;
			}
			prev->next=NULL;
			free(atual);
		}	
		else {
			*ap = NULL;
			free(atual);
		}
	}	
	
}

void esvaziaLista(Lista *ap) {
	Celula *p = *ap;
	Celula *aux;
	while(p!=NULL) {
		aux = p;
		p = p->next;
		free(aux);
	}	
	*ap=NULL;
}

void removeDesordenado(Lista *ap) {
	Celula *p = *ap;
	Celula *ant=NULL;
	
	if(p!=NULL) {
		ant = p;
		p = p->next;
		while(p!=NULL && ant->item<=p->item) {
			ant = p;
			p = p->next;
			}
		if(ant==*ap && p!=NULL) { 
			*ap = p;
			free(ant);
		}
		else if(ant!=*ap){ 	
			ant->next = p->next;
			free(p);
		}	
	}
}  	

void inserirOrdenado(Lista *ap, int y) {
	Celula *nova = malloc(sizeof(Celula));
	nova->item = y;
	
	Celula *p = *ap;
	Celula *ant=NULL;
	while(p!=NULL && p->item<y) {
		ant = p;
		p = p->next;
	}
	if(ant==NULL) { 
		nova->next = *ap;
		*ap = nova;
	}
	else { 	
		nova->next = p;
		ant->next = nova;
	}
}	

void trocarCelulas(Lista *ap, Celula *cel1, Celula *cel2) {
	if(cel1!=NULL && cel2!=NULL) {
		Celula *p=*ap;
		Celula *prev1=NULL;
		Celula *prev2=NULL;
		if(p!=NULL) {
			while(p->next!=NULL && (prev1==NULL || prev2==NULL)) {
				if(p->next==cel1) {
					prev1 = p;
				}
				else if(p->next==cel2) {
					prev2 = p;
				}
				p = p->next;
			}
			
			if (*ap == cel1) {
            	*ap = cel2;
        	} else if (*ap == cel2) {
            	*ap = cel1;
        	}
			
			if(prev1!=NULL) { 
				prev1->next=cel2;
			} 
		
			if(prev2!=NULL) { 
				prev2->next=cel1; 
			} 
		
			Celula *aux;
			aux = cel2->next;
			cel2->next = cel1->next;
			cel1->next = aux;	
		}
	}
}

bool verificarIgual(Lista A, Lista B)
{
	bool igual;
	Celula *p, *q;
	if ((A == NULL) && (B == NULL))
		igual = TRUE;
	else
	{
		if ((A == NULL) || (B == NULL))
			igual = FALSE;
		else
		{
			igual = TRUE;
			p = A;
			do
			{
				q = B;
				while ((p->item != q->item) && (q->next != NULL))
					q = q->next;
				if (p->item != q->item)
					igual = FALSE;
				else
					p = p->next;
			} while ((p != NULL) && (igual == TRUE));
			if (igual == TRUE)
			{
				p = B;
				do
				{
					q = A;
					while ((p->item != q->item) && (q->next != NULL))
						q = q->next;
					if (p->item != q->item)
						igual = FALSE;
					else
						p = p->next;
				} while ((p != NULL) && (igual == TRUE));
			}
		}
	}
	return igual;
}

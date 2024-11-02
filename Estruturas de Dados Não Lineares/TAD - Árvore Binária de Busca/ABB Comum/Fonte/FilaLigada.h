#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"
#define ghost -1

typedef struct Celula
{
	void *elemento;
	struct Celula *suc;
	struct Celula *pre;
} Celula;

typedef struct
{
	int tamanho;
	Celula *inicio;
	Celula *fim;
} Fila;

Fila criarFila();					 
bool verFilaVazia(Fila *);		 
int obterTamanho(Fila *);			 	
void pushFila(Fila *, void *);
void popFila(Fila *);
void esvaziarFila(Fila *);

Fila criarFila()
{
	Fila A;
	A.fim = NULL;
	A.inicio = NULL;
	A.tamanho = 0;

	return A;
}

bool verFilaVazia(Fila *ap)
{
	bool vazio = FALSE;

	if (ap->inicio == NULL)
		vazio = TRUE;

	return vazio;
}

int obterTamanho(Fila *ap)
{
	return ap->tamanho;
}

void *acessarFila(Fila *qp) {
	Celula *aux;
    void *valor;
    aux = qp->inicio; 
    if (aux == NULL) 
        valor = NULL;
    else 
        valor = aux->elemento;
    return valor;
}

void pushFila(Fila *ap, void *y)
{
	Celula *nova;
	nova = (Celula*) malloc(sizeof(Celula));
	nova->elemento = y;
	Celula *p;

	if (ap->inicio == NULL)
	{
		nova->pre = NULL;
		nova->suc = NULL;
		ap->inicio = nova;
	}

	else
	{
		p = ap->fim;
		p->suc = nova;
		nova->pre = p;
		nova->suc = NULL;
	}

	ap->fim = nova;

	ap->tamanho++;
}

void popFila(Fila *ap)
{
	if (ap->inicio != NULL)
	{
		Celula *aux;
		Celula *removida;
		removida = ap->inicio;
		aux = removida->suc;

		if (aux != NULL)
		{
			aux->pre = NULL;
		}
		else
		{
			ap->fim = NULL;
		}

		ap->inicio = aux;

		free(removida);
		ap->tamanho--;
	}
}

void esvaziarFila(Fila *ap)
{
	Celula *p = ap->inicio;
	Celula *temp;

	while (p != NULL)
	{
		temp = p;
		p = p->suc;
		free(temp);
	}
	ap->inicio = NULL;
	ap->fim = NULL;
	ap->tamanho = 0;
}
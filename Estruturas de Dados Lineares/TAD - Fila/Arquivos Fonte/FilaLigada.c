#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"
#define ghost -1

typedef struct Celula
{
	int elemento;
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
void mostrarFila(Fila *);		 
void pushFila(Fila *, int);
void popFila(Fila *);
int peekFila(Fila *);
void esvaziarFila(Fila *);

int main()
{
	Fila A = criarFila();
	pushFila(&A, 12);
	pushFila(&A, 15);
	mostrarFila(&A);
	popFila(&A);
	mostrarFila(&A);

	return 0;
}

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

void mostrarFila(Fila *ap)
{
	Celula *p = ap->inicio;

	if (ap->inicio == NULL)
	{
		printf("\nFila Vazia\n");
	}
	else
	{
		do
		{
			printf("%d\t", p->elemento);
			p = p->suc;
		} while (p != NULL);
	}

	printf("\n");
}

void pushFila(Fila *ap, int y)
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

int peekFila(Fila *ap) {
	Celula *p = ap->inicio;
	int elemento = ghost;
	if(p!=NULL) {
		elemento = p->elemento;
	}
	return elemento;
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
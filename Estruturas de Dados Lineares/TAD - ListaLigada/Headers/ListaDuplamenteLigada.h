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
} Lista;

Lista criarLista();					 // cria uma lista vazia
bool verListaVazia(Lista *);		 // devolve TRUE se a lista eh vazia
int obterTamanho(Lista *);			 // devolve o tamanho da lista
int localizarElemento(Lista *, int); // devolve a ordem do registro que contem y ou zero
void mostrarLista(Lista *);		 // mostra na tela os elementos da lista
int obterElemento(Lista *, int); // obtem o elemento na posicao pos
void inserir(Lista *, int); // acrescenta um novo elemento ao inicio da lista
void inserirUltimo(Lista *, int);
void remover(Lista *);
void removerUltimo(Lista *);
void buscaRemove(Lista *, int);				   // Remove a primeira ocorrência da célula que contém y
void buscaInsere(Lista *, int);				   // Insere no início uma célula com o valor y somente se esse valor não ocorre na lista.
void trocarCelulas(Lista *, Celula *, Celula *); // Troca a posição das duas células. Suponha que as referências sejam válidas, diferentes de NULL
void esvaziarLista(Lista *);
bool verificarCrescente(Lista);		  // Verifica se a lista está em ordem crescente. Suponha que a lista não contenha duplicatas
void concatenarListasPointer(Lista *, Lista *); // Concatena as duas listas na ordem dos parâmetros e devolve a segunda lista vazia
Lista separarLista(Lista *, int);			  // Divide a lista em duas listas, de modo que a segunda lista comece no primeiro elemento
											  // após a primeira ocorrência de y na lista original. A lista original deve conter y como último elemento

Lista criarLista()
{
	Lista A;
	A.fim = NULL;
	A.inicio = NULL;
	A.tamanho = 0;

	return A;
}

bool verListaVazia(Lista *ap)
{
	bool vazio = FALSE;

	if (ap->inicio == NULL)
		vazio = TRUE;

	return vazio;
}

int obterTamanho(Lista *ap)
{
	Celula *p;
	p = ap->inicio;
	int cont = 0;

	while (p != NULL)
	{
		cont++;
		p = p->suc;
	}

	return cont;
}

int localizarElemento(Lista *ap, int elem)
{
	int pos = 0;
	Celula *p = ap->inicio;
	int cont = 1;

	while (p != NULL && p->elemento != elem)
	{
		cont++;
		p = p->suc;
	}
	if (p != NULL)
		pos = cont;

	return pos;
}

int obterElemento(Lista *ap, int pos)
{
	int elem = -1;
	Celula *p = ap->inicio;

	while (p != NULL && pos != 1)
	{
		pos--;
		p = p->suc;
	}
	if (p != NULL)
		elem = p->elemento;

	return elem;
}

void mostrarLista(Lista *ap)
{
	Celula *p = ap->inicio;

	if (ap->inicio == NULL)
	{
		printf("\nLista Vazia\n");
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

void inserir(Lista *ap, int y)
{
	Celula *nova;
	nova = (Celula*) malloc(sizeof(Celula));
	nova->pre = NULL;
	nova->suc = ap->inicio;
	nova->elemento = y;

	if (ap->inicio == NULL)
		ap->fim = nova;

	else
	{
		Celula *aux;
		aux = ap->inicio;
		aux->pre = nova;
	}

	ap->inicio = nova;

	ap->tamanho++;
}

void inserirUltimo(Lista *ap, int y)
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

void remover(Lista *ap)
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

void removerUltimo(Lista *ap)
{
	if (ap->inicio != NULL)
	{
		Celula *aux;
		Celula *removida;
		removida = ap->fim;
		aux = removida->pre;

		if (aux != NULL)
		{
			aux->suc = NULL;
			ap->fim = aux;
		}

		else
		{
			ap->fim = NULL;
			ap->inicio = NULL;
		}

		free(removida);
		ap->tamanho--;
	}
}

void buscaRemove(Lista *ap, int y)
{
	if (ap->inicio != NULL)
	{
		Celula *p;
		p = ap->inicio;
		while (p != NULL && p->elemento != y)
			p = p->suc;
		if (p != NULL)
		{
			Celula *ant;
			Celula *pos;
			ant = p->pre;
			pos = p->suc;

			if (ant != NULL)
				ant->suc = pos;
			else
				ap->inicio = pos;

			if (pos != NULL)
				pos->pre = ant;
			else
				ap->fim = ant;

			free(p);

			ap->tamanho--;
		}
	}
}

void buscaInsere(Lista *ap, int y)
{
	Celula *p;
	p = ap->inicio;

	while (p != NULL && p->elemento != y)
	{
		p = p->suc;
	}
	if (p == NULL)
	{
		Celula *nova;
		nova = (Celula*) malloc(sizeof(Celula));
		nova->elemento = y;
		nova->pre = NULL;
		nova->suc = ap->inicio;

		if (ap->inicio == NULL)
			ap->fim = nova;

		else
		{
			Celula *aux;
			aux = ap->inicio;
			aux->pre = nova;
		}

		ap->inicio = nova;
		ap->tamanho++;
	}
}

void trocarCelulas(Lista *ap, Celula *cel1, Celula *cel2)
{
	// Cel no inicio atualiza ap->inicio
	// Cel no fim atualiza ap->fim
	// Cel no meio atualiza cel->pre e cel->pos

	Celula *prev1 = cel1->pre;
	Celula *suc1 = cel1->suc;
	Celula *prev2 = cel2->pre;
	Celula *suc2 = cel2->suc;

	if (prev1 != NULL)
	{
		prev1->suc = cel2;
	}
	else
		ap->inicio = cel2;

	if (suc1 != NULL)
	{
		suc1->pre = cel2;
	}
	else
		ap->fim = cel2;

	if (prev2 != NULL)
	{
		prev2->suc = cel1;
	}
	else
		ap->inicio = cel1;

	if (suc2 != NULL)
	{
		suc2->pre = cel1;
	}
	else
		ap->fim = cel1;

	cel1->pre = prev2;
	cel1->suc = suc2;
	cel2->pre = prev1;
	cel2->suc = suc1;
}

void esvaziarLista(Lista *ap)
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

void concatenarListasPointer(Lista *ap, Lista *bp)
{
	if (bp->inicio != NULL)
	{
		if (ap->inicio != NULL)
		{
			Celula *p = ap->fim;
			Celula *b = bp->inicio;
			p->suc = b;
			b->pre = p;
			ap->fim = bp->fim;
			ap->tamanho = ap->tamanho + bp->tamanho;
		}
		else
		{
			ap->inicio = bp->inicio;
			ap->fim = bp->fim;
			ap->tamanho = bp->tamanho;
		}

		bp->inicio = NULL;
		bp->fim = NULL;
		bp->tamanho = 0;
	}
}

Lista separarLista(Lista *ap, int y)
{
	Lista sublista;
	sublista.inicio = NULL;
	sublista.fim = NULL;
	sublista.tamanho = 0;
	int cont = 0;

	Celula *p = ap->inicio;
	while (p != NULL && p->elemento != y)
	{
		cont++;
		p = p->suc;
	}

	if (p != NULL)
	{
		sublista.inicio = p->suc;
		sublista.inicio->pre = NULL;
		sublista.fim = ap->fim;
		sublista.tamanho = ap->tamanho - cont;

		p->suc = NULL;
		ap->fim = p;
		ap->tamanho = cont;
	}

	return sublista;
}

bool verificarCrescente(Lista A)
{
	Celula *atual;
	Celula *ant;
	bool crescente = TRUE;

	if (A.inicio != NULL)
	{
		atual = A.inicio;

		if (atual->suc != NULL)
		{
			ant = atual;
			atual = atual->suc;
			while (atual->suc != NULL && atual->elemento > ant->elemento)
			{
				ant = atual;
				atual = atual->suc;
			}
			if (atual->elemento < ant->elemento)
			{
				crescente = FALSE;
			}
		}
	}

	return crescente;
}
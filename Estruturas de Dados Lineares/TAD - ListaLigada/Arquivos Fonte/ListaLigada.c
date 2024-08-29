#include <stdlib.h>
#include <stdio.h>
#include "Booleano.h"
#define ghost -1

typedef struct Celula{
        int item;
        struct Celula* next;
}Celula;

typedef struct{
        int tamanho;
        Celula* inicio;
}Lista;

Lista criarLista();                   	// cria uma lista vazia	
bool verListaVazia(Lista*);             // devolve TRUE se a lista eh vazia
int obterTamanho(Lista*);              	// devolve o tamanho da lista
int localizarElemento(Lista*, int);		// devolve a ordem do registro que contem y ou zero
void mostrarLista(Lista*);              // mostra na tela os elementos da lista					
int obterElemento(Lista*, int);			//obtem o elemento na posicao pos
Celula* buscarElemento(Lista, int);		//obtem a celula onde a primeira instancia de um elemento esta. Devolve NULL se o elemento nao estiver na lista.
void inserir(Lista*, int);           	// acrescenta um novo elemento ao inicio da lista
void inserirUltimo(Lista*, int);
void remover(Lista*);
void removerUltimo(Lista*);
void buscaRemove(Lista*, int);  		// Remove a primeira ocorr�ncia da c�lula que cont�m y
void buscaInsere(Lista*, int);			// Insere no in�cio uma c�lula com o valor y somente se esse valor n�o ocorre na lista.
void trocarCelulas(Lista*,Celula*,Celula*);  // Troca a posi��o das duas c�lulas. Suponha que as refer�ncias sejam v�lidas, diferentes de NULL  
bool verificarCrescente(Lista);		// Verifica se a lista est� em ordem crescente. Suponha que a lista n�o contenha duplicatas
bool verificarIgual(Lista ,Lista ); // Verifica se as duas listas cont�m os mesmos elementos, n�o importa a ordem. As listas n�o cont�m duplicatas
bool verificarIgualOrdem ( Lista, Lista ); // Verifica se as duas listas s�o iguais, isto �, se cont�m os mesmos elementos, na mesma ordem.
Lista concatenarListas (Lista*,Lista*); // Constr�i uma nova lista com a concatena��o das listas na ordem dos par�metros
Lista inverterLista (Lista);  // Inverte a ordem dos elementos de uma lista, sem criar novas c�lulas.
void concatenarListasPointer(Lista *,Lista *); // Concatena as duas listas na ordem dos par�metros e devolve a segunda lista vazia
Lista separarLista ( Lista *,  int); // Divide a lista em duas listas, de modo que a segunda lista comece no primeiro elemento 
									 		//ap�s a primeira ocorr�ncia de y na lista original. A lista original deve conter y como �ltimo elemento


int main(){
	Lista L;
	
	printf("\n");
	L = criarLista();  mostrarLista(&L);		
	
	inserir(&L,10);   	mostrarLista(&L);						
	
	inserir(&L,20);   	mostrarLista(&L);						
	
	inserir(&L,25);   	mostrarLista(&L);						

	inserir(&L,30);   	mostrarLista(&L);						

	printf("\n\n FIM ");
	return 0;
}

Lista criarLista(){     
    Lista L;
    L.tamanho=0;
    L.inicio=NULL;
    
    return L;
}

bool verListaVazia(Lista *ap){
    bool vazio = FALSE;
	if(ap->inicio==NULL)
    	vazio=TRUE;
    	
    return vazio;
}

int obterTamanho(Lista *ap){
    return ap->tamanho;
}
     
void inserir(Lista *ap, int y){
    Celula *nova;
	nova = malloc(sizeof(Celula));
    nova->item = y;
    nova->next = ap->inicio;
    ap->inicio = nova;
    ap->tamanho = ap->tamanho + 1;
}

void inserirUltimo(Lista *ap, int y) {
	Celula *p;
	Celula *nova;
	nova = malloc(sizeof(Celula));
	nova->item=y;
	nova->next=NULL;
	
	p = ap->inicio;
	if(p!=NULL) {
		while(p->next!=NULL)
			p = p->next;
		p->next = nova;
	}
	
	else {
		ap->inicio = nova;
	}
	
	ap->tamanho = ap->tamanho + 1;
}

void remover(Lista *ap) {
	Celula *aux;
	aux = ap->inicio;
	if(aux!=NULL) {
		ap->inicio = aux->next;
		ap->tamanho = ap->tamanho - 1;
		free(aux);
	}
}

void removerUltimo(Lista *ap) {
	//Ultimo eh o unico (primeiro) - muda ap-inicio para NULL e limpa a celula do primeiro
	//Lista vazia - nao faz nada
	//Ultimo em lista maior - aponta anterior para NULL e limpa ultimo
	if (ap->inicio != NULL) {
        Celula *atual = ap->inicio;
        Celula *anterior;
        if(atual->next==NULL) {
        	ap->inicio=NULL;
        	free(atual);
		}
		else {
			anterior = atual;
			atual = atual->next;
			while(atual->next!=NULL) {
				anterior = atual;
				atual = atual->next;
			}
			anterior->next = NULL;
			free(atual);
		}
        ap->tamanho = ap->tamanho - 1;
    }
}
       
void mostrarLista(Lista *ap){
    Celula *seg;
    printf("\n");
	seg = ap->inicio;
	if(seg==NULL) 
		printf("Lista Vazia.");
		
	else {
		do {
			printf("%d\t", seg->item);
    		seg = seg->next;
		} while(seg!=NULL);
	}
	
	printf("\n");
}

int obterElemento(Lista *ap, int pos) {
	int el = ghost;
	Celula *p = ap->inicio;
	
	while(p!=NULL && pos>1) {
		p = p->next;
		pos--;
	}
	if(p!=NULL)
		el = p->item;
	
	return el;
}

Celula* buscarElemento(Lista ap, int y) {
	Celula *p = ap.inicio;
	Celula *alvo = NULL;
	while(p!=NULL && p->item!=y) {
		p = p->next;
	}
	if(p!=NULL)
		alvo = p;
		
	return alvo;
}


int localizarElemento(Lista *ap, int y){
	Celula *atual;
	int pos = 0;
	int cont = 1;
	
	atual = ap->inicio;
	while(atual!=NULL && atual->item!=y) {
		atual = atual->next;
		cont++;
	}
	if(atual!=NULL)
		pos = cont;
	
	return pos;
}	

void buscaRemove(Lista *ap, int y) { // Remove a primeira ocorr�ncia da c�lula que cont�m y
	//Lista vazia - nao faz nada
	//Lista unica - Se y existe, ap->inicio vira NULL e limpa primeiro. Se nao, nao faz nada
	//Lista com mais de um elemento - Se y existe, aponta anterior para o y->next e limpa o atual
	//Lista com mais de um elemento - Se y nao existe, nao faz nada
	if(ap->inicio!=NULL) {
		Celula *atual = ap->inicio;
		Celula *anterior;
		if(atual->item==y) {
			ap->inicio=atual->next;
			free(atual);
			ap->tamanho = ap->tamanho - 1;
		}
		else if(atual->next!=NULL) {
			anterior = atual;
			atual = atual->next;
			while(atual->next!=NULL && atual->item!=y) {
				anterior = atual;
				atual = atual->next;
			}
			if(atual->item==y) {
				anterior->next = atual->next;
				free(atual);
				ap->tamanho = ap->tamanho - 1;
			}
		}
	}
}

void buscaInsere(Lista *ap, int y) {
	//Lista vazia = insere no comeco
	//Lista unica = se nao for y, insere
	//Lista com mais de um elemento = se nao houver y, insere
	Celula *p;
	p = ap->inicio;
	
	while(p!=NULL && p->item!=y) //Lista nao for vazia
		p = p->next;

	if(p==NULL) {
		Celula *nova; 
		nova = malloc(sizeof(Celula));
		nova->item = y;
		nova->next = ap->inicio;
		ap->inicio = nova;
		ap->tamanho = ap->tamanho + 1;
	}
}

void trocarCelulas(Lista *ap, Celula *cel1, Celula *cel2) {
	//A lista nao eh vazia e tem pelo menos dois elementos
	if(cel1!=cel2) {
		Celula *p = ap->inicio;	
		Celula *prev1 = NULL;
		Celula *prev2 = NULL;
	
		while(p!=NULL && (prev1==NULL || prev2==NULL)) {
			if(p->next==cel1) prev1 = p;
			else if(p->next==cel2) prev2 = p;
			p = p->next;
		}
	
		if(ap->inicio==cel1) {
			ap->inicio = cel2;
		}
		else if(ap->inicio==cel2) {
			ap->inicio = cel1;
		}
	
		if (prev1 != NULL) {
	        prev1->next = cel2;
	    }
	    if (prev2 != NULL) {
	        prev2->next = cel1;
	    }
    
	    Celula *temp = cel1->next;
	    cel1->next = cel2->next;
	    cel2->next = temp;		
	}

}

bool verificarCrescente(Lista ap) {
	bool crescente = TRUE;
	Celula *prim;
	Celula *seg;
	if(ap.inicio!=NULL) {
		prim = ap.inicio;
		seg = prim->next;
		while(seg!=NULL && seg->item>=prim->item) {
			prim = seg;
			seg = seg->next;	
		}
		if(seg!=NULL)
			crescente = FALSE;
	}
	
	return crescente;
}

bool verificarIgual(Lista A, Lista B)
{
	bool igual;
	Celula *p, *q;
	igual = FALSE;
	if (A.tamanho == B.tamanho)
	{
		if ((A.inicio == NULL) && (B.inicio == NULL))
			igual = TRUE;
		else
		{
			if ((A.inicio == NULL) || (B.inicio == NULL))
				igual = FALSE;
			else
			{
				igual = TRUE;
				p = A.inicio;
				do
				{
					q = B.inicio;
					while ((p->item != q->item) && (q->next != NULL))
						q = q->next;
					if (p->item != q->item)
						igual = FALSE;
					else
						p = p->next;
				} while ((p != NULL) && (igual == TRUE));
				if (igual == TRUE)
				{
					p = B.inicio;
					do
					{
						q = A.inicio;
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
	}
	return igual;
}

Lista concatenarListas(Lista *ap, Lista *bp) {
    //Se a lista A for vazia - Copiar a Lista B
    //Se a lista B for vazia - Copiar a Lista A
    //Se as duas listas forem vazias - retornar lista vazia
    //Se as listas nao forem vazias - Copiar A depois copiar B
	Lista concat;
    Celula *p1;
    Celula *p2;
	Celula *nova;
	
    // Inicializa a lista concatenada
    concat.inicio=NULL;
    concat.tamanho=0;
	
    if(ap->inicio!=NULL) {
    	p1 = ap->inicio;
    	//Define o primeiro elemento
    	nova = malloc(sizeof(Celula));
		nova->next=NULL;
		nova->item=p1->item;
		//Define o inicio da lista nova
    	concat.inicio = nova;
    	concat.tamanho++;
    	
    	p1 = p1->next;
    	
		while(p1!=NULL) {
			nova->next = malloc(sizeof(Celula));
			nova = nova->next;
			nova->item=p1->item;
			nova->next = NULL;
			concat.tamanho++;
			p1 = p1->next;
		}	
	}
	
	if(bp->inicio!=NULL) {
    	p2 = bp->inicio;
		if(concat.inicio==NULL)	{
    		//Define o primeiro elemento
    		nova = malloc(sizeof(Celula));
			nova->item=p2->item;
			nova->next=NULL;
			//Define o inicio da lista nova
    		concat.inicio = nova;
    		concat.tamanho++;
    	
    		p2 = p2->next;
		}	

		while(p2!=NULL) {
			nova->next = malloc(sizeof(Celula));
			nova = nova->next;
			nova->item=p2->item;
			nova->next = NULL;
			concat.tamanho++;
			p2 = p2->next;
		}	
	}		

    return concat;
}

Lista inverterLista(Lista A) {
	Lista invertida;
	invertida.inicio=NULL;
	invertida.tamanho=0;
	
	if(A.inicio!=NULL){
		Celula *prim;
		Celula *seg;
		Celula *pA;

		pA = A.inicio;
		prim = NULL;
		
		while(pA!=NULL) {
			seg = malloc(sizeof(Celula));
			seg->item = pA->item;
			seg->next = prim;
			prim = seg;
			pA = pA->next;
		}
		invertida.tamanho = A.tamanho;
		invertida.inicio = prim;
	}
	
	return invertida;
}

void concatenarListasPointer(Lista *ap,Lista *bp) {
	Celula *p;
	
	if(ap->inicio!=NULL) {
		p = ap->inicio;
		
		while(p->next!=NULL) 
			p = p->next;		
		p->next = bp->inicio;
	}
	
	else {
		ap->inicio = bp->inicio;
	}
		
		ap->tamanho = ap->tamanho + bp->tamanho;
		bp->inicio=NULL;
		bp->tamanho=0;
}

bool verificarIgualOrdem(Lista A, Lista B) {
	bool igual=TRUE;
	Celula *p1;
	Celula *p2;

	if(A.tamanho == B.tamanho) {
		p1 = A.inicio;
		p2 = B.inicio;
	
		while((p1!=NULL && p2!=NULL) && p1->item==p2->item) {
			p1 = p1->next;
			p2 = p2->next;
		}
		if(p1!=NULL && p2!=NULL) {
			igual = FALSE;
		}
	}
	else {
		igual = FALSE;
	}	
		
	return igual; 
}

Lista separarLista(Lista *ap,  int y) {
	Lista sublista;
	sublista.inicio=NULL;
	sublista.tamanho=0;
	int cont = 0;
	if(ap->inicio!=NULL) {
		Celula *p;
		p = ap->inicio;
		cont++;
		while(p->next!=NULL && p->item!=y) {
			p = p->next;
			cont++;
		}		
		if(p->item==y) {
			sublista.inicio = p->next;
			p->next = NULL;
		}
		sublista.tamanho = ap->tamanho - cont;
		ap->tamanho = cont;
	}
	
	return sublista;
}

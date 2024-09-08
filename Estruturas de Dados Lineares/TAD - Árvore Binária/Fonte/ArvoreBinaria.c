/*
Autor: Luís Augusto Coelho de Souza
Versão/Data: 07/09/2024
TAD - Árvore Binária
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FilaLigada.h"
#include "PilhaLigada.h"

typedef struct No{
    int elemento;
    struct No *esq;
    struct No *dir;
} No;

typedef No *Arvore;

Arvore criarArvoreVazia(); 
Arvore construirArvore(int, Arvore, Arvore); 
void mostrarArvore_Red(Arvore); 
void mostrarArvore_edR(Arvore); 
void mostrarArvore_eRd(Arvore); 
void mostrarArvore_BFS(Arvore); 
void mostrarPorNivel(Arvore);
Arvore construirArvoreRam(int); 
No* buscar(Arvore, int); 
int obterAlturaRec(Arvore); 
int contarNosRec(Arvore); 
int contarFolhasRec(Arvore); 
//Sem recursao 
void mostrarArvore_Red_Nrec(Arvore); 
void mostrarArvore_edR_Nrec(Arvore); 
void mostrarArvore_eRd_Nrec(Arvore); 
int obterAltura(Arvore); 
int contarNos(Arvore); 
int contarFolhas(Arvore);  
int contarNoIN(Arvore); 
//Rotacoes Arvore Binaria
No *rodar_Esquerda(No*);
No *rodar_Direita(No*);
No *rodar_EsqDir(No*);
No *rodar_DirEsq(No*);
//Exercicios extras:
//--------------eRd--------------
void mostrarPrimeiro_eRd(Arvore); 
void mostrarUltimo_eRd(Arvore); 
No* obterAnterior_eRd(Arvore, int); 
No* obterSeguinte_eRd(Arvore, int); 
//--------------Red--------------
void mostrarPrimeiro_Red(Arvore); 
void mostrarUltimo_Red(Arvore); 
No* obterAnterior_Red(Arvore, int); 
No* obterSeguinte_Red(Arvore, int); 
//--------------edR--------------
void mostrarPrimeiro_edR(Arvore); 
void mostrarUltimo_edR(Arvore); 
No* obterAnterior_edR(Arvore, int); 
No* obterSeguinte_edR(Arvore, int); 
//-------------------------------

int main() {
    srand(time(NULL));
    Arvore subArvoreDireita = criarArvoreVazia();
    subArvoreDireita = construirArvore(11, criarArvoreVazia(), criarArvoreVazia()); // Nó 11
    subArvoreDireita = construirArvore(12, subArvoreDireita, criarArvoreVazia());   // Nó 12 com filho esquerdo 11
    subArvoreDireita = construirArvore(15, subArvoreDireita, criarArvoreVazia());   // Nó 15 com filho esquerdo 12

    Arvore subArvoreEsquerda = criarArvoreVazia();
    subArvoreEsquerda = construirArvore(5, criarArvoreVazia(), criarArvoreVazia()); // Nó 5
    subArvoreEsquerda = construirArvore(7, subArvoreEsquerda, criarArvoreVazia());  // Nó 7 com filho esquerdo 5

    Arvore arvoreMista = construirArvore(10, subArvoreEsquerda, subArvoreDireita);
    mostrarPorNivel(arvoreMista);
    return 0;
}

Arvore criarArvoreVazia() {
    Arvore ap;
    ap=NULL;
    return ap;
}

Arvore construirArvore(int elemento, Arvore ap, Arvore bp) {
    Arvore novaArvore;
    novaArvore = malloc(sizeof(No));
    novaArvore->elemento=elemento;
    novaArvore->esq=ap;
    novaArvore->dir=bp;

    return novaArvore;
}

void mostrarArvore_Red(Arvore ap) {
    if(ap!=NULL) {
        printf("%d\t", ap->elemento);
        mostrarArvore_Red(ap->esq);
        mostrarArvore_Red(ap->dir);
    }
}

void mostrarArvore_edR(Arvore ap) {
    if(ap!=NULL) {
        mostrarArvore_edR(ap->esq);
        mostrarArvore_edR(ap->dir);
        printf("%d\t", ap->elemento);
    }
}

void mostrarArvore_eRd(Arvore ap) {
    if(ap!=NULL) {
        mostrarArvore_eRd(ap->esq);
        printf("%d\t", ap->elemento);
        mostrarArvore_eRd(ap->dir);
    }
}

void mostrarArvore_BFS(Arvore ap) { //Fila
    No *p; Fila f;
    if(ap==NULL) {
        printf("\n arvore vazia \n");
    }
    else {
        f = criarFila(); p = ap; pushFila(&f, p);
        do {
            p = acessarFila(&f);
            printf("%d\t", p->elemento);
            popFila(&f);
            if(p->esq!=NULL)    pushFila(&f, p->esq);
            if(p->dir!=NULL)    pushFila(&f, p->dir);
        } while(verFilaVazia(&f) == FALSE);
    }
}

void mostrarPorNivel(Arvore ap) { //Usando o caminhamento BFS
    int numNosNivel;
    No *p; Fila f;
    if(ap!=NULL) {
        f = criarFila(); p = ap; pushFila(&f, p);
        
        do {
            numNosNivel = obterTamanho(&f);
            while(numNosNivel--) {
                p = acessarFila(&f);
                printf("%d\t", p->elemento);
                if(p->esq!=NULL) {
                    pushFila(&f, p->esq);
                }
                if(p->dir!=NULL) {    
                    pushFila(&f, p->dir);
                }
                popFila(&f);
            }
            printf("\n");
        } while(verFilaVazia(&f) == FALSE);
    }
    
}

int obterAlturaRec(Arvore ap) {
    No *p = ap;
    int altura = 0;
    if(p==NULL) {
        altura = -1;
    }
    else {
        int alturaEsq = obterAlturaRec(p->esq);
        int alturaDir = obterAlturaRec(p->dir);
        if(alturaEsq > alturaDir)
            altura = alturaEsq + 1;
        else
            altura = alturaDir + 1;
    }

    return altura;
}

int contarNosRec(Arvore ap) {
    No *p = ap;
    int numNos;
    if(p==NULL) {
        numNos = 0;
    }
    else {
        numNos = contarNosRec(p->esq) + contarNosRec(p->dir) + 1;
    }
    return numNos;
}

int contarFolhasRec(Arvore ap) {
    No *p = ap;
    int numFolhas;
    if(p==NULL) {
        numFolhas = 0;
    }
    else if(p->dir==NULL && p->esq==NULL) {
        numFolhas = 1;
    }
    else {
        numFolhas = contarFolhasRec(p->esq) + contarFolhasRec(p->dir);
    }

    return numFolhas;
}

Arvore construirArvoreRam(int n) {
    Arvore ram;
    int n1, n2; 
    if(n==0) { //Arvore vazia
        ram=NULL;
    }
    else if(n==1) { //Arvore de 1 no (folha)
        ram = malloc(sizeof(No));
        ram->elemento = rand()%50;
        ram->esq = NULL;
        ram->dir = NULL;
    }
    else { //Arvore de n nos
        n1 = (n - 1)/2;  
        n2 = (n - 1) - n1;
        ram = malloc(sizeof(No));
        ram->elemento = rand()%50;
        ram->esq = construirArvoreRam(n1);
        ram->dir = construirArvoreRam(n2);
    }
    
    return ram;
}

No* buscar(Arvore ap, int y) {
    No *p; Fila f; No *elemento = NULL;
    if(ap!=NULL) {
        f = criarFila(); p = ap; pushFila(&f, p);
        do {
            p = acessarFila(&f);
            popFila(&f);
            if(p->esq!=NULL)    pushFila(&f, p->esq);
            if(p->dir!=NULL)    pushFila(&f, p->dir);
        } while(!verFilaVazia(&f) && (p->elemento != y));
        if(p->elemento==y) {
            elemento = p;
        }
    }
    return elemento;
}

//Sem recursao ------------------------------------------------

void mostrarArvore_Red_Nrec(Arvore ap) {
    Pilha s; No *p; p = ap;
    if (p == NULL) {
        printf("\n arvore vazia \n");
    }
    else {
        s = criarPilhaVazia();

        push(&s, p);

        do {
            p = peek(s); 
            printf("%d\t", p->elemento);
            pop(&s);

            // Adiciona os filhos à Pilha
            if (p->dir != NULL) {
                push(&s, p->dir);
            }
            if (p->esq != NULL) {
                push(&s, p->esq);
            }

        } while(verPilhaVazia(s) == FALSE);
    }
}

void mostrarArvore_edR_Nrec(Arvore ap) {
    if (ap == NULL) {
        printf("\n arvore vazia \n");
    }

    Pilha s1 = criarPilhaVazia();
    Pilha s2 = criarPilhaVazia();

    // Adiciona a raiz na primeira pilha
    push(&s1, ap);

    // Processa todos os nós na primeira pilha
    while (!verPilhaVazia(s1)) {
        // Remove o nó da pilha1 e coloca na pilha2
        No* p = peek(s1);
        pop(&s1);

        push(&s2, p);

        // Adiciona o filho esquerdo
        if (p->esq != NULL) {
            push(&s1, p->esq);
        }

        // Adiciona o filho direito
        if (p->dir != NULL) {
            push(&s1, p->dir);
        }
    }

    // A pilha2 agora contém os nós em pós-ordem
    while (!verPilhaVazia(s2)) {
        No* p = peek(s2);
        pop(&s2);
        printf("%d\n", p->elemento);
    }
}

void mostrarArvore_eRd_Nrec(Arvore ap) {
    Pilha s; No *p; bool fim;
    if(ap!=NULL) {
        s = criarPilhaVazia(); fim = FALSE; p = ap;
        do {
            while(p!=NULL) {
                push(&s, p); p = p->esq;
            }
            if(verPilhaVazia(s) == FALSE) {
                p = peek(s);
                printf("%d\t", p->elemento);
                pop(&s);
                p = p->dir;
            }
            else {
                fim = TRUE;
            }
        }while(fim == FALSE);
    }
    else {
        printf("\n Arvore Vazia \n");
    }
}

int obterAltura(Arvore ap) { //Usando o caminhamento BFS
    int nivel = 0; int altura; int numNosNivel;
    No *p; Fila f;
    if(ap!=NULL) {
        f = criarFila(); p = ap; pushFila(&f, p);
        
        do {
            nivel = nivel + 1;
            numNosNivel = obterTamanho(&f);
            while(numNosNivel--) {
                p = acessarFila(&f);
                if(p->esq!=NULL) {
                    pushFila(&f, p->esq);
                }
                if(p->dir!=NULL) {    
                    pushFila(&f, p->dir);
                }
                popFila(&f);
            }
        } while(verFilaVazia(&f) == FALSE);
    }
    
    altura = nivel - 1; 
    
    return altura;
}

int contarNos(Arvore ap) { //Usando o caminhamento BFS
    Fila q; No *p; int numNos = 0;
    if(ap!=NULL) {
        q = criarFila(); p = ap; pushFila(&q, p);
        do {
            p = acessarFila(&q);
            numNos++;
            popFila(&q);

            if(p->esq!=NULL) pushFila(&q, p->esq);
            if(p->dir!=NULL) pushFila(&q, p->dir);
        }while(verFilaVazia(&q) == FALSE);
    }
    
    return numNos;
}

int contarFolhas(Arvore ap) { 
    Fila q; No *p; int numFolhas = 0;
    if(ap!=NULL) {
        q = criarFila(); p = ap; pushFila(&q, p);
        do {
            p = acessarFila(&q);
            popFila(&q);

            if(p->esq!=NULL) pushFila(&q, p->esq);
            if(p->dir!=NULL) pushFila(&q, p->dir);
            if(p->esq==NULL && p->dir==NULL) numFolhas++;
        }while(verFilaVazia(&q) == FALSE);
    }

    return numFolhas;
}

int contarNoIN(Arvore ap) { //BFS
    Fila q; No *p; int numNoInterno = 0;
    if(ap!=NULL) {
        q = criarFila(); p = ap; pushFila(&q, p);
        do {
            p = acessarFila(&q);
            popFila(&q);

            if(p->esq!=NULL) pushFila(&q, p->esq);
            if(p->dir!=NULL) pushFila(&q, p->dir);
            if(p->esq!=NULL || p->dir!=NULL) numNoInterno++;
        }while(verFilaVazia(&q) == FALSE);
    }

    return numNoInterno;
}

//--------------------------------------------------Rotacoes em Arvores Binarias-------------------------------------------------------
No *rodar_Esquerda(No* p) {
    No *esqY; No* Y;
    if(p!=NULL) {
        Y = p->dir;
        if(Y!=NULL) {
            esqY = Y->esq;
            p->dir = esqY;
            Y->esq = p;
        }
    }

    return Y;
}

No *rodar_Direita(No* p) {
    No *dirY; No* Y;
    if(p!=NULL) {
        Y = p->esq;
        if(Y!=NULL) {
            dirY = Y->dir;
            p->esq = dirY;
            Y->dir = p;
        }
    }

    return Y;
}

No *rodar_EsqDir(No* X) { 
    No *Y; No *Z; No *novaRaiz; novaRaiz = NULL;
    if(X!=NULL) {
        Y = X->esq;
        if(Y!=NULL) {
            Z = Y->dir;
            if(Z!=NULL) {
                Y->dir = Z->esq;
                X->esq = Z->dir;
                Z->esq = Y;
                Z->dir = X;
                novaRaiz = Z;
            }
            else {
                X->esq = Y->dir;
                Y->dir = X;
                novaRaiz = Y;
            }
        }
    }

    return novaRaiz;
}

No *rodar_DirEsq(No *A) {
    No *B; No *C; No *novaRaiz; novaRaiz = NULL;
    if(A!=NULL) {
        B = A->dir;
        if(B!=NULL) {
            C = B->esq;
            if(C!=NULL) {
                B->esq = C->dir;
                A->dir = C->esq;
                C->esq = A;
                C->dir = B;
                novaRaiz = C;
            }
            else {
                A->dir = B->esq;
                B->esq = A;
                novaRaiz = B;
            }
        }
    }

    return novaRaiz;
}

//-----------------eRd-----------------------------------------------------------------------------------------------------------------

void mostrarPrimeiro_eRd(Arvore ap) {
    No *p; 
    if (ap==NULL)
    {
        printf("\n Arvore vazia \n");
    }
    else {
        p = ap;
        while(p->esq!=NULL) {
            p = p->esq;
        }
        printf("\n %d \n", p->elemento);
    }
}

void mostrarUltimo_eRd(Arvore ap) {
    No *p; 
    if (ap==NULL)
    {
        printf("\n Arvore vazia \n");
    }
    else {
        p = ap;
        while(p->dir!=NULL) {
            p = p->dir;
        }
        printf("\n %d \n", p->elemento);
    }
}

No *obterAnterior_eRd(Arvore ap, int y)
{
    No *p; p = ap; 
    No *aux;    aux = NULL;
    No *anterior; anterior = NULL;
    Pilha s = criarPilhaVazia();
    bool fim = FALSE;
    if (p != NULL)
    {
        do {
            while (p != NULL) { 
                push(&s, p); p = p->esq;
            }
            if (verPilhaVazia(s) == FALSE) 
            {
                p = peek(s);
                if(p->elemento==y) { 
                    anterior = aux;
                    fim = TRUE;
                }
                aux = p;
                pop(&s);
                
                p = p->dir;
            }
            else
            {
                fim = TRUE;
            }
        }while (fim == FALSE);
    }
    
    return anterior;
}

No* obterSeguinte_eRd(Arvore ap, int y) {
    No *p; p = ap; 
    No *proximo; proximo = NULL;
    No *aux; aux = NULL;
    Pilha s = criarPilhaVazia();
    bool fim = FALSE;
    if (p != NULL)
    {
        do {
            while (p != NULL) { 
                push(&s, p); p = p->esq;
            }
            if(aux!=NULL) {
                proximo = peek(s);
                fim = TRUE;
            }
            if (verPilhaVazia(s) == FALSE && fim == FALSE) 
            {
                p = peek(s);
                if(p->elemento==y) {
                    aux = p;
                }
                pop(&s);

                p = p->dir;
            }
            else 
            {
                fim = TRUE;
            }
        } while (fim == FALSE);
        esvaziaPilha(&s);
    }
    
    return proximo;
}

//-----------------Red-----------------------------------------------------------------------------------------------------------------
void mostrarPrimeiro_Red(Arvore ap) {
    if(ap!=NULL) {
        printf("\n %d \n", ap->elemento);
    }
    else
        printf("\n Arvore Vazia \n");
}

void mostrarUltimo_Red(Arvore ap) {
    No *p; 
    if (ap==NULL)
    {
        printf("\n Arvore vazia \n");
    }
    else {
        p = ap;
        while(p->dir!=NULL) {
            p = p->dir;
        }
        printf("\n %d \n", p->elemento);
    }
}

No* obterAnterior_Red(Arvore ap, int y) {
    No *p; p = ap;
    No *aux; aux = NULL;
    No *anterior; anterior = NULL;
    Pilha s = criarPilhaVazia(); 
    bool fim = FALSE;
    if(p!=NULL) {
            aux = peek(s);
            push(&s, p);

        do {
            p = peek(s);
            if(p->elemento==y) {
                anterior = aux;
                fim = TRUE;
            }
            aux = p;
            pop(&s);

            if(p->dir != NULL)   push(&s, p->dir);
            if(p->esq != NULL)   push(&s, p->esq);

        }while(verPilhaVazia(s)==FALSE && fim==FALSE);   

        esvaziaPilha(&s);
    }

    return anterior;
}

No* obterSeguinte_Red(Arvore ap, int y) {
    No *p; p = ap;
    Pilha s = criarPilhaVazia();
    No *proximo; proximo = NULL;
    No *aux; 
    bool fim = FALSE;
    if(ap!=NULL) {
        push(&s, p);
        do {
            p = peek(s);
            pop(&s);
            aux = p;
        
            if(p->dir!=NULL) push(&s, p->dir);
            if(p->esq!=NULL) push(&s, p->esq);
            
            if(aux->elemento == y) {
                proximo = peek(s);
                fim = TRUE;
            }
            
        }while(verPilhaVazia(s)==FALSE && fim==FALSE);

        esvaziaPilha(&s);
    }

    return proximo;
}

//-----------------edR-----------------------------------------------------------------------------------------------------------------

void mostrarPrimeiro_edR(Arvore ap) {
    if(ap==NULL) {
        printf("\n Arvore Vazia \n");
    }
    else {
        No *p = ap; bool fim = FALSE;
        do {
            while(p->esq != NULL) { //Move para esquerda ate onde for possivel
                p = p->esq;
            }
            if(p->dir!=NULL) { //tenta mover para direita
                p = p->dir;
            }
            
            else { //Se nao for possivel, a p esta no primeiro elemento
                fim = TRUE;
            }

        } while(fim==FALSE);
        
        printf("\n %d \n", p->elemento);
    }
}

void mostrarUltimo_edR(Arvore ap) {
    if(ap==NULL) {
        printf("\n Arvore Vazia \n");
    }
    else { //Se a arvore nao for vazia, o ultimo elemento eh a raiz
        printf("\n %d \n", ap->elemento);
    }
}

No* obterAnterior_edR(Arvore ap, int y) {
    No *ant; ant = NULL;
    if(ap!=NULL) {
        No *p; No *aux; Pilha s1 = criarPilhaVazia(); Pilha s2 = criarPilhaVazia(); bool fim = FALSE;
        p = ap; push(&s1, p);
        
        do {
            p = peek(s1);
            pop(&s1);

            push(&s2, p);

            if(p->esq!=NULL) push(&s1, p->esq);
            if(p->dir!=NULL) push(&s1, p->dir);
            
            aux = peek(s2);
            if(aux->elemento==y) {
                ant = peek(s1);
                fim = TRUE;
                esvaziaPilha(&s1);
            }
        } while(verPilhaVazia(s1)==FALSE && fim==FALSE);
        
        esvaziaPilha(&s2);
    }

    return ant;
}

No* obterSeguinte_edR(Arvore ap, int y) {
    No *seg; seg = NULL;
    if(ap!=NULL) {
        No *p; Pilha s1 = criarPilhaVazia(); Pilha s2 = criarPilhaVazia(); bool fim = FALSE;
        p = ap; push(&s1, p);
        
        do {
            p = peek(s1);
            pop(&s1);
            if(p->elemento==y) {
                seg = peek(s2);
                fim = TRUE;
            }

            push(&s2, p);

            if(p->esq!=NULL) push(&s1, p->esq);
            if(p->dir!=NULL) push(&s1, p->dir);
    
        } while(verPilhaVazia(s1)==FALSE && fim==FALSE);
        
        esvaziaPilha(&s1);
        esvaziaPilha(&s2);
    }

    return seg;
}

//-------------------------------------------------------------------------------------------------------------------------------------


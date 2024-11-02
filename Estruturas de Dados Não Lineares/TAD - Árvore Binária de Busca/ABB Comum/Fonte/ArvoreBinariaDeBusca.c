#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FilaLigada.h"
#include "PilhaLigada.h"

typedef struct No
{
    int chave;
    struct No *esq;
    struct No *dir;
} No;
typedef No *ArvoreBB;

ArvoreBB criarABB();
ArvoreBB destruirArvore(ArvoreBB);
ArvoreBB inserirNo(ArvoreBB, int); //Insere um no na ABB 
ArvoreBB removerNo(ArvoreBB, int); //Remove um no na ABB
void mostrarArvore(ArvoreBB); //Mostra a ABB pelo caminhamento eRd (em ordem)
void mostrarArvoreBFS(ArvoreBB);
void mostrarArvore_edR(ArvoreBB);
void mostrarArvore_Red(ArvoreBB);
void mostrarArvoreRED(ArvoreBB);
void mostrarArvoreEDR(ArvoreBB);
No* obterAncestralIT(ArvoreBB, No*, No*); //Obtem um ancestral comum entre dois nos
No* obterAncestral(ArvoreBB, No*, No*);  //Obtem um ancestral comum entre dois nos por recursao
No* obterPai(ArvoreBB, No*);
ArvoreBB removerRaiz(ArvoreBB); //Remove a raiz de uma ABB
No * buscarABBIT(ArvoreBB, int); //Busca uma chave na ABB iterativamente
No * buscarABB(ArvoreBB, int); //Busca uma chave na ABB
ArvoreBB inserirR(ArvoreBB, int); //Insere um no na ABB por recursao
int obterAltura(ArvoreBB); //Obtem a altura de uma ABB recursivamente 
void mostrarPrimeiro(ArvoreBB); //Mostra o primeiro No no caminhamento eRd
void mostrarUltimo(ArvoreBB); //Mostra o ultimo No no caminhamento eRd
No * obterPrimeiro(ArvoreBB); //Recolhe o primeiro No no caminhamento eRd
No * obterSucessor(ArvoreBB, int); //Recolhe o Sucessor de um No no caminhamento eRd
No * obterAnterior(ArvoreBB, int); //Recolhe o Antecessor de um No no caminhamento eRd
ArvoreBB buscaInsere(ArvoreBB, int); //Insere um elemento na ABB se ele ja nao existir nela.
No * select(ArvoreBB, int); //Devolve o No com elemento da ordem k na ordem crescente
int rank(ArvoreBB, int); //Devolve a posicao na ordem crescente em que se encontra um elemento

int main() {
    ArvoreBB A = criarABB();
    A = inserirNo(A, 30);   A = inserirNo(A, 7);    A = inserirNo(A, 40);    A = inserirNo(A, 4);    A = inserirNo(A, 20);    A = inserirNo(A, 35);    A = inserirNo(A, 50);    A = inserirNo(A, 2);    A = inserirNo(A, 5);    A = inserirNo(A, 10);
    A = inserirNo(A, 22);    A = inserirNo(A, 32);    A = inserirNo(A, 38);    A = inserirNo(A, 45);    A = inserirNo(A, 60);    A = inserirNo(A, 1); A = inserirNo(A, 3);    A = inserirNo(A, 8);    A = inserirNo(A, 12);    A = inserirNo(A, 21);
    A = inserirNo(A, 25);    A = inserirNo(A, 36);    A = inserirNo(A, 42);    A = inserirNo(A, 80);    A = inserirNo(A, 11);    A = inserirNo(A, 24);
    mostrarArvore(A);/*
    printf("\n");
    int w = 24, j = 22;
    printf("O menor ancestral entre %d e %d eh o no : %d", buscarABB(A, w)->chave, buscarABB(A, j)->chave, obterAncestralIT(A, buscarABB(A, w), buscarABB(A, j))->chave);
    printf("\n");
    int t = 1;
    printf("O elemento na posicao %d eh %d", t, select(A, t)->chave);
    printf("\n");
    int k = 200;
    printf("O elemento %d eh rankeado %d", k, rank(A, k));
    printf("\n");
    int n = 20;
    printf("O elemento %d eh sucedido por %d", n, obterSucessor(A, n)->chave);
    printf("\n");
    int m = 80;
    printf("O elemento %d eh antecedido por %d", m, obterAnterior(A, m)->chave);
    printf("\n");
    int p = 12;
    printf("O pai de %d eh a chave %d", p, obterPai(A, buscarABBIT(A, p))->chave);
    A = destruirArvore(A);
    mostrarArvore(A);*/
    printf("\n");
    A = removerNo(A, 10);
    mostrarArvore(A);

    return 0;
}

ArvoreBB criarABB() {
    ArvoreBB novaArvore;
    novaArvore = NULL;
    
    return novaArvore;
}

ArvoreBB destruirArvore(ArvoreBB abb) { //Caminha no caminhamento edR e destroi todos os nos da arvore;
    Pilha s1 = criarPilhaVazia(); Pilha s2 = criarPilhaVazia();
    No* p; p = abb;
    if(p!=NULL) {
        push(&s1, p);

        do {
            p = peek(s1);
            pop (&s1);

            push(&s2, p);

            if(p->esq!=NULL) push(&s1, p->esq);
            if(p->dir!=NULL) push(&s1, p->dir);
        }while(verPilhaVazia(s1)==FALSE);

        while(verPilhaVazia(s2)==FALSE) {
            p = peek(s2);
            pop(&s2);
            free(p);
        }
    }

    return NULL;
}

ArvoreBB inserirNo(ArvoreBB abb, int chave) { //Insere um no na ABB
    No *novo, *p, *ant;
    novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    if (abb == NULL)
        abb = novo;
    else
    {
        p = abb;
        while (p != NULL)
        {
            ant = p;
            if (novo->chave < p->chave)
                p = p->esq;
            else
                p = p->dir;
        }
        if (novo->chave < ant->chave)
            ant->esq = novo;
        else
            ant->dir = novo;
    }
    return abb;
}

ArvoreBB removerNo(ArvoreBB abb, int chave) { //Remove um no na ABB
    No *p, *fa, *m, *ba, *filho, *fm;
    int nf;
    if (abb != NULL) //Arvore nao eh vazia
    {
        p = abb;
        nf = 0; // não tem 2 filhos: ou tem 1 ou não tem filhos
        while ((p != NULL) && (p->chave != chave)) //Busca a chave
        {
            fa = p; //Armazena o pai da chave alvo
            if (chave < p->chave) 
                p = p->esq;
            else
                p = p->dir;
        }
        if (p != NULL) //Se encontrar a chave alvo
        {
            if (p->esq == NULL) //Se nao houver filho esquerdo guarda o direito
                filho = p->dir;
            else if (p->dir == NULL) //Se nao houver filho direito guarda o esquerdo
                filho = p->esq;
            else //Se houver filho esq e dir nf = 2
                nf = 2;
            if ((fa == NULL) && (nf == 0)) // raiz : o pai da chave alvo eh null e nao ha dois filhos
            {
                abb = filho; //a nova raiz eh o unico filho da arvore
                free(p);
            } 
            else if ((fa != NULL) && (nf == 0)) // folha ou um único filho
            { 
                if (p == fa->esq) //Se p for o filho esquerdo de seu pai, o pai recebe o unico filho de p pela esquerda
                    fa->esq = filho;
                else //Se p for o filho direito de seu pai, o pai recebe o unico filho de p pela direita
                    fa->dir = filho;
                free(p);
            }
            else
            {               // 2 filhos
                m = p->esq; //m procura o maior filho da subarvore esquerda
                ba = p; //ba sera o pai de m
                while (m->dir != NULL)
                {
                    ba = m; //ba guarda o pai do maior filho da subarvore esquerda
                    m = m->dir;
                }
                fm = m->esq; //fm recebe o filho esquerdo do no da subarvore esquerda
                if (ba != p) //Se o pai nao for a chave alvo
                    ba->dir = fm; //o pai da maior chave da subarvore esquerda recebe o filho esquerdo de m (a unica possivel subarvore ligada a m) pela direita
                    //Isso resulta na desconexao de m do pai ba, pois ba recebera a subarvore de elementos menores que m (mas maiores que ba pois estavam a sua direita)
                else 
                    ba->esq = fm; //o pai da maior chave da subarvore esquerda recebe o filho esquerdo de m (a unica possivel subarvore ligada a m) pela esquerda
                    //Isso resulta na desconexao de m da chave alvo, pois p recebera a subarvore de elementos menores que m e p (pois m eh a maior chave da esquerda de p)
                p->chave = m->chave; //o no p recebe a chave de m, assim a chave a ser liberada se torna m que esta desconexa da continuidade da arvore
                free(m);
            }
        }
    }
    return abb;
}

void mostrarArvore(ArvoreBB abb) { //Mostra a ABB pelo caminhamento eRd (em ordem)
    Pilha s = criarPilhaVazia();
    No *p; p = abb;
    bool fim = FALSE;
    if(p!=NULL) {
        do {
            while(p!=NULL) {
                push(&s, p); p = p->esq;
            }
            if(verPilhaVazia(s)==FALSE) {
                p = peek(s);
                pop(&s);
                printf("%d\t", p->chave);
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

void mostrarArvoreBFS(ArvoreBB ab) {
    Fila q = criarFila(); No *p; p = ab;
    if(p!=NULL) {
        pushFila(&q, p);

        do {
            p = acessarFila(&q);
            popFila(&q);
            printf("%d\t", p->chave);
            
            if(p->esq!=NULL)    pushFila(&q, p->esq);
            if(p->dir!=NULL)    pushFila(&q, p->dir);
        
        }while(verFilaVazia(&q)==FALSE);
    }
    else {
        printf("Arvore vazia.\n");
    }
}

void mostrarArvoreRED(ArvoreBB abb) {
    Pilha s1 = criarPilhaVazia();
    No* p = abb;

    if(p!=NULL) {
        
        push(&s1, p);

        do {
            p = peek(s1);
            pop(&s1);
            printf("%d ", p->chave);

            if(p->dir!=NULL) push(&s1, p->dir);
            if(p->esq!=NULL) push(&s1, p->esq);

        }while(verPilhaVazia(s1)==FALSE);

        printf("\n");
    }
    else {
        printf("Arvore vazia.\n");
    }
}

void mostrarArvoreEDR(ArvoreBB abb) {
    Pilha s1 = criarPilhaVazia(); 
    Pilha s2 = criarPilhaVazia();
    No* p = abb; 

    if(p!=NULL) {
        
        push(&s1, p);

        do {
            p = peek(s1);
            pop(&s1);
            push(&s2, p);

            if(p->esq!=NULL) push(&s1, p->esq);
            if(p->dir!=NULL) push(&s1, p->dir);

        }while(verPilhaVazia(s1)==FALSE);

        while(verPilhaVazia(s2)==FALSE) {
            p = peek(s2);
            pop(&s2);
            printf("%d ", p->chave);
        }
        printf("\n");
    }
    else {
        printf("Arvore vazia.\n");
    }
}

void mostrarArvore_edR(ArvoreBB ab) {
    if(ab!=NULL) {
        mostrarArvore_edR(ab->esq);
        mostrarArvore_edR(ab->dir);
        printf("%d\t", ab->chave);
    }
}

void mostrarArvore_Red(ArvoreBB ab) {
    if(ab!=NULL) {
        printf("%d\t", ab->chave);
        mostrarArvore_Red(ab->esq);
        mostrarArvore_Red(ab->dir);
    }
}

No *obterAncestralIT(ArvoreBB abb, No *n1, No *n2)
{ // Obtem um ancestral comum entre dois nos
    No *ancestral = NULL;
    bool fim = FALSE;

    if (abb != NULL)
    {
        ancestral = abb;
        do
        {

            if (ancestral == n1 || ancestral == n2)
                fim = TRUE;

            else
            {
                // Ambos os nós estão à direita do nó atual
                if (n1->chave > ancestral->chave && n2->chave > ancestral->chave)
                    ancestral = ancestral->dir;

                // Ambos os nós estão à esquerda do nó atual
                else if (n1->chave < ancestral->chave && n2->chave < ancestral->chave)
                    ancestral = ancestral->esq;

                // Os nós estão em lados opostos, então `ancestral` é o LCA
                else
                    fim = TRUE;
            }

        } while (fim == FALSE);
    }

    return ancestral;
}

No *obterAncestral(ArvoreBB abb, No *n1, No *n2) // Obtem um ancestral comum entre dois nos por recursao
{ 

    if (abb != NULL)
    {
        if (n1->chave > abb->chave && n2->chave > abb->chave)
            abb = obterAncestral(abb->dir, n1, n2);

        else if (n1->chave < abb->chave && n2->chave < abb->chave)
            abb = obterAncestral(abb->esq, n1, n2);
    }

    return abb;
}

No* obterPai(ArvoreBB abb, No* filho) {
    No* pai = NULL;
    No* p = abb;
    bool fim = FALSE;
    if(abb!=NULL && filho!=NULL) {
        do
        {
            if (filho->chave == p->chave)
            {
                fim = TRUE;
            }
            else {
                // Atualiza o pai antes de mudar o nó atual
                pai = p;

                if (filho->chave < p->chave) p = p->esq; // Move para a subárvore esquerda
                else p = p->dir; // Move para a subárvore direita
            }

        }while((fim == FALSE) && (p!=NULL));
        if(p==NULL) pai = NULL;
    }

    return pai; // Retorna NULL se o nó não for encontra
}

ArvoreBB removerRaiz(ArvoreBB abb) { //Remove a raiz de uma ABB
    if(abb!=NULL) {
        No *p;
        int nf = 0;
        if(abb->esq == NULL) p = abb->dir; //Se nao houver filho esquerdo guarda o direito
        else if(abb->dir == NULL) p = abb->esq; //Se nao houver filho direito mas houver esquerdo guarda o esquerdo
        else nf = 2; //Se houver dois filhos

        if(nf == 0) { //Raiz com um ou nenhum filho
            free(abb);
            abb = p;
        }
        else {
            p = abb->esq;
            No* fa = abb;
            while(p->dir!=NULL) {
                fa = p;
                p = p->dir;
            }
            No* fp = p->esq;
            
            if(fa->esq != p) fa->dir = fp; //O pai de p nao eh a raiz
            else fa->esq = fp;

            abb->chave = p->chave;
            free(p);
        }
    }

    return abb;
}

No *buscarABB(ArvoreBB ap, int y)
{
    if (ap != NULL)
    {
        if (y < ap->chave)
            ap = buscarABB(ap->esq, y);
        else if (y > ap->chave)
            ap = buscarABB(ap->dir, y);
    }
    return ap;
}

No *buscarABBIT(ArvoreBB ap, int y)
{
    No *p;
    p = ap;
    while ((p != NULL) && (p->chave != y))
    {
        if (y < p->chave)
            p = p->esq;
        else
            p = p->dir;
    }
    return p;
}

ArvoreBB inserirR(ArvoreBB abb, int chave) { //Insere um no na ABB por recursao
    No* novoNo;
        if(abb == NULL) {
            novoNo = (No*) malloc(sizeof(No));
            novoNo->chave = chave;
            novoNo->esq = NULL;
            novoNo->dir = NULL;
            abb = novoNo;
        }
        if(chave < abb->chave) {
            abb->esq = inserirR(abb->esq, chave);
        }
        else if(chave > abb->chave){
            abb->dir = inserirR(abb->dir, chave);
        }

    return abb;
}

int obterAltura(ArvoreBB abb) { //Obtem a altura de uma ABB recursivamente 
    int altura;
    if(abb==NULL) {
        altura = -1;
    }
    else {
        int alturaEsq = obterAltura(abb->esq);
        int alturaDir = obterAltura(abb->dir);
        if(alturaEsq > alturaDir)
            altura = alturaEsq + 1;
        else
            altura = alturaDir + 1;
    }
    
    return altura;
}

void mostrarPrimeiro(ArvoreBB abb) { //Mostra o primeiro No no caminhamento eRd
    No *p; p = abb;
    if(p!=NULL) {
        do {
            p = p->esq;
        }while(p->esq!=NULL);
        printf("\n%d\n", p->chave);
    }
}

void mostrarUltimo(ArvoreBB abb) { //Mostra o ultimo No no caminhamento eRd
    No *p; p = abb;
    if(p!=NULL) {
        do {
            p = p->dir;
        }while(p->dir!=NULL);
        printf("\n%d\n", p->chave);
    }
}

No* obterPrimeiro(ArvoreBB abb) { //Recolhe o primeiro No no caminhamento eRd
    No *p; p = abb;
    No *prim; prim = NULL;
    if(p!=NULL) {
        do {
            p = p->esq;
        }while(p->esq!=NULL);
        prim = p;
    }

    return prim;
}

No* obterSucessor(ArvoreBB abb, int chave) { //Recolhe o Sucessor de um No no caminhamento eRd
    Pilha s = criarPilhaVazia();
    No *p; p = abb;
    No *aux, *proximo;  
    proximo = NULL; aux = NULL;
    bool fim = FALSE;
    if(p!=NULL) {
        do {
            while(p!=NULL) {
                push(&s, p);    p = p->esq;
            }
            if(aux!=NULL) {
                proximo = peek(s);
                fim = TRUE;
            }
            if(verPilhaVazia(s)==FALSE) {
                p = peek(s);
                if(p->chave==chave) {
                    aux = p;
                }
                pop(&s);
                p = p->dir;
            }
            else {
                fim = TRUE;
            }
        }while(fim == FALSE);
        esvaziaPilha(&s);
    }

    return proximo;
}

No* obterAnterior(ArvoreBB abb, int chave) { //Recolhe o Antecessor de um No no caminhamento eRd
    Pilha s = criarPilhaVazia();
    No *p; p = abb;
    No *aux, *anterior;  
    anterior = NULL; aux = NULL;
    bool fim = FALSE;
    if(p!=NULL) {
        do {
            while(p!=NULL) {
                push(&s, p);    p = p->esq;
            }

            if(verPilhaVazia(s)==FALSE) {
                p = peek(s);
                if (p->chave == chave)
                {
                    anterior = aux;
                    fim = TRUE;
                }
                aux = p;
                pop(&s);
                
                p = p->dir;
            }
            else {
                fim = TRUE;
            }
        }while(fim == FALSE);
        esvaziaPilha(&s);
    }
    
    return anterior;
}

ArvoreBB buscaInsere(ArvoreBB abb, int chave) { //Insere um elemento na ABB se ele ja nao existir nela.
    No* p; p = abb; bool fim = FALSE;
    No* ant; 
    No* novoNo; 
    if(abb!=NULL) {
        do {
            ant = p;
            if (p == NULL || p->chave == chave)
            {
                if(p==NULL){
                    novoNo = (No*) malloc(sizeof(No));
                    novoNo->chave = chave;
                    novoNo->dir = NULL;
                    novoNo->esq = NULL;
                    if(chave < ant->chave) {
                        p->esq = novoNo;
                    }
                    else
                        p->dir = novoNo;
                } 
                fim = TRUE;
            }
            else if (p->chave > chave)
            {
                p = p->esq;
            }
            else
            {
                p = p->dir;
            }
        }while(fim==FALSE);
    }

    return abb;
}

No* select(ArvoreBB abb, int y) { //Devolve o No com elemento da ordem k na ordem crescente
    No* alvo; alvo = NULL;
    No* p; p = abb;
    bool fim = FALSE;
    Pilha s = criarPilhaVazia();
    if(abb!=NULL) {
        do {
                while (p != NULL) {
                    push(&s, p);    p = p->esq;
                }
                if (verPilhaVazia(s) == FALSE)
                {
                    p = peek(s);
                    pop(&s);
                    y--;
                    if(y==0) {
                        fim = TRUE;
                        alvo = p;
                    }
                    p = p->dir;
                }
                else {
                    fim = TRUE;
                }

        }while(fim == FALSE);
        esvaziaPilha(&s);
    }

    return alvo;
}

int rank(ArvoreBB abb, int chave) { //Devolve a posicao na ordem crescente em que se encontra um elemento
    No* p; p = abb;
    bool fim = FALSE;
    int cont = 0;
    Pilha s = criarPilhaVazia();
    if(abb!=NULL) {
        do {
                while (p != NULL) {
                    push(&s, p);    p = p->esq;
                }
                if (verPilhaVazia(s) == FALSE)
                {
                    p = peek(s);
                    pop(&s);
                    cont++;
                    if(p->chave == chave) {
                        fim = TRUE;
                    }
                    p = p->dir;
                }
                else {
                    fim = TRUE;
                    cont = -1;
                }

        }while(fim == FALSE);
        esvaziaPilha(&s);
    }

    return cont;
}

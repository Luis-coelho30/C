#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FilaLigada.h"
#include "PilhaLigada.h"

typedef struct No{ 
    int chave; 
    int size;  // size guarda a quantidade de nós da árvore 
    struct No * pai; 
    struct No * esq;  
    struct No * dir; 
} No; 
typedef No* ArvoreBB; 

ArvoreBB criarABB(); // Cria uma nova arvore binaria de busca - ok
ArvoreBB destruirArvore(ArvoreBB); // Libera a memoria de uma arvore binaria de busca destruindo-a - ok
ArvoreBB inserirNo(ArvoreBB, int); //Insere um no na ABB - ok
ArvoreBB removerNo(ArvoreBB, int); //Remove um no na ABB - ok
void mostrarArvore(ArvoreBB); //Mostra a ABB pelo caminhamento eRd (em ordem) - ok
void mostrarArvoreBFS(ArvoreBB); //Mostra a ABB pelo caminhamento BFS - ok
void mostrarArvore_edR(ArvoreBB); //Mostra a ABB pelo caminhamento edR - ok
void mostrarArvore_Red(ArvoreBB); //Mostra a ABB pelo caminhamento Red - ok
void mostrarArvoreRED(ArvoreBB); //Mostra a ABB pelo caminhamento Red recursivamente - ok
void mostrarArvoreEDR(ArvoreBB); //Mostra a ABB pelo caminhamento edR recursivamente - ok
No* obterAncestralIT(ArvoreBB, No*, No*); //Obtem um ancestral comum entre dois nos - ok
No* obterAncestral(ArvoreBB, No*, No*);  //Obtem um ancestral comum entre dois nos por recursao - ok
No* obterPai(No*); //Obtem o pai de um no - ok
ArvoreBB removerRaiz(ArvoreBB); //Remove a raiz de uma ABB - ok
No * buscarABBIT(ArvoreBB, int); //Busca uma chave na ABB iterativamente - ok
No * buscarABB(ArvoreBB, int); //Busca uma chave na ABB - ok
ArvoreBB inserirR(ArvoreBB, int); //Insere um no na ABB por recursao -ok
int obterAltura(ArvoreBB); //Obtem a altura de uma ABB recursivamente - ok
void mostrarPrimeiro(ArvoreBB); //Mostra o primeiro No no caminhamento eRd -ok
void mostrarUltimo(ArvoreBB); //Mostra o ultimo No no caminhamento eRd - ok
No * obterPrimeiro(ArvoreBB); //Recolhe o primeiro No no caminhamento eRd -ok
No * obterSucessor(ArvoreBB, int); //Recolhe o Sucessor de um No no caminhamento eRd - ok
No * obterAnterior(ArvoreBB, int); //Recolhe o Antecessor de um No no caminhamento eRd - ok
ArvoreBB buscaInsere(ArvoreBB, int); //Insere um elemento na ABB se ele ja nao existir nela. -ok
No * select(ArvoreBB, int); //Devolve o No com elemento da ordem k na ordem crescente - ok
int rank(ArvoreBB, int); //Devolve a posicao na ordem crescente em que se encontra um elemento - ok

int main() {
    ArvoreBB A = criarABB();
    A = inserirR(A, 30);   A = inserirNo(A, 7);    A = inserirNo(A, 40);    A = inserirNo(A, 4);    A = inserirNo(A, 20);    A = inserirNo(A, 35);    A = inserirNo(A, 50);    A = inserirNo(A, 2);    A = inserirNo(A, 5);    A = inserirNo(A, 10);
    A = inserirNo(A, 22);    A = inserirNo(A, 32);    A = inserirNo(A, 38);    A = inserirNo(A, 45);    A = inserirNo(A, 60);    A = inserirNo(A, 1); A = inserirNo(A, 3);    A = inserirR(A, 8);    A = inserirNo(A, 12);    A = inserirNo(A, 21);
    A = inserirNo(A, 25);    A = inserirNo(A, 36);    A = inserirR(A, 42);    A = inserirNo(A, 80);    A = inserirR(A, 11);    A = inserirNo(A, 24);
    mostrarArvore(A);
    printf("\n");
    int w = 24, j = 22;
    printf("O menor ancestral entre %d e %d eh o no : %d", buscarABBIT(A, w)->chave, buscarABBIT(A, j)->chave, obterAncestral(A, buscarABB(A, w), buscarABB(A, j))->chave);
    printf("\n");
    int t = 10;
    printf("O elemento na posicao %d eh %d", t, select(A, t)->chave);
    printf("\n");
    int k = 25;
    printf("O elemento %d eh rankeado %d", k, rank(A, k));
    printf("\n");
    int n = 20;
    printf("O elemento %d eh sucedido por %d", n, obterSucessor(A, n)->chave);
    printf("\n");
    int m = 80;
    printf("O elemento %d eh antecedido por %d", m, obterAnterior(A, m)->chave);
    printf("\n");
    int p = 12;
    printf("O pai de %d eh a chave %d", p, obterPai(buscarABBIT(A, p))->chave);
    A = removerRaiz(A);
    printf("\n");
    mostrarArvore(A);
    int h = 90;
    A = buscaInsere(A, h);
    mostrarArvore(A);
    A = destruirArvore(A);
    return 0;
}

ArvoreBB criarABB() {
    ArvoreBB A;
    A = NULL;

    return A;
}

ArvoreBB destruirArvore(ArvoreBB abb) { //Caminhar por erd e apagar os nos na segunda pilha
    Pilha s1 = criarPilhaVazia();
    Pilha s2 = criarPilhaVazia();
    No* p = abb;
    
    if(abb!=NULL) {
        push(&s1, p);

        do {
            p = peek(s1);
            pop(&s1);

            push(&s2, p);

            if(p->dir!=NULL) push(&s1, p->dir);
            if(p->esq!=NULL) push(&s1, p->esq);
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
    No* p = abb;
    No* pai;
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->dir = NULL; novoNo->esq = NULL; 
    novoNo->size = 1;

    if(abb!=NULL) {
        while (p != NULL) {
            pai = p;
            pai->size = pai->size + 1;
            if (p->chave > chave) p = p->esq;
            else p = p->dir;
        }

        if (pai->chave > chave) pai->esq = novoNo;
        else if (pai->chave < chave) pai->dir = novoNo;
        novoNo->pai = pai;
    }
    else {
        abb = novoNo;
        novoNo->pai = NULL;
    }

    return abb;
} 

ArvoreBB removerNo(ArvoreBB abb, int chave) { // Remove um nó na ABB
    No *p, *fa, *m, *ba, *filho, *fm;
    int nf;

    if (abb != NULL) // Árvore não está vazia
    {
        p = abb;
        fa = NULL; // Inicializa o pai como NULL
        nf = 0; // Não tem 2 filhos: ou tem 1 ou não tem filhos
        
        while ((p != NULL) && (p->chave != chave)) // Busca a chave
        {
            fa = p; // Armazena o pai da chave alvo
            if (chave < p->chave) 
                p = p->esq;
            else
                p = p->dir;
        }
        
        if (p != NULL) // Se encontrar a chave alvo
        {
            if (p->esq == NULL) // Se não houver filho esquerdo, guarda o direito
                filho = p->dir;
            else if (p->dir == NULL) // Se não houver filho direito, guarda o esquerdo
                filho = p->esq;
            else // Se houver filho esquerdo e direito, nf = 2
                nf = 2;

            if ((fa == NULL) && (nf == 0)) // Raiz: o pai da chave alvo é NULL e não há dois filhos
            {
                abb = filho; // A nova raiz é o único filho da árvore
                if (filho != NULL) {
                    filho->pai = NULL; // Atualiza o pai do novo nó raiz
                }
                free(p);
            } 
            else if ((fa != NULL) && (nf == 0)) // Folha ou um único filho
            { 
                if (p == fa->esq) // Se p for o filho esquerdo de seu pai
                    fa->esq = filho;
                else // Se p for o filho direito de seu pai
                    fa->dir = filho;

                if (filho != NULL) {
                    filho->pai = fa; // Atualiza o pai do filho
                }
                free(p);
            }
            else // Dois filhos
            {               
                m = p->esq; // m procura o maior filho da subárvore esquerda
                ba = p; // ba será o pai de m
                
                while (m->dir != NULL)
                {
                    ba = m; // ba guarda o pai do maior filho da subárvore esquerda
                    m = m->dir;
                }
                
                fm = m->esq; // fm recebe o filho esquerdo do nó da subárvore esquerda
                
                if (ba != p) // Se o pai não for a chave alvo
                    ba->dir = fm; // o pai da maior chave da subárvore esquerda recebe o filho esquerdo de m
                else 
                    ba->esq = fm; // se ba é o pai de m, atualiza a referência do pai
                
                if (fm != NULL) {
                    fm->pai = ba; // Atualiza o pai do filho de m, se existir
                }

                p->chave = m->chave; // o nó p recebe a chave de m

                // Atualiza o campo size do nó p
                p->size = 1; // Conta o próprio nó
                if (p->esq != NULL) {
                    p->size += p->esq->size; // Adiciona o tamanho da subárvore esquerda, se houver
                }
                if (p->dir != NULL) {
                    p->size += p->dir->size; // Adiciona o tamanho da subárvore direita, se houver
                }

                free(m);
            }

            // Atualiza o campo size para todos os ancestrais a partir do pai
            No *ancestral = fa;
            while (ancestral != NULL) {
                ancestral->size = 1; // Conta o próprio nó
                if (ancestral->esq != NULL) {
                    ancestral->size = ancestral->size + ancestral->esq->size; // Adiciona o tamanho da subárvore esquerda
                }
                if (ancestral->dir != NULL) {
                    ancestral->size = ancestral->size + ancestral->dir->size; // Adiciona o tamanho da subárvore direita
                }
                ancestral = ancestral->pai; // Move para o próximo ancestral
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
        printf("\n");
    }
    else {
        printf("\n Arvore Vazia \n");
    }
}

void mostrarArvoreBFS(ArvoreBB abb) {
    Fila q = criarFila();
    No* p = abb;
    if(abb!=NULL) {
        
        pushFila(&q, p);

        do {
            p = acessarFila(&q);
            popFila(&q);
            printf("%d\t", p->chave);

            if(p->esq!=NULL) pushFila(&q, p->esq);
            if(p->dir!=NULL) pushFila(&q, p->dir);
        }while(verFilaVazia(&q)==FALSE);
    }
    else {
        printf("Arvore vazia.\n");
    }
}

void mostrarArvore_edR(ArvoreBB abb) {
    Pilha s1 = criarPilhaVazia();
    Pilha s2 = criarPilhaVazia();
    No* p = abb;
    
    if(abb!=NULL) {
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
            printf("%d\t", p->chave);
        }
        printf("\n");
    }
    else {
        printf("Arvore vazia.\n");
    }
}

void mostrarArvore_Red(ArvoreBB abb) {
    Pilha s = criarPilhaVazia();
    No* p = abb;

    if(abb!=NULL) {
        push(&s, p);

        do {
            p = peek(s);
            pop(&s);
            printf("%d\t", p->chave);

            if(p->dir!=NULL) push(&s, p->dir);
            if(p->esq!=NULL) push(&s, p->esq);
        }while(verPilhaVazia(s)==FALSE);

        printf("\n");
    }
    else {
        printf("Arvore vazia.\n");
    }
}

void mostrarArvoreRED(ArvoreBB abb) {
    if(abb!=NULL) {
        printf("%d\t", abb->chave);
        mostrarArvoreRED(abb->esq);
        mostrarArvoreRED(abb->dir);
    }

}

void mostrarArvoreEDR(ArvoreBB abb) {
    if(abb!=NULL) {
        mostrarArvoreEDR(abb->esq);
        mostrarArvoreEDR(abb->dir);
        printf("%d\t", abb->chave);        
    }
}

No* obterAncestralIT(ArvoreBB abb, No* n1, No* n2) {//Obtem um ancestral comum entre dois nos
    No* ancestral = NULL;
    bool fim = FALSE;

    if(abb!=NULL) {
        ancestral = abb;
        do {    
            if(ancestral == n1 || ancestral == n2) {
                fim = TRUE;
            }

            else {
                if(ancestral->chave > n1->chave && ancestral->chave > n2->chave) ancestral = ancestral->esq;
                else if(ancestral->chave < n1->chave && ancestral->chave < n2->chave) ancestral = ancestral->dir;
                else fim = TRUE;
            }

        }while(fim == FALSE);
    }

    return ancestral;
}

No* obterAncestral(ArvoreBB abb, No* n1, No* n2)  {//Obtem um ancestral comum entre dois nos por recursao
    
    if(abb!=NULL) {
        if(abb->chave > n1->chave && abb->chave > n2->chave) abb = obterAncestral(abb->esq, n1, n2);

        else if(abb->chave < n1->chave && abb->chave < n2->chave) abb = obterAncestral(abb->dir, n1, n2);
    }

    return abb;
}

No* obterPai(No* p) {
    No* pai = NULL;

    if(p!=NULL) pai = p->pai;
    
    return pai;
}

ArvoreBB removerRaiz(ArvoreBB abb) { //Remove a raiz de uma ABB
    //Caso 1 raiz tem apenas um ou nenhum filho - apagar raiz, abb->esq || abb->dir = novaRaiz
    //Caso 2 raiz tem 2 filhos - Procurar maior no da subarvore esquerda e mandar para raiz
    No* filhoR = NULL;
    int nf = 0;

    if(abb!=NULL) { //Arvore nao eh vazia
        if(abb->esq==NULL) filhoR = abb->dir; 
        else if(abb->dir==NULL) filhoR = abb->esq;
        else nf = 2;

        //Caso 1
        if(nf==0) {
            free(abb);
            abb = filhoR; //Mesmo que filhoR seja NULL, a implementacao continua correta, pois a raiz apontaria para NULL
            if (filhoR != NULL) filhoR->pai = NULL;
        } 
        else { //Caso 2
            No* mEsq = abb->esq;
            while(mEsq->dir!=NULL) {
                mEsq->size = mEsq->size - 1;
                mEsq = mEsq->dir;
            }
            No* fm = mEsq->esq; 
            No* pai;
            
            //Cenario 1 - o maior no esquerdo eh o filho esq da raiz
            if(mEsq->pai == abb) {
                abb->esq = fm; 
                if (fm != NULL) fm->pai = abb;
            }
            //Cenario 2 - o maior no esquerdo esta mais abaixo na arvore
            else {
                pai = mEsq->pai;
                pai->dir = fm;
                if (fm != NULL) fm->pai = pai;
            } 
            abb->chave = mEsq->chave;
            abb->size = abb->size - 1;
            free(mEsq);
        }
    }

    return abb;
} 

No * buscarABBIT(ArvoreBB abb, int chave) {//Busca uma chave na ABB iterativamente
    No* p = abb;

    if(abb!=NULL) {
        while((p!=NULL) && (p->chave!=chave)) {
            if(chave > p->chave) p = p->dir;
            else p = p->esq;
        }
    } 

    return p;
}

No * buscarABB(ArvoreBB abb, int chave) {//Busca uma chave na ABB
    if (abb != NULL)
    {
        if (chave > abb->chave)
            abb = buscarABB(abb->dir, chave);
        else if (chave < abb->chave)
            abb = buscarABB(abb->esq, chave);
    }

    return abb;
}

ArvoreBB inserirR(ArvoreBB abb, int chave) {//Insere um no na ABB por recursao
    if (abb != NULL)
    {
        if (chave > abb->chave) {
            abb->dir = inserirR(abb->dir, chave);
            if (abb->dir != NULL) abb->dir->pai = abb; // Atualiza o campo pai do nó direito
        }
            
        else if (chave < abb->chave) {
            abb->esq = inserirR(abb->esq, chave);
            if (abb->esq != NULL) abb->esq->pai = abb; // Atualiza o campo pai do nó esquerdo
        }

        // Atualiza o tamanho da subárvore atual
        abb->size = 1; // Conta o próprio nó
        if (abb->esq != NULL) {
            abb->size = abb->size + abb->esq->size; // Adiciona o tamanho da subárvore esquerda, se houver
        }
        if (abb->dir != NULL) {
            abb->size = abb->size + abb->dir->size; // Adiciona o tamanho da subárvore direita, se houver
        }
    }
    else {
        No* novoNo = (No *)malloc(sizeof(No));
        novoNo->chave = chave;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->size = 1;
        novoNo->pai = NULL;
        abb = novoNo;
    }

    return abb;
}

int obterAltura(ArvoreBB abb) {//Obtem a altura de uma ABB recursivamente 
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
    No *p, *prox, *R, *fa; prox = NULL; p = abb;
    while ((p != NULL) && (p->chave != chave)) // busca a chave
    {
        if (chave < p->chave) p = p->esq;
        else p = p->dir;
    }
    if (p != NULL) { //Se encontrar a chave
        R = p->dir; //R eh o filho direito de p (chave de r eh maior que p)
        if (R != NULL) { //Se o no procurado tem filho direito, entao a menor chave presente nessa subarvore direita eh seu sucessor
            p = R; 
            while (p->esq != NULL) { p = p->esq; } //Busca o menor na subarvore direita
            prox = p;
        }
        else { //Se p nao tem filho direito, seu ancestral sera o mais proximo e maior
            fa = p->pai; //Recolhe o pai da chave
            while ((fa != NULL) && (fa->dir == p)) { //Enquanto houver pais e p for o filho direito deles (enquanto nao encontrar chave maior que p) escala na arvore
                p = fa;
                fa = p->pai;
            }
            if (fa != NULL) prox = fa; //Se fa nao for null (se nao tiver atingido a raiz)
        }
    }
    return prox;
}

No* obterAnterior(ArvoreBB abb, int chave) { //Recolhe o Antecessor de um No no caminhamento eRd
    No *p, *ant, *R, *fa; ant = NULL; p = abb;
    while ((p != NULL) && (p->chave != chave)) // busca a chave
    {
        if (chave < p->chave) p = p->esq;
        else p = p->dir;
    }
    if (p != NULL) { //Se encontrar a chave
        R = p->esq; //R eh o filho esquerdo de p (chave de r eh menor que p)
        if (R != NULL) { //Se o no procurado tem filho esquerdo, entao o maior no presente nessa subarvore esquerda eh seu antecessor
            p = R; 
            while (p->dir != NULL) { p = p->dir; } //Busca o maior na subarvore esquerda
            ant = p;
        }
        else { //Se p nao tem filho esquerdo, seu ancestral sera o mais proximo e menor
            fa = p->pai; //Recolhe o pai da chave
            while ((fa != NULL) && (fa->esq == p)) { //Enquanto houver pais e p for o filho esquerdo deles (enquanto nao encontrar chave menor que p) escala na arvore
                p = fa;
                fa = p->pai;
            }
            if (fa != NULL) ant = fa; //Se fa nao for null (se nao tiver atingido a raiz)
        }
    }
    return ant;
}

ArvoreBB buscaInsere(ArvoreBB abb, int chave) {//Insere um elemento na ABB se ele ja nao existir nela.
    No* p; No* novoNo; No* paiP;
    p = abb; paiP = NULL;

    if(abb==NULL) {
        novoNo = (No*) malloc(sizeof(No));
        novoNo->chave = chave;
        novoNo->size = 1;
        novoNo->dir = NULL; novoNo->esq = NULL;
        abb = novoNo;
        novoNo->pai = NULL;
    }
    else {
        while((p!=NULL) && (p->chave!=chave)) {
            paiP = p;
            if(chave > p->chave) p = p->dir;
            else p = p->esq;
        }
        if(p==NULL) {
            novoNo = (No *)malloc(sizeof(No));
            novoNo->chave = chave;
            novoNo->size = 1;
            novoNo->dir = NULL;
            novoNo->esq = NULL;

            if (chave > paiP->chave) paiP->dir = novoNo;
            else if (chave < paiP->chave) paiP->esq = novoNo;            
            novoNo->pai = paiP;

            // Atualiza size de cada ancestral (nao pode ser feito no laco anterior pois nao se sabe se a chave nao eh duplicata)
            p = paiP;
            while (p!=NULL) {
                p->size = p->size + 1;
                p = p->pai;
            }
        }
    }

    return abb;
}

No* select(ArvoreBB abb, int k) {//Devolve o No com elemento da ordem k na ordem crescente
    No* p = abb, *e; 
    int rank;
    if(abb!=NULL) { //Se a arvore pesquisada nao for vazia
        if(p->esq==NULL) rank = 0; //Se a subarvore esquerda for vazia, o tamanho total ja pesquisado eh 0
        else { //Se nao for vazia, coleta o tamanho da subarvore esquerda
            e = p->esq;
            rank = e->size;
        }
        if(k < rank + 1) p = select(abb->esq, k); //Se o elemento de ordem k estiver na subarvore esquerda, k sera menor que a quantidade de elementos a esquerda mais 1
        else if(k > rank + 1) p = select(abb->dir, k - rank - 1); //Senao se estiver na subarvore direita, k vai ser maior que a quantidade de elementos a direita mais 1
        //Se k==rank, entao acaba a chamada recursiva e o elemento foi encontrado.
    }
    return p;
}

int rank(ArvoreBB abb, int chave) {//Devolve a posicao na ordem crescente em que se encontra um elemento
    int R;
    No *p, *e, *d;
    R = 0;
    if (abb != NULL) { //Se a arvore nao for vazia
        p = abb;
        while ((p != NULL) && (chave != p->chave)) { //Busca o elemento
            if (chave > p->chave) { //Se a chave for maior que o elemento atual
                d = p->dir; //Pega o elemento a direita
                if (d != NULL) R = R + (p->size - d->size); //Acumula ao rank o tamanho da (subarvore esquerda - subarvore direita) que resulta em raiz + subarvore esquerda 
                p = p->dir; //Avanca para direita
            } 
            else p = p->esq; //Senao, avanca para esquerda. 
            //Aqui nao ha acumulo, pois os elementos da subarvore esquerda aparecerao primeiro do que os da direita, portanto so fazem importancia os da subarvore esquerda da chave procurada
        }

        if (p != NULL) { //Se encontrar a chave
            R = R + 1; //Acumula o valor da propria chave
            e = p->esq; //Pega a subarvore esquerda da chave
            if (e != NULL) R = R + e->size; //Acumula o tamanho da subarvore esquerda, pois estes aparecerao primeiro que a chave alvo
        }
        else R = 0; //Se nao encontrar entao o rank eh 0    
    }
    
    return R;
}
/*
FilaDePrioridadeMax - Este programa tem como objetivo desenvolver o Tipo Abstrato de Dados fila de prioridade maxima (Heap Maxima)
Autor: Luis Augusto Coelho de Souza
Data: 14/09/2024 
*/

#include <stdio.h>
#include <stdlib.h>
#include "Booleano.h"

#define MAX 101 //HEAP MÁXIMA 
#define ghost -1

typedef struct{       
int tamanho; 
int tab[MAX];         
}HeapMax; 

//interface 
void newHeap(HeapMax*);  // cria HeapMax vazia       
void inicializarHeap(HeapMax*, int[ ] ,int); //copia 
void construirHeap_Restauro(HeapMax*); //restaurar 
void construirHeap_Insercao(HeapMax*, int[ ], int); //inserção  
void pushHeap(HeapMax*, int); //insere 
void popHeap(HeapMax*); //remove o maior 
int getHeap(HeapMax*); //obtém o valor máximo 
int obterTamanhoHeap(HeapMax*); //Obter tamanho da heap
void aumentarChave(HeapMax*, int, int); //altera valor: posição, novo valor
void diminuirChave(HeapMax*, int, int); //altera valor:  posição, novo valor 
void restaurarHeapAcima(HeapMax*, int, int); //último,posição 
void restaurarHeapAbaixo(HeapMax*, int, int); //último,posição 
void mostrarHeap(HeapMax*);  // mostra na tela o conteúdo do array 

void newHeap(HeapMax *h) { // cria HeapMax vazia  
    h->tamanho = 0;
}       

void inicializarHeap(HeapMax *h, int V[] ,int tamanho) { //copia 
    int tamanhoHeap = tamanho;
    for(int i = 1; i<=tamanhoHeap; i++) {
        h->tab[i] = V[i];
    }
    h->tamanho = tamanho;
}

void construirHeap_Restauro(HeapMax *h) { //restaurar 
    for(int i = h->tamanho/2; i>=1; i--) {
        restaurarHeapAbaixo(h, h->tamanho, i);
    }
}


void construirHeap_Insercao(HeapMax *h, int V[ ], int tamanho) { //inserção  
    for(int i = 1; i<=tamanho; i++) {
        pushHeap(h, V[i]);
    }
}

void pushHeap(HeapMax *h, int chave) { //insere
    int tamanhoHeap = h->tamanho;
    if(tamanhoHeap<MAX-1) {
        h->tab[tamanhoHeap+1] = chave;
        h->tamanho = h->tamanho + 1;
    }
    restaurarHeapAcima(h, h->tamanho, h->tamanho);
} 

void popHeap(HeapMax *h) { //remove o maior
    int tamanhoHeap = h->tamanho; 
    int aux;
    if(tamanhoHeap>0) {
        aux = h->tab[1];
        h->tab[1] = h->tab[tamanhoHeap];
        h->tab[tamanhoHeap] = aux;
        h->tamanho = h->tamanho - 1;
    }
    restaurarHeapAbaixo(h, h->tamanho, 1);
} 

int getHeap(HeapMax *h) { //obtém o valor máximo 
    int max = ghost;
    if(h->tamanho>0) {
        max = h->tab[1];
    }
    
    return max;
}

int obterTamanhoHeap(HeapMax *h) { //Obter tamanho da heap
    return h->tamanho;
}

void aumentarChave(HeapMax *h, int pos, int chave) { //altera valor: posição, novo valor
    if((pos>0 && pos<MAX) && (chave>h->tab[pos])) {
        h->tab[pos] = chave;
    }
    restaurarHeapAcima(h, h->tamanho, pos);
}

void diminuirChave(HeapMax *h, int pos, int chave) { //altera valor:  posição, novo valor 
    if((pos>0 && pos<MAX) && (chave<h->tab[pos])) {
        h->tab[pos] = chave;
    }
    restaurarHeapAbaixo(h, h->tamanho, pos);
}

void restaurarHeapAcima(HeapMax *h, int ult, int pos) { //último,posição 
    int j = pos; bool fim = FALSE; int pai; int aux;
    if (pos > 1 && pos <= ult)
    {
        while (j > 1 && fim == FALSE)
        {
            pai = j / 2;
            if (h->tab[pai] < h->tab[j])
            {
                aux = h->tab[pai];
                h->tab[pai] = h->tab[j];
                h->tab[j] = aux;
                j = pai;
            }
            else
            {
                fim = TRUE;
            }
        }
    }
}

void restaurarHeapAbaixo(HeapMax *h, int ult, int pos) { //último,posição 
    int ultPai = ult/2; int j = pos; bool fim = FALSE; int aux;
    int e, d, f;
    if (pos >= 1 && pos <= ult)
    {
        while (j <= ultPai && fim == FALSE)
        {
            e = 2 * j;
            d = 2 * j + 1;
            f = e;
            if (d <= ult)
            {
                if (h->tab[d] > h->tab[e])
                {
                    f = d;
                }
            }
            if (h->tab[f] > h->tab[j])
            {
                aux = h->tab[j];
                h->tab[j] = h->tab[f];
                h->tab[f] = aux;
                j = f;
            }
            else
            {
                fim = TRUE;
            }
        }
    }
}

void mostrarHeap(HeapMax *h) {  // mostra na tela o conteúdo do array 
    int tamanhoHeap = h->tamanho;
    printf("\n");
    if(tamanhoHeap!=0) {
        for(int i = 1; i<=tamanhoHeap; i++) {
            printf("%d\t", h->tab[i]);
        }
    }
    else {
        printf("Heap vazia.");
    }
    printf("\n");
}

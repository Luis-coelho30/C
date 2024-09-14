/*
Sorting - Este programa tem como objetivo desenvolver e propor um estudo sobre os principais algoritmos de ordenacao
Autor: Luis Augusto Coelho de Souza
Data: 14/09/2024 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Booleano.h"
#include "FilaDePrioridadeMax.h"
#include "ListaPointer.h"

void selectionSort(Lista*); //Lista a ser ordenada
void insertionSort(Lista*); //Lista a ser ordenada
void bubbleSort(Lista*); //Lista a ser ordenada
//Recursivos
void quickSort(Lista*, int, int); //Lista a ser ordenada, comeco, fim
void mergeSort(Lista*, int, int); //Lista a ser ordenada, comeco, fim
//Heap
void heapSort(Lista*); //Lista a ser ordenada, tamanho

//Funcoes auxiliares
int separarLista(Lista*, int, int); //Fragmenta a lista em torno do pivo - QuickSort
void intercalar(Lista*, int, int, int); //MergeSort
void trocar(Lista*, int, int); //Troca dois elementos em um array
Lista criarListaAleatoria(int); //Cria uma lista aleatoria com n elementos

int main() {
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    heapSort(&A);
    mostrarLista(&A);
    return 0;
}

void selectionSort(Lista *ap) {
    int fim = ap->tamanho;
    int p;
    for(int j=1; j<=ap->tamanho-1; j++) {
        p = 1;
        for(int k = 2; k<=fim; k++) {
            if(ap->vetor[k] > ap->vetor[p])
                p = k;
        }
        if(p!=fim) 
            trocar(ap, p, fim);
        fim = fim - 1;
    }
    
    /*
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    selectionSort(&A);
    mostrarLista(&A);
    */
}

void insertionSort(Lista *ap) {
    int k;
    for(int j = 2; j<=ap->tamanho; j++) {
        ap->vetor[0] = ap->vetor[j]; k = j-1;
        while(ap->vetor[0] < ap->vetor[k]) {
            ap->vetor[k+1] = ap->vetor[k];
            k = k - 1;
        }
        ap->vetor[k+1] = ap->vetor[0];
    }

    /*
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    insertionSort(&A);
    mostrarLista(&A);
    */
}

void bubbleSort(Lista *ap) {
    int fim = ap->tamanho;
    for(int j=1; j<=ap->tamanho-1; j++) {
        for(int k = 1; k<=(fim-1); k++) {
            if(ap->vetor[k] > ap->vetor[k+1])
                trocar(ap, k, k+1);
        }
        fim = fim - 1;
    }

    /*
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    bubbleSort(&A);
    mostrarLista(&A);
    */
}

//Recursivos
void quickSort(Lista *ap, int p, int r)
{
    int j;
    if (p < r)
    {
        j = separarLista(ap, p, r);
        quickSort(ap, p, j - 1);
        quickSort(ap, j + 1, r);
    }
    /*
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    quickSort(&A, 1, 10);
    mostrarLista(&A);
    */
}

void mergeSort(Lista *ap, int p, int r)
{
    int q;
    if (p < r)
    {
        q = (p + r) / 2;
        mergeSort(ap, p, q);
        mergeSort(ap, q + 1, r);
        intercalar(ap, p, q, r);
    }

    /*
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    mergeSort(&A, 1, 10);
    mostrarLista(&A);
    */
}

//Heap
void heapSort(Lista *ap) {
    HeapMax h; int tamanhoHeap = ap->tamanho;
    
    inicializarHeap(&h, ap->vetor, tamanhoHeap);
    construirHeap_Restauro(&h);
    while(obterTamanhoHeap(&h)!=1) {
        popHeap(&h);
    }
    
    for(int i = 1; i<=tamanhoHeap; i++) {
        ap->vetor[i] = h.tab[i];
    }
    
    /*
    Lista A = criarListaAleatoria(10);
    mostrarLista(&A);
    printf("\n");
    heapSort(&A);
    mostrarLista(&A);
    */
}

//------------------------------------------Auxiliares------------------------------------------

int separarLista(Lista *ap, int l, int r)
{
    int i, j, pivo;
    i = l;
    j = r + 1;
    pivo = ap->vetor[l];
    while (i < j)
    {
        do
        {
            i = i + 1;
        } while ((ap->vetor[i] < pivo) && (i < r));
        do
        {
            j = j - 1;
        } while (ap->vetor[j] > pivo);
        if (i < j) {
            trocar(ap, i, j);
        }
    }
    trocar(ap, l, j);
    
    return j;
}

void intercalar(Lista *ap, int p, int q, int n) {
    int j, k, e; int V[obterTamanho(ap)];
    for(j = p; j<=n; j++) V[j] = ap->vetor[j];
    
    j = p; k = q + 1; e = p;
    
    do {
        if(V[j]<=V[k]) {
            ap->vetor[e] = V[j];
            j = j + 1;
        }
        else {
            ap->vetor[e] = V[k];
            k = k + 1;
        }
        e = e + 1;
    }while((j<=q) && (k<=n));

    if(j>q)
        for(int c = k; c<=n; c++) {
            ap->vetor[e] = V[c];
            e = e + 1;
        }
    else {
        for(int c = j; c<=q; c++) {
            ap->vetor[e] = V[c];
            e = e + 1;
        }
    }
}

void trocar(Lista *ap, int pos1, int pos2) {
    int aux;
    if((pos1>0 && pos1<=ap->tamanho) && (pos2>0 && pos2<=ap->tamanho)) {
        aux = ap->vetor[pos1];
        ap->vetor[pos1] = ap->vetor[pos2];
        ap->vetor[pos2] = aux;
    }
}

Lista criarListaAleatoria(int tamanho) {
    Lista A;
    criarLista(&A);
    srand(time(NULL));
    
    for(int i = 1; i<=tamanho; i++) {
        inserir(&A, rand()%1000);
    }

    return A;
}
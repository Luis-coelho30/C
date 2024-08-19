#include "Booleano.h"
#include <stdio.h>
#include <stdlib.h>

#define MaxPilha 10
#define sinal 0
#define fantasma '$'

typedef struct {
	int topo;
	unsigned char Vetor[MaxPilha];
}Pilha;

Pilha criarPilha();
bool PilhaVazia(Pilha);
unsigned char acessarPilha(Pilha);
Pilha pushPilha(Pilha, unsigned char el);
Pilha popPilha(Pilha);
Pilha esvaziarPilha(Pilha);
void mostrarPilha(Pilha);
int obterProfundidade(Pilha);
Pilha inverter(Pilha);
Pilha copy(Pilha, Pilha);

Pilha criarPilha() {
	Pilha A;
	A.topo = sinal;
	
	return A;
}

bool PilhaVazia(Pilha A) {
	bool Vazio=FALSE;
	if(A.topo==sinal)
		Vazio=TRUE;
		
	return Vazio;
}

unsigned char acessarPilha(Pilha A) {
	unsigned char topo = fantasma;
	if(A.topo!=sinal)
		topo = A.Vetor[A.topo];
	
	return topo;
}

Pilha pushPilha(Pilha A, unsigned char el) {
	int local;
	
	if(A.topo<MaxPilha-1){
		local = A.topo + 1;
		A.Vetor[local] = el;
		A.topo = local;
	}	
	
	return A;
}

Pilha popPilha(Pilha A) {
	if(A.topo!=sinal)
		A.topo = A.topo - 1;
		
	return A;
}

Pilha esvaziarPilha(Pilha A) {
	if(A.topo!=sinal)
		A.topo = sinal;
	
	return A;
}

void mostrarPilha(Pilha A) {
	int i;
	for(i = A.topo; i>=1; i--) //(i = A.topo; i>=1; i--)
		printf("%c\n", A.Vetor[i]);
}

int obterProfundidade(Pilha A) {
	int tamanho;
	tamanho = A.topo;
	return tamanho;
}

Pilha inverter(Pilha A) {
	
	int i=1, j = A.topo;
	char aux;
	while(i<j) {
		aux = A.Vetor[i];
		A.Vetor[i]=A.Vetor[j];
		A.Vetor[j]=aux;
		i++;
		j--;
	}
	
	return A;
}

Pilha copy(Pilha A, Pilha B) {
	
	int i;
	B.topo=A.topo;
	for(i=1; i<=A.topo; i++)
		B.Vetor[i]=A.Vetor[i];
		
	return B;
}

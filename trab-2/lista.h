#ifndef LISTA
#define LISTA

#include "arvore.h"

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *criaLista();

void *liberaLista(Lista *l);

void imprimeLista(Lista *l);

Celula *retiraLista(Lista *l, char *nome);

Celula *retiraPrimeiro(Lista *l);

void insereListaOrdenado(Lista *l, Arv *a);

void *insereCelula(Lista *l, Celula *cel);

void insereCelulasHuff(Lista *l, Celula *esq, Celula *dir);

void criaArvoreHuff(Lista *l);

int retAlturaCelula(Lista *l);

unsigned char **criaDicionario(Lista *a, int altura);

char *stringArvore(Lista *l);

Lista *criaListaOrdenada(Lista *l, int *vetFreq);

unsigned char *decodificaArquivo(Lista *l, char *txt, FILE *fp);

#endif
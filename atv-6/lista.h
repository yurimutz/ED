#ifndef LISTA
#define LISTA

#define CAT 6
#define DOG 5

#include "Cachorro.h"
#include "Gato.h"

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *criaLista();

void *liberaLista(Lista *l);

void *imprimeLista(Lista *l);

Celula *retiraLista(Lista *l, char *nome);

void *insereLista(Lista *l, void *p, int tipo);

void *insereCelula(Lista *l, Celula *cel);

float calculaValor(Lista *l);

int procuraElementoGato(Lista *l, Lista *listDest, char *nome);

int procuraElementoCachorro(Lista *l, Lista *listDest, char *nome);

#endif
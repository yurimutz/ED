#ifndef LISTA_H
#define LISTA_H

#include "ComidaNaoVegana.h"
#include "ComidaVegana.h"
#include "Pedido.h"

#define VEGANA 0
#define nVEGANA 1

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *criaLista();

void liberaLista(Lista *l);

void insereLista(Lista *l, void *prod, int tipo);

void insereCelula(Lista *l, Celula *cel);

Celula *retiraLista(Lista *l, char *nome);

int buscaLista(Lista *l, char *nome);

void imprimeLista(Lista *l);

#endif

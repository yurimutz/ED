#ifndef LISTA
#define LISTA

#include "produto.h"

typedef struct Lista Lista;

Lista *criaLista();

void *liberaLista(Lista *l);

void *imprimeLista(Lista *l);

int retiraLista(Lista *l, int codigo);

void *insereLista(Lista *l, Produto *p);


#endif
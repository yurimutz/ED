// Feito dia 28/05/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LISTA
#define LISTA

#include "produto.h"

typedef struct Lista Lista;

Lista *criaLista();

void *liberaLista(Lista *l);

void *imprimeLista(Lista *l);

Lista *busca(Lista *l, int codigo);

Lista *retiraLista(Lista *l, int codigo);

Lista *insereLista(Lista *l, Produto *p);

#endif
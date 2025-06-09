#ifndef LISTA
#define LISTA

#define LIVRO 0
#define LEITOR 1

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *criaLista();

void *liberaLista(Lista *l);

void *imprimeLista(Lista *l);

Celula *retiraLista(Lista *l, char *nome);

void *insereLista(Lista *l, void *p, int tipo);

void *insereCelula(Lista *l, Celula *cel);


#endif
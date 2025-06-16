// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LISTA
#define LISTA

// #include "leitor.h"
// #include "livro.h"

#define LIVRO 0
#define LEITOR 1

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *criaLista();

void liberaLista(Lista *l);

void liberaExterno(Lista *l);

void imprimeLista(Lista *l);

void imprimeBookED(Lista *l);

Celula *retiraLista(Lista *l, char *nome);

void *insereLista(Lista *l, void *p, int tipo);

void *insereCelula(Lista *l, Celula *cel);

Celula *busca(Lista *l, int id);

Lista *retListaLidos(Celula *cel);

Lista *retListaDesejados(Celula *cel);

Lista *retListaRecomendados(Celula *cel);

Lista *retListaLeitoresComAfinidade(Celula *cel);

char *retLivroTituloLista(Celula *cel);

char *retLeitorNomeLista(Celula *cel);

void *verificaLivrosEmComum(Celula *l1, Celula *l2);

void adicionaAfinidades(Lista *l);

int verificaAfinidadeLista(Celula *l1, Celula *l2);

int encotraLeitorComum(Lista *l1, Lista *l2);

#endif
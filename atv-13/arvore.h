#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv Arv;

typedef int (*comparaCliente) (void *v, void *a);

typedef void (*destroy)(void *a);

Arv *abb_criaVazia();

//Arv* arv_cria (Aluno* c, Arv* e, Arv* d);

void abb_imprime (Arv* a, int (*comparaCliente) (void *v, void *a), FILE *fp);

Arv* abb_busca (Arv* r, int v);

Arv* abb_insere (Arv* a, void *v, int (*comparaCliente)(void *a, void *g));

Arv* abb_retira (Arv* r, int v);

void arv_imprime (Arv* a);

Arv* abb_libera (Arv* a, void (*destroy)(void *info));

#endif 
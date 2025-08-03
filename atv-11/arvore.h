#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

typedef struct arv Arv;

Arv *abb_criaVazia();

//Arv* arv_cria (Aluno* c, Arv* e, Arv* d);

void abb_imprime (Arv* a);

Arv* abb_busca (Arv* r, int v);

Arv* abb_insere (Arv* a, Aluno *v);

Arv* abb_retira (Arv* r, int v);

void arv_imprime (Arv* a);

Arv* abb_libera (Arv* a);

#endif 
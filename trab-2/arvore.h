#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv Arv;

Arv *abb_criaVazia();

Arv* arv_cria (int frequencia, char carac);

Arv* arvCriaNaoVazia(Arv *esq, Arv *dir);

void abb_imprime (Arv* a);

Arv* abb_busca (Arv* r, int v);

Arv* abb_insere (Arv* a, Arv *info);

//Arv* abb_retira (Arv* r, int v);

void arv_imprime (Arv* a);

Arv* abb_libera (Arv* a);

int retFrequencia(Arv *a);

char retCarac(Arv *a);

int altura(Arv* a);

void preencheDicionario(unsigned char **dic, Arv *a, char *conteudo, int altura);

void criaStringArvore(Arv* a, char* conteudo);

char *decodificaFinal(Arv *a, char *txtCodificado, FILE *fp);

#endif 
#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

typedef struct arv Arv;

Arv *abb_criaVazia();

Arv* arv_cria (unsigned int frequencia, unsigned char carac);

Arv* arvCriaNaoVazia(Arv *esq, Arv *dir);

void abb_imprime (Arv* a);

void arv_imprime (Arv* a);

Arv* abb_libera (Arv* a);

unsigned int retFrequencia(Arv *a);

unsigned char retCarac(Arv *a);

unsigned int altura(Arv* a);

void preencheDicionario(unsigned char **dic, Arv *a, unsigned char *conteudo, unsigned int altura);

void criaStringArvore(Arv* a, unsigned char* conteudo);

unsigned char *decodificaFinal(Arv *a, unsigned char *txtCodificado, FILE *fp);

unsigned char *decodificaFinal2(Arv *a, bitmap *bm, unsigned int tamUtil, char *dir);

Arv *recriaArvore(bitmap *bm, unsigned int *tamAtual, unsigned int tamUtil);

unsigned int calculaTamanhoArvore(Arv* a);

void criaStringArvore_Manual(Arv* a, unsigned char* buffer, unsigned int* indice);

#endif 